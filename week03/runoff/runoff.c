#include <stdio.h>
#include <stdlib.h>
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
void print_votes(void);
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
      char *name = (char *)malloc(sizeof(char *) * BUFFERSIZE);
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
      for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    eliminate(min);

    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
  // print_votes();
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

void print_votes(void) {
  printf("\n");
  for (int i = 0; i < candidate_count; i++)
    printf("NAME: %s; VOTES: %d\n", candidates[i].name, candidates[i].votes);
  printf("\n");
  return;
}

void tabulate(void) {
  for (int i = 0; i < voter_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      int c = preferences[i][j];
      if (candidates[c].eliminated == 0) {
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
  int minimumCandidate = -1;
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes < minimum && !candidates[i].eliminated) {
      minimum = candidates[i].votes;
    }
  }
  if (minimum != MAX_VOTERS) return minimum;
  return 0;
}

int is_tie(int min) {
  int candidatesRemaining = 0;
  int candidatesTied = 0;
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated) candidatesRemaining += 1;
    if (candidates[i].votes == min && !candidates[i].eliminated)
      candidatesTied += 1;
  }
  if (candidatesTied == candidatesRemaining)
    return 1;
  else
    return 0;
}

void eliminate(int min) {
  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes == min && !candidates[i].eliminated)
      candidates[i].eliminated = 1;
  return;
}
