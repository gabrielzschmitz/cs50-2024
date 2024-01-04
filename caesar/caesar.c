#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 100

int debug = 0;

int digitsOnly(const char *string) {
  while (*string)
    if (isdigit(*string++) == 0)
      return 0;
  return 1;
}

char *caesar(char *plaintext, int key) {
  int length = strlen(plaintext);
  char *cypherText = (char *)malloc(length + 1);

  for (int i = 0; i < length; i++) {
    char current = plaintext[i];
    if (islower(current))
      cypherText[i] = 'a' + (current - 'a' + key) % 26;
    else if (isupper(current))
      cypherText[i] = 'A' + (current - 'A' + key) % 26;
    else
      cypherText[i] = current;
  }
  cypherText[length] = '\0';

  return cypherText;
}

int main(int argc, char *argv[]) {
  int key = -1;
  if (argc != 2 || !digitsOnly(argv[1])) {
    printf("Usage: ./caesar key");
    return 1;
  }
  sscanf(argv[1], "%d", &key);
  if (debug)
    printf("KEY: %d\n", key);

  char *plainText = (char *)malloc(sizeof(char *) * BUFFERSIZE);
  printf("plaintext:  ");
  scanf("%[^\n]", plainText);

  char *cipherText = caesar(plainText, key);
  printf("ciphertext: %s\n", cipherText);

  free(plainText);
  free(cipherText);
  return 0;
}
