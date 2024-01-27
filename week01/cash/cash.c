/*
  Program Description:
  --------------------
  This C program, named cash.c, resides in the "cash" folder. It is designed for
  use in a store to calculate and print the minimum number of coins needed to
  make change for a given amount. The program prompts the user for an integer
  greater than 0, representing the change owed, and then calculates the minimum
  number of quarters, dimes, nickels, and pennies required for the change.

  Implementation Details:
  -----------------------
  - The program utilizes a while loop to repeatedly prompt the user for the
  change owed until a valid input is provided. The input must be an integer
  greater than or equal to 0.
  - The countChange function takes a reference to the remaining cents and a coin
  value and calculates the number of coins of that denomination needed for the
  change. It also updates the remaining cents accordingly.
  - The main function uses countChange to determine the number of quarters,
  dimes, nickels, and pennies required to make the change.
  - The total number of coins needed is calculated and printed to the console.
  - The program ensures continuous re-prompting of the user in case of invalid
  input (not an integer or less than 0).

  Usage Example:
  --------------
  Suppose the user enters the change owed as "70" in response to the prompt. The
  program will output: "4"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>

int countChange(int *cents, int coin) {
  int count = *cents / coin;
  *cents %= coin;
  return count;
}

int main(void) {
  int cents = -1;
  while (cents < 0) {
    printf("Change owed: ");
    scanf("%d", &cents);
    getc(stdin);
  }

  int quarters = countChange(&cents, 25);
  int dimes = countChange(&cents, 10);
  int nickels = countChange(&cents, 5);
  int pennies = countChange(&cents, 1);

  int changeAmount = quarters + dimes + nickels + pennies;
  printf("%d\n", changeAmount);
}
