#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 100
#define ALPHABET 26

int debug = 1;

int charactersOnly(const char *string) {
  while (*string)
    if (isalpha(*string++) == 0)
      return 0;
  return 1;
}

char *caesar(char *plaintext, char *key) {
  int length = strlen(plaintext);
  char *cypherText = (char *)malloc(length + 1);

  for (int i = 0; i < length; i++) {
    char current = plaintext[i];
    if (islower(current))
      cypherText[i] = tolower(key[current - 'a']);
    else if (isupper(current))
      cypherText[i] = toupper(key[current - 'A']);
    else
      cypherText[i] = current;
  }
  cypherText[length] = '\0';

  return cypherText;
}

int checkDuplicates(char *key) {
  for (int i = 0, j = ALPHABET; i < j; i++) {
    for (int k = i + 1; k < j; k++) {
      if (key[i] == key[k]) {
        return 1;
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2 || !charactersOnly(argv[1])) {
    printf("Usage: ./substitution key");
    return 1;
  }
  if (strlen(argv[1]) != ALPHABET) {
    printf("Key must contain 26 characters.");
    return 1;
  }
  char *key = argv[1];
  if (debug)
    printf("KEY: %s\n", key);
  if (checkDuplicates(key)) {
    printf("Key must not repeat any character.");
    return 1;
  }

  char *plainText = (char *)malloc(sizeof(char *) * BUFFERSIZE);
  printf("plaintext:  ");
  scanf("%[^\n]", plainText);

  char *cipherText = caesar(plainText, key);
  printf("ciphertext: %s\n", cipherText);

  free(plainText);
  free(cipherText);
  return 0;
}
