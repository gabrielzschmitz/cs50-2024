/*
  Program Description:
  --------------------
  This C program, named scrabble.c, is located in the "scrabble" folder. It
  determines the winner of a short Scrabble-like game by calculating the scores
  of two players' words. The program prompts each player to input their word,
  calculates the scores based on the Scrabble letter values, and then declares
  the winner or a tie.

  Implementation Details:
  -----------------------
  - The program defines an array 'points' representing the point values for each
  letter in the alphabet.
  - The calculateScore function takes the letter points array and a player's
  word, calculates the score, and returns it.
  - The main function prompts "Player 1" and "Player 2" to input their words,
  calculates their scores, and compares the scores to determine the winner or a
  tie.
  - The scores are calculated by iterating through each character in the input
  words, converting to lowercase, and accumulating the corresponding letter
  points.
  - The program then prints the result, either "Player 1 wins!", "Player 2
  wins!", or "Tie!".

  Usage Example:
  --------------
  Suppose "Player 1" inputs the word "CODE" and "Player 2" inputs the word
  "QUIZ". The program will output: "Player 2 wins!"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 100
#define ALPHABET   26

int calculateScore(int *points, char *scramble) {
  int score = 0;
  int length = strlen(scramble);

  for (int i = 0; i < length; i++) {
    char current = tolower(scramble[i]);
    if (isalpha(current)) score += points[current - 'a'];
  }

  return score;
}

int main(void) {
  int points[ALPHABET] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                          1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  char player1[BUFFERSIZE];
  char player2[BUFFERSIZE];

  printf("Player 1: ");
  scanf("%s", player1);
  printf("Player 2: ");
  scanf("%s", player2);

  int score1 = calculateScore(points, player1);
  int score2 = calculateScore(points, player2);

  if (score1 > score2)
    printf("Player 1 wins!\n");
  else if (score1 < score2)
    printf("Player 2 wins!\n");
  else
    printf("Tie!\n");

  return 0;
}
