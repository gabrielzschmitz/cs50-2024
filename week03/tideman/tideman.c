#include <stdio.h>
#include <stdlib.h>
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
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
  }

  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = 0;
    }
  }

  pair_count = 0;
  int voter_count = -1;
  printf("Number of voters: ");
  scanf("%d", &voter_count);

  for (int i = 0; i < voter_count; i++) {
    int ranks[candidate_count];

    for (int j = 0; j < candidate_count; j++) {
      char *name = (char *)malloc(sizeof(char *) * BUFFERSIZE);
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
  int index = 0;

  for (int i = 0; i < pair_count; i++) {
    index = i;
    for (int j = i + 1; j < pair_count; j++) {
      int strength_of_victory =
        preferences[pairs[index].winner][pairs[index].loser] -
        preferences[pairs[index].loser][pairs[index].winner];
      int current_high = preferences[pairs[j].winner][pairs[j].loser] -
                         preferences[pairs[j].loser][pairs[j].winner];
      if (current_high > strength_of_victory) {
        index = j;
      }
    }
    pair temp = pairs[i];
    pairs[i] = pairs[index];
    pairs[index] = temp;
  }
  return;
}

void lock_pairs(void) {
  for (int i = 0; i < pair_count; i++) {
    if (check_loop(pairs[i].winner, pairs[i].loser))
      continue;
    else
      locked[pairs[i].winner][pairs[i].loser] = 1;
  }
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
