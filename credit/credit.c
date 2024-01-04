#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 20

int checkSize(char *creditCardNumber) {
  int size = -1;
  size = strlen(creditCardNumber);
  if (creditCardNumber[0] < 0 || creditCardNumber[0] < 9)
    return -1;
  switch (size) {
  case 13:
    break;
  case 15:
    break;
  case 16:
    break;
  default:
    return -1;
  }
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
  char creditCardNumber[BUFFERSIZE];

  int size = 0;
  while (size == 0) {
    printf("Number: ");
    scanf("%s", creditCardNumber);
    getc(stdin);
    size = checkSize(creditCardNumber);
    if (size == -1) {
      printf("INVALID\n");
      return 0;
    }
  }

  if (luhnAlgorithm(creditCardNumber, size) % 10 != 0) {
    printf("INVALID\n");
    return 0;
  }

  printType(creditCardNumber, size);
  return 0;
}
