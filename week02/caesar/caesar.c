/*
  Program Description:
  --------------------
  This C program, named caesar.c, is located in the "caesar" folder. It enables
  the encryption of messages using Caesar's cipher. The user specifies the key
  as a command-line argument when executing the program, and then they provide
  the plaintext message at runtime. The program ensures that the key is a
  positive integer and handles both uppercase and lowercase letters in the
  input.

  Implementation Details:
  -----------------------
  - The program checks the validity of the key provided as a command-line
  argument using the isValidKey function, ensuring it is a positive integer.
  - The caesar function takes a plaintext message and a key, encrypts it using
  Caesar's cipher, and returns the ciphertext.
  - The main function checks if the correct number of command-line arguments is
  provided and if the key is valid. If not, it prints a usage message and exits.
  - The user inputs the plaintext message, and the program calls the caesar
  function to encrypt it with the specified key.
  - The resulting ciphertext is printed to the console.

  Usage Example:
  --------------
  Suppose the user executes the program with the command:
  "./caesar 3"
  The program prompts for a plaintext message, and the user enters "HELLO". The
  program then outputs: "ciphertext: KHOOR"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 100

int isValidKey(const char *key) {
  while (*key)
    if (isdigit(*key++) == 0) return 0;
  return 1;
}

char *caesar(char *plaintext, int key) {
  int length = strlen(plaintext);
  char *cypherText = (char *)malloc(length + 1);

  for (int i = 0; i < length; i++) {
    char current = plaintext[i];
    if (isalpha(current)) {
      char base = islower(current) ? 'a' : 'A';
      cypherText[i] = (current - base + key) % 26 + base;
    } else
      cypherText[i] = current;
  }
  cypherText[length] = '\0';

  return cypherText;
}

int main(int argc, char *argv[]) {
  if (argc != 2 || !isValidKey(argv[1])) {
    printf("Usage: ./caesar key");
    return 1;
  }
  int key = atoi(argv[1]);

  char plainText[BUFFERSIZE];
  printf("plaintext:  ");
  scanf("%[^\n]", plainText);

  char *cipherText = caesar(plainText, key);
  printf("ciphertext: %s\n", cipherText);

  free(cipherText);
  return 0;
}
