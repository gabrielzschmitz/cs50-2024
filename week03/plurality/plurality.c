#include <stdio.h>
#include <stdlib.h>
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
void print_votes(void);
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
    char *name = (char *)malloc(sizeof(char *) * BUFFERSIZE);
    printf("Vote: ");
    scanf("%s", name);

    if (!vote(name)) {
      printf("Invalid vote.\n");
    }
  }

  // print_votes();
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

void print_votes(void) {
  printf("\n");
  for (int i = 0; i < candidate_count; i++)
    printf("NAME: %s; VOTES: %d\n", candidates[i].name, candidates[i].votes);
  printf("\n");
  return;
}

void print_winner(void) {
  int maxVote = 0;
  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes > maxVote) maxVote = candidates[i].votes;

  for (int i = 0; i < candidate_count; i++)
    if (candidates[i].votes == maxVote) printf("%s\n", candidates[i].name);
  return;
}
