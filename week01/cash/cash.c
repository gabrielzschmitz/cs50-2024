#include <stdio.h>

int countChange(int cents, int coin) {
  int count = 0;
  while (cents >= coin) {
    cents = cents - coin;
    count++;
  }
  return count;
}

int main(void) {
  int cents = -1;
  while (cents < 0) {
    printf("Change owed: ");
    scanf("%d", &cents);
    getc(stdin);
  }

  int quarters = countChange(cents, 25);
  cents = cents - (quarters * 25);

  int dimes = countChange(cents, 10);
  cents = cents - (dimes * 10);

  int nickels = countChange(cents, 5);
  cents = cents - (nickels * 5);

  int pennys = countChange(cents, 1);
  cents = cents - (pennys * 1);

  int changeAmount = quarters + dimes + nickels + pennys;
  printf("%d\n", changeAmount);
}
