"""
Program Description:
--------------------
The credit.py program, located in the sentimental-credit folder, is designed to
prompt the user for a credit card number and determine whether it is a valid
American Express, MasterCard, or Visa card number. The program utilizes the Luhn
algorithm for credit card number validation.

Implementation Details:
-----------------------
- The check_size function checks the size and initial digit of the credit card
number to determine if it is within the valid range for American Express,
MasterCard, or Visa.
- The luhn_algorithm function implements the Luhn algorithm to validate the
credit card number.
- The print_type function identifies and prints the type of credit card based
on its size and initial digits.
- The main function prompts the user for a credit card number, performs
validation, and prints the type of credit card or "INVALID" if it fails
validation.

Usage:
------
Execute the program by running the command: python credit.py

Note: The user should input the credit card number when prompted.
"""


def check_size(credit_card_number):
    size = len(credit_card_number)
    if not (1 <= int(credit_card_number[0]) <= 9) or size not in {13, 15, 16}:
        return -1

    return size


def luhn_algorithm(credit_card_number, size):
    addup = 0

    for i in range(size - 1, -1, -2):
        digit = int(credit_card_number[i - 1]) * 2 if i - 1 >= 0 else 0
        addup += (digit % 10) + digit // 10
        addup += int(credit_card_number[i])

    return addup


def print_type(credit_card_number, size):
    number = int(credit_card_number[:2])
    if size == 15 and number in {34, 37}:
        print("AMEX")
    elif size != 15 and credit_card_number[0] == "4":
        print("VISA")
    elif size == 16 and 51 <= number <= 55:
        print("MASTERCARD")
    else:
        print("INVALID")


def main():
    try:
        credit_card_number = input("Number: ").replace(" ", "")

        size = check_size(credit_card_number)
        if size == -1 or luhn_algorithm(credit_card_number, size) % 10 != 0:
            print("INVALID")
            return

        print_type(credit_card_number, size)
    except ValueError:
        print("INVALID")


if __name__ == "__main__":
    main()
