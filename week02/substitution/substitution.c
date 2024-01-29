/*
  Program Description:
  --------------------
  This C program, named substitution.c, is located in the "substitution" folder.
  It enables the encryption of messages using a substitution cipher. The user
  provides a command-line argument specifying the key for the substitution
  cipher, and then the program prompts the user for input text to be encrypted.

  Implementation Details:
  -----------------------
  - The program checks the validity of the key provided by the user, ensuring it
  contains only alphabetic characters, has a length of 26 characters, and does
  not contain any repeated characters.
  - The charactersOnly function checks if a string contains only alphabetic
  characters.
  - The caesar function encrypts the input text using the substitution cipher
  based on the provided key.
  - The checkDuplicates function checks for duplicate characters in the key.
  - The main function validates the command-line argument, key, and input text,
  and then prints the resulting ciphertext.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
  The program will prompt for input text, and if the user enters "HELLO," it
  will output: "ciphertext: FOLLE"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 100
#define ALPHABET   26

int charactersOnly(const char *string) {
  while (*string)
    if (!isalpha(*string++)) return 0;
  return 1;
}

char *substitution(char *plaintext, char *key) {
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
  int charCount[ALPHABET] = {0};

  for (int i = 0; i < ALPHABET; i++) {
    char current = tolower(key[i]);
    if (isalpha(current)) {
      if (charCount[current - 'a'] == 1) return 1;
      charCount[current - 'a']++;
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
  if (checkDuplicates(key)) {
    printf("Key must not repeat any character.");
    return 1;
  }

  char plainText[BUFFERSIZE];
  printf("plaintext:  ");
  scanf("%[^\n]", plainText);

  char *cipherText = substitution(plainText, key);
  printf("ciphertext: %s\n", cipherText);

  free(cipherText);
  return 0;
}
