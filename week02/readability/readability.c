#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1000

int debug = 0;

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
  char *text = (char *)malloc(sizeof(char *) * BUFFERSIZE);
  printf("Text: ");
  scanf("%[^\n]", text);

  if (debug)
    printf("\n%s <-- INPUT\n", text);

  // index = 0.0588 * L - 0.296 * S - 15.8
  int words = 1;
  int letters = 0;
  int sentences = 0;

  countInfos(&letters, &words, &sentences, text);
  if (debug)
    printf("%d LETTERS, %d WORDS, %d SENTENCES\n", letters, words, sentences);

  float L = ((float)letters / words) * 100;
  float S = ((float)sentences / words) * 100;

  int index = round(0.0588 * L - 0.296 * S - 15.8);
  if (debug)
    printf("%d <-- INDEX\n\n", index);

  if (index < 1)
    printf("Before Grade 1\n");
  else if (index > 16)
    printf("Grade 16+\n");
  else
    printf("Grade %d\n", index);

  return 0;
}
