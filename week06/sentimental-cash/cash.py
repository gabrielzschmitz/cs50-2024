"""
Program Description:
--------------------
The cash.py program, located in the sentimental-cash folder, is designed to
prompt the user for an amount of change owed in dollars and determine the
minimum number of coins required to make that change. The user inputs the change
owed in dollars (e.g., 0.50 dollars instead of 50 cents), and the program
calculates the optimal distribution of quarters, dimes, nickels, and pennies.

Implementation Details:
-----------------------
- The count_change function takes the total cents and a coin value and returns
the number of coins of that denomination and the remaining cents after
calculating the change.
- The program continuously prompts the user for input until a non-negative
numeric value is provided.
- The provided dollars input is converted to cents (rounded) for further
calculations.
- The count_change function is used to determine the number of quarters, dimes,
nickels, and pennies required.
- The program prints the total number of coins needed to make the given change.

Usage:
------
Execute the program by running the command: python cash.py

Note: The user should input the change owed in dollars when prompted.
"""


def count_change(cents, coin):
    return cents // coin, cents % coin


while True:
    try:
        dollars = float(input("Change owed: "))
        if dollars >= 0:
            break
    except ValueError:
        print("Invalid input. Please enter a non-negative numeric value.")

cents = round(dollars * 100)

quarters, cents = count_change(cents, 25)
dimes, cents = count_change(cents, 10)
nickels, cents = count_change(cents, 5)
pennies = cents

change_amount = quarters + dimes + nickels + pennies
print(change_amount)
