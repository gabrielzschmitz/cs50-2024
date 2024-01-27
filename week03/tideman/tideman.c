/*
  Program Description:
  --------------------
  This C program, named tideman.c, simulates an election using the Tideman
  voting method (ranked pairs). The Tideman method is a ranked-choice voting
  system that guarantees the Condorcet winner if one exists. The program
  collects ranked preferences from voters, calculates pairwise preferences,
  sorts the pairs based on preference differences, and determines the winner
  without creating cycles in the preferences.

  Implementation Details:
  -----------------------
  - The program defines a pair structure to represent a pairwise comparison
  between candidates.
  - Arrays are used to store candidate names, preferences, locked pairs, and
  pairs sorted by preference differences.
  - Functions are implemented to register votes, record preferences, add pairs,
  sort pairs, lock pairs without creating cycles, and print the winner.
  - The main function collects voter preferences, calculates and sorts pairs,
  locks pairs, and prints the winner.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./tideman Alice Bob Charlie
  The program prompts for the number of voters and collects ranked preferences
  for each candidate. After processing the preferences, it outputs the winner(s)
  according to the Tideman voting method.

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 100
#define MAX        9

typedef struct {
  int winner;
  int loser;
} pair;

int vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int check_loop(int base, int loser);

int preferences[MAX][MAX];
int locked[MAX][MAX];
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) candidates[i] = argv[i + 1];

  for (int i = 0; i < candidate_count; i++)
    for (int j = 0; j < candidate_count; j++) locked[i][j] = 0;

  pair_count = 0;
  int voter_count = -1;
  printf("Number of voters: ");
  scanf("%d", &voter_count);

  for (int i = 0; i < voter_count; i++) {
    int ranks[candidate_count];

    for (int j = 0; j < candidate_count; j++) {
      char name[BUFFERSIZE];
      printf("Rank %d: ", j + 1);
      scanf("%s", name);

      if (!vote(j, name, ranks)) {
        printf("Invalid vote.\n");
        return 3;
      }
    }
    record_preferences(ranks);

    printf("\n");
  }

  add_pairs();
  sort_pairs();
  lock_pairs();
  print_winner();
  return 0;
}

int vote(int rank, char *name, int ranks[]) {
  for (int i = 0; i < candidate_count; i++)
    if (strcmp(name, candidates[i]) == 0) {
      ranks[rank] = i;
      return 1;
    }
  return 0;
}

void record_preferences(int ranks[]) {
  for (int i = 0; i < candidate_count; i++)
    for (int j = i + 1; j < candidate_count; j++)
      preferences[ranks[i]][ranks[j]] += 1;
  return;
}

void add_pairs(void) {
  for (int i = 0; i < candidate_count; i++) {
    for (int j = i + 1; j < candidate_count; j++) {
      if (preferences[i][j] != preferences[j][i]) {
        if (preferences[i][j] > preferences[j][i]) {
          pairs[pair_count].winner = i;
          pairs[pair_count].loser = j;
        } else {
          pairs[pair_count].winner = j;
          pairs[pair_count].loser = i;
        }
        pair_count++;
      }
    }
  }
  return;
}

void sort_pairs(void) {
  for (int i = 0; i < pair_count; i++) {
    for (int j = i + 1; j < pair_count; j++) {
      int diff1 = preferences[pairs[i].winner][pairs[i].loser] -
                  preferences[pairs[i].loser][pairs[i].winner];
      int diff2 = preferences[pairs[j].winner][pairs[j].loser] -
                  preferences[pairs[j].loser][pairs[j].winner];

      if (diff1 < diff2) {
        pair temp = pairs[i];
        pairs[i] = pairs[j];
        pairs[j] = temp;
      }
    }
  }
  return;
}

void lock_pairs(void) {
  for (int i = 0; i < pair_count; i++)
    if (!check_loop(pairs[i].winner, pairs[i].loser))
      locked[pairs[i].winner][pairs[i].loser] = 1;
  return;
}

int check_loop(int base, int loser) {
  if (loser == base) return 1;

  for (int i = 0; i < candidate_count; i++)
    if (locked[loser][i])
      if (check_loop(base, i)) return 1;

  return 0;
}

void print_winner(void) {
  for (int i = 0; i < candidate_count; i++) {
    int pointed_at = 0;

    for (int j = 0; j < candidate_count; j++)
      if (locked[j][i] == 1) pointed_at = 1;

    if (!pointed_at) printf("%s\n", candidates[i]);
  }

  return;
}
