/*
  Program Description:
  --------------------
  This C program, named mario.c, is located in the "mario-less" folder. It aims
  to recreate a pyramid pattern using hashes (#) as bricks. The program prompts
  the user for the desired height of the pyramid, ensuring the input is a
  positive integer within the range of 1 to 8. The user is re-prompted until a
  valid input is provided.

  Implementation Details:
  -----------------------
  - The program utilizes a do-while loop to repeatedly prompt the user for the
  pyramid height until a valid input is received.
  - The user input is stored in the 'height' variable, initialized to -1 to
  ensure entry into the loop.
  - The loop condition checks if the height is less than 1 or greater than 8,
  re-prompting the user in such cases.
  - After obtaining a valid height, the program uses nested loops to generate
  the pyramid pattern.
  - The outer loop iterates over each row of the pyramid, while the inner loop
  handles the columns for each row.
  - The program prints either a space or a hash based on the specified
  conditions to form the pyramid structure.
  - Each row is followed by a newline character, creating the desired pyramid
  pattern.

  Usage Example:
  --------------
  Suppose the user enters the height "3" in response to the prompt. The program
  will output the following pyramid:

    #
   ##
  ###

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>

int main(void) {
  int height = -1;
  do {
    printf("Height: ");
    scanf("%d", &height);
  } while (height < 1 || height > 8);

  for (int row = 0; row < height; row++) {
    for (int column = 0; column < height; column++) {
      if (row + column >= height - 1)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }

  return 0;
}
