#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Define coin values in cents
    int quater = 25; // Value of a quarter in cents
    int dime = 10;   // Value of a dime in cents
    int nickel = 5;  // Value of a nickel in cents
    int n;           // Variable to store the change owed

    // Prompt the user for a non-negative amount of change
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 0); // Repeat until a valid (non-negative) amount is entered

    int score = 0; // Variable to track the total number of coins used

    // Calculate the number of quarters needed
    score += n / quater; // Add the number of quarters to the score
    n = n % quater;      // Update the remaining change after quarters

    // Calculate the number of dimes needed
    score += n / dime; // Add the number of dimes to the score
    n = n % dime;      // Update the remaining change after dimes

    // Calculate the number of nickels needed
    score += n / nickel; // Add the number of nickels to the score
    n = n % nickel;      // Update the remaining change after nickels

    // Add the remaining cents (pennies) directly to the score
    score += n; // Since each penny is worth 1 cent, remaining cents = number of pennies

    // Print the total number of coins used
    printf("%i \n", score);
}
