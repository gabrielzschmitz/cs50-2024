/*
  Program Description:
  --------------------
  This C program, named hello.c, resides in the "me" folder. It is designed to
  interact with the user by prompting them for their name. Once the user inputs
  their name, the program greets them by printing "hello, [name]\n!" to the
  console.

  Implementation Details:
  -----------------------
  - The program uses dynamic memory allocation to create a character array to
  store the user's name.
  - A buffer size of 100 characters is defined using the macro BUFFERSIZE to
  ensure sufficient space for the user's input.
  - The program checks if the memory allocation is successful; if not, it
  returns an error code (1).
  - The user is prompted to enter their name with the message
  "What's your name?".
  - The program reads the user's input using the scanf function and stores it
  in the allocated memory.
  - It then prints a personalized greeting using the entered name with the
  format "hello, [name]\n".
  - Finally, the allocated memory is freed to prevent memory leaks.

  Usage Example:
  --------------
  If the user enters "Adele" in response to the prompt, the program will
  output: "hello, Adele\n!"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>
#include <stdlib.h>
#define BUFFERSIZE 100

int main(void) {
  char *name = (char *)malloc(sizeof(char) * BUFFERSIZE);
  if (!name) return 1;

  printf("What's your name? ");
  scanf("%s", name);

  printf("hello, %s\n", name);

  free(name);
  return 0;
}
