/*
  Program Description:
  --------------------
  This C program, named credit.c, is located in the "credit" folder. It is
  designed to check the validity of a given credit card number using the Luhn
  algorithm. Credit card numbers typically have specific characteristics, such
  as length and initial digits, depending on the issuing company (e.g., American
  Express, Visa, MasterCard).

  Implementation Details:
  -----------------------
  - The program prompts the user for a credit card number and performs various
  checks to determine its validity.
  - It uses a function checkSize to verify the size of the credit card number
  and its initial digit, adhering to the conventions of different card issuers
  (e.g., American Express, Visa, MasterCard).
  - The Luhn algorithm is implemented in the function luhnAlgorithm to calculate
  the checksum and verify the mathematical relationship between the digits.
  - The program uses a function printType to identify and print the type of
  credit card (e.g., AMEX, VISA, MASTERCARD) based on the card's
  characteristics.
  - Dynamic memory allocation is utilized to store the credit card number using
  malloc, and proper error checks are performed to handle memory allocation
  failures.
  - The program continuously prompts the user for a valid credit card number
  until a valid input is provided.
  - After obtaining a valid credit card number, the program checks its validity
  using the Luhn algorithm and prints the type of credit card if valid;
  otherwise, it outputs "INVALID."

  Usage Example:
  --------------
  Suppose the user enters the credit card number "378282246310005" in response
  to the prompt. The program will output: "AMEX"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 20

int checkSize(char *creditCardNumber) {
  int size = strlen(creditCardNumber);
  if (size != 13 && size != 15 && size != 16) return -1;
  if (creditCardNumber[0] < '1' || creditCardNumber[0] > '9') return -1;

  return size;
}

int luhnAlgorithm(char *creditCardNumber, int size) {
  int addup = 0;

  int i = size - 1;
  while (i >= 0) {
    if (i - 1 >= 0) {
      int digit = (creditCardNumber[i - 1] - '0') * 2;
      if (digit >= 10)
        addup += (digit % 10) + 1;
      else
        addup += digit;
    }
    addup += (creditCardNumber[i] - '0');
    i -= 2;
  }

  return addup;
}

void printType(char *creditCardNumber, int size) {
  int number = ((creditCardNumber[0] - '0') * 10) + creditCardNumber[1] - '0';
  if (size == 15 && (number == 34 || number == 37))
    printf("AMEX\n");
  else if (size != 15 && ((int)(number / 10) == 4))
    printf("VISA\n");
  else if (size == 16 && (number >= 51 && number <= 55))
    printf("MASTERCARD\n");
  else
    printf("INVALID\n");
}

int main(void) {
  char *creditCardNumber = (char *)malloc(sizeof(char) * BUFFERSIZE);
  if (!creditCardNumber) return 1;

  int size = 0;
  while (size == 0) {
    printf("Number: ");
    scanf("%s", creditCardNumber);
    getc(stdin);
    size = checkSize(creditCardNumber);
    if (size == -1) {
      printf("INVALID\n");
      free(creditCardNumber);
      return 0;
    }
  }

  if (luhnAlgorithm(creditCardNumber, size) % 10 != 0) {
    printf("INVALID\n");
    free(creditCardNumber);
    return 0;
  }

  printType(creditCardNumber, size);
  free(creditCardNumber);
  return 0;
}
