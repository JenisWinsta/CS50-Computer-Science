from cs50 import get_float

quater = 25  # Value of a quarter in cents
dime = 10   # Value of a dime in cents
nickel = 5  # Value of a nickel in cents
penny = 1

n = get_float("Change: ")
while n < 0:
    n = get_float("Change: ")


n = n*100

cents = n*100

score = 0

# Calculate the number of quarters needed
score += int(n / quater)
n = n % quater


# Calculate the number of dimes needed
score += int(n / dime)
n = n % dime

# Calculate the number of nickels needed
score += int(n / nickel)
n = n % nickel

# Add the remaining cents (pennies) directly to the score
score += n

# Print the total number of coins used
print(int(score))
