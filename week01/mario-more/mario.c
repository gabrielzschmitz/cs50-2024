/*
  Program Description:
  --------------------
  This C program, named mario.c, is located in the "mario-more" folder. It aims
  to create a pair of pyramids using hashes (#) for bricks. The user is prompted
  to input a positive integer between 1 and 8 (inclusive) to determine the
  height of the pyramids. The program ensures the input is valid and re-prompts
  the user as needed.

  Implementation Details:
  -----------------------
  - The program utilizes a do-while loop to repeatedly prompt the user for the
  pyramid height until a valid input is received.
  - The user input is stored in the 'height' variable, initialized to -1 to
  ensure entry into the loop.
  - The loop condition checks if the height is less than 1 or greater than 8,
  re-prompting the user in such cases. The height is then decremented by 1 to
  adjust for indexing.
  - The program uses nested loops to generate the left and right halves of each
  row of the pyramids.
  - The first half (left) of each row is printed with spaces and hashes based on
  specific conditions to create a left-aligned pyramid.
  - The second half (right) of each row is printed with hashes to create a
  right-aligned pyramid.
  - The two halves are separated by two spaces to align the pyramids properly.
  - The program repeats this process for each row, creating a pair of pyramids.

  Usage Example:
  --------------
  Suppose the user enters the height "4" in response to the prompt. The program
  will output the following pair of pyramids:

     # #
    ## ##
   ### ###
  #### ####

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>

int main(void) {
  int height = -1;
  do {
    printf("Height: ");
    scanf("%d", &height);
  } while (height < 1 || height > 8);
  height -= 1;

  for (int rowLeft = 0; rowLeft <= height; rowLeft++) {
    for (int column = 0; column <= height; column++) {
      if (rowLeft + column >= height)
        printf("#");
      else
        printf(" ");
    }
    printf("  ");

    int rowRight = height - rowLeft;
    for (int column = 0; column <= height; column++)
      if (rowRight + column <= height) printf("#");
    printf("\n");
  }

  return 0;
}
