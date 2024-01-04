#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 100
#define ALPHABET 26

int debug = 0;

int calculateScore(int *points, char *scramble) {
  int score = 0;
  int length = strlen(scramble);

  for (int i = 0; i < length; i++) {
    char current = tolower(scramble[i]);
    if (isalpha(current))
      score += points[current - 97];
  }

  return score;
}

int main(void) {
  int points[ALPHABET] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                          1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  if (debug)
    for (int i = 0; i < sizeof(points) / sizeof(int); i++)
      printf("%d: %d\n", i, points[i]);

  char *player1 = (char *)malloc(sizeof(char *) * BUFFERSIZE);
  char *player2 = (char *)malloc(sizeof(char *) * BUFFERSIZE);
  printf("Player 1: ");
  scanf("%s", player1);
  printf("Player 2: ");
  scanf("%s", player2);

  if (debug) {
    printf("\n\n%s\n", player1);
    printf("%s\n", player2);
  }

  int score1 = calculateScore(points, player1);
  int score2 = calculateScore(points, player2);

  if (score1 > score2)
    printf("Player 1 wins!");
  else if (score1 < score2)
    printf("Player 2 wins!");
  else
    printf("Tie!");
  return 0;
}
