import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    user = db.execute("SELECT cash FROM users WHERE id=?", user_id)

    if not user:
        return apology("user not found", 400)
    cash = user[0]["cash"]

    rows = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id=? GROUP BY symbol HAVING total_shares >0",
        user_id,
    )

    portfolio = []
    total_stock_value = 0

    for row in rows:
        stock = lookup(row["symbol"])
        if not stock:
            return apology("stock lookup failed", 400)

        current_price = stock["price"]
        total_value = current_price * row["total_shares"]

        portfolio.append(
            {
                "symbol": stock["symbol"],
                "name": stock["name"],
                "shares": row["total_shares"],
                "price": usd(current_price),
                "total": usd(total_value),
            }
        )

        total_stock_value += total_value

    grand_total = cash + total_stock_value

    # Render the portfolio in the index.html template
    return render_template(
        "index.html",
        portfolio=portfolio,
        cash=usd(cash),
        grand_total=usd(grand_total),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide stock symbol", 400)

        stock = lookup(symbol)

        if not stock:
            return apology("invalid stock symbol", 400)

        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("shares must be a positive integer", 400)

        user_id = session["user_id"]
        user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        if not user:
            return apology("user not found", 400)

        cash = user[0]["cash"]

        price = stock["price"]
        total_cost = price * shares

        if total_cost > cash:
            return apology("can't afford", 400)

        db.execute("UPDATE users SET cash = cash -? WHERE id = ?", total_cost, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?,?,?,?)",
            user_id,
            stock["symbol"],
            shares,
            price,
        )

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get the user ID from the session
    user_id = session["user_id"]

    # Query the database to retrieve all transactions for the user
    transactions = db.execute(
        "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        user_id,
    )

    # Render the history.html template, passing the transactions
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("muct provide a stock symbol", 400)

        # look up the stock information using the lookup helper function
        stock = lookup(symbol)

        if not stock:
            return apology("invalide stock symbol", 400)

        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        if not password:
            return apology("must provide password", 400)

        if password != confirmation:
            return apology("passwords do not match", 400)

        # Try to insert the new user into the database
        try:
            hash_pw = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pw)
        except ValueError:
            return apology("username already exists", 400)

        # Redirect to the login page upon successful registration
        flash("Registered successfully! Please log in.")
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get the user ID from the session
    user_id = session["user_id"]

    # Handle GET request (render the sell form)
    if request.method == "GET":
        stocks = db.execute(
            "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
            user_id,
        )
        return render_template("sell.html", stocks=stocks)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must select a stock", 400)

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a valid number of shares", 400)

        shares = int(shares)

        # Query the database to check if the user owns the stock and has enough shares
        rows = db.execute(
            "SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )
        if len(rows) != 1 or rows[0]["total_shares"] < shares:
            return apology("not enough shares", 400)

        # Use lookup to get the current price of the stock
        stock = lookup(symbol)
        if not stock:
            return apology("stock lookup failed", 400)

        # Calculate the total value of the sale
        total_sale_value = shares * stock["price"]

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_sale_value, user_id)

        # Record the sale in the transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id,
            symbol,
            -shares,  # Negative shares to indicate a sale
            stock["price"],
        )

        # Redirect the user to the home page
        return redirect("/")
