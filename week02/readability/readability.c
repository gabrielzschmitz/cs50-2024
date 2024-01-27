/*
  Program Description:
  --------------------
  This C program, named readability.c, is located in the "readability" folder.
  It calculates the approximate grade level needed to comprehend a given text.
  The program takes user input for the text and computes the grade level based
  on the Coleman-Liau index. The result is then rounded to the nearest integer
  and displayed as output, with specific messages for extreme cases.

  Implementation Details:
  -----------------------
  - The program prompts the user to input text and reads it using scanf.
  - The countInfos function calculates the number of letters, words, and
  sentences in the text.
  - The Coleman-Liau index (CLI) is calculated using the formula:
  index = 0.0588 * L - 0.296 * S - 15.8,
  where L is the average number of letters per 100 words, and S is the average
  number of sentences per 100 words.
  - The program then rounds the calculated index to the nearest integer.
  - If the index is less than 1, the program outputs "Before Grade 1". If the
  index is 16 or higher, it outputs "Grade 16+". Otherwise, it outputs the
  calculated grade level.

  Usage Example:
  --------------
  Suppose the user enters the following text:
  "There are more things in Heaven and Earth, Horatio, than are dreamt of in
  your philosophy." The program will output: "Grade 9"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 1000

void countInfos(int *letters, int *words, int *sentences, char *text) {
  int length = strlen(text);
  for (int i = 0; i < length; i++) {
    if (isalpha(text[i]))
      *letters += 1;
    else if (text[i] == ' ')
      *words += 1;
    else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
      *sentences += 1;
  }
}

int main(void) {
  char text[BUFFERSIZE];
  printf("Text: ");
  scanf("%[^\n]", text);

  int words = 1;
  int letters = 0;
  int sentences = 0;
  countInfos(&letters, &words, &sentences, text);

  float L = ((float)letters / words) * 100;
  float S = ((float)sentences / words) * 100;

  int index = round(0.0588 * L - 0.296 * S - 15.8);
  if (index < 1)
    printf("Before Grade 1\n");
  else if (index >= 16)
    printf("Grade 16+\n");
  else
    printf("Grade %d\n", index);

  return 0;
}
