/*
  Program Description:
  --------------------
  This C program, named plurality.c, implements a plurality election. The
  program runs a simple election where voters vote for one candidate each, and
  the candidate with the highest number of votes is declared the winner.

  Implementation Details:
  -----------------------
  - The program defines a candidate structure with attributes "name" and
  "votes."
  - The main function initializes an array of candidates based on the
  command-line arguments, sets their initial votes to 0, and prompts the user
  for the number of voters.
  - The vote function takes a voter's choice and increments the vote count for
  the corresponding candidate.
  - The print_winner function determines and prints the winner(s) by identifying
  the candidate(s) with the highest number of votes.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./plurality Alice Bob Charlie
  The program prompts for the number of voters, and if the user enters "3" and
  votes for Alice, Bob, and Charlie, the program outputs:
  "Alice\n"
  "Bob\n"
  "Charlie\n"

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 100
#define MAX        9

typedef struct {
  char *name;
  int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

int vote(char *name);
void print_winner(void);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: plurality [candidate ...]\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
  }

  int voter_count = -1;
  printf("Number of voters: ");
  scanf("%d", &voter_count);

  for (int i = 0; i < voter_count; i++) {
    char name[BUFFERSIZE];
    printf("Vote: ");
    scanf("%s", name);

    if (!vote(name)) printf("Invalid vote.\n");
  }

  print_winner();
  return 0;
}

int vote(char *name) {
  for (int i = 0; i < candidate_count; i++)
    if (strcmp(name, candidates[i].name) == 0) {
      candidates[i].votes += 1;
      return 1;
    }
  return 0;
}

void print_winner(void) {
  int maxVote = 0;
  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes > maxVote) maxVote = candidates[i].votes;

  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes == maxVote) printf("%s\n", candidates[i].name);
  return;
}
