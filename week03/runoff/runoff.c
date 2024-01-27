/*
  Program Description:
  --------------------
  This C program, named runoff.c, simulates a ranked-choice voting (instant
  runoff) election. The program allows voters to rank candidates in order of
  preference, and it iteratively eliminates candidates with the fewest votes
  until a candidate receives more than 50% of the votes.

  Implementation Details:
  -----------------------
  - The program defines a candidate structure with attributes "name," "votes,"
  and "eliminated."
  - An array 'preferences' is used to store the ranked preferences of each
  voter.
  - The main function initializes the candidates based on command-line
  arguments, prompts for the number of voters, and collects the ranked
  preferences from each voter.
  - The program iteratively tabulates votes, checks for a winner, finds the
  candidate with the fewest votes, and eliminates candidates in case of a tie.
  - The simulation continues until a candidate receives more than 50% of the
  votes or a tie occurs.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./runoff Alice Bob Charlie
  The program prompts for the number of voters, and if the user enters "3" and
  provides ranked preferences for each candidate, the program outputs the winner
  or a tie result.

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE     100
#define MAX_VOTERS     100
#define MAX_CANDIDATES 9

typedef struct {
  char *name;
  int votes;
  int eliminated;
} candidate;

int preferences[MAX_VOTERS][MAX_CANDIDATES];
candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;

int vote(int voter, int rank, char *name);
void tabulate(void);
int print_winner(void);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES) {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i].eliminated = 0;
  }

  voter_count = -1;
  printf("Number of voters: ");
  scanf("%d", &voter_count);
  if (voter_count > MAX_VOTERS) {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  for (int i = 0; i < voter_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      char name[BUFFERSIZE];
      printf("Rank %d: ", j + 1);
      scanf("%s", name);

      if (!vote(i, j, name)) {
        printf("Invalid vote.\n");
        return 4;
      }
    }

    printf("\n");
  }

  while (1) {
    tabulate();

    int won = print_winner();
    if (won) break;

    int min = find_min();
    int tie = is_tie(min);

    if (tie) {
      for (int i = 0; i < candidate_count; i++)
        if (!candidates[i].eliminated) printf("%s\n", candidates[i].name);
      break;
    }

    eliminate(min);

    for (int i = 0; i < candidate_count; i++) candidates[i].votes = 0;
  }
  return 0;
}

int vote(int voter, int rank, char *name) {
  for (int i = 0; i < candidate_count; i++)
    if (strcmp(name, candidates[i].name) == 0) {
      preferences[voter][rank] = i;
      return 1;
    }
  return 0;
}

void tabulate(void) {
  for (int i = 0; i < voter_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      int c = preferences[i][j];
      if (!candidates[c].eliminated) {
        candidates[c].votes++;
        break;
      }
    }
  }
}

int print_winner(void) {
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated && candidates[i].votes > voter_count / 2) {
      printf("%s\n", candidates[i].name);
      return 1;
    }
  }
  return 0;
}

int find_min(void) {
  int minimum = MAX_VOTERS;
  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes < minimum && !candidates[i].eliminated)
      minimum = candidates[i].votes;
  return minimum;
}

int is_tie(int min) {
  int candidatesRemaining = 0;
  int candidatesTied = 0;
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated) candidatesRemaining += 1;
    if (candidates[i].votes == min && !candidates[i].eliminated)
      candidatesTied += 1;
  }
  return candidatesTied == candidatesRemaining;
}

void eliminate(int min) {
  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes == min && !candidates[i].eliminated)
      candidates[i].eliminated = 1;
  return;
}
