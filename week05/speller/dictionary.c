// Implements a dictionary's functionality

#include "dictionary.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// Choose number of buckets in hash table
#define N 50000

// Hash table
node *table[N];

int dictionarySize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
  int hashValue = hash(word);
  node *new = table[hashValue];

  while (new != NULL) {
    if (strcasecmp(word, new->word) == 0) return true;
    new = new->next;
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  long sum = 0;
  for (int i = 0; i < strlen(word); i++) sum += tolower(word[i]);
  return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  FILE *dictionaryPointer = fopen(dictionary, "r");
  if (dictionary == NULL) {
    printf("Unable to open %s\n", dictionary);
    return false;
  }

  char next[LENGTH + 1];
  while (fscanf(dictionaryPointer, "%s", next) != EOF) {
    node *new = malloc(sizeof(node));
    if (new == NULL) return false;

    strcpy(new->word, next);
    int hashValue = hash(next);

    new->next = table[hashValue];
    table[hashValue] = new;
    dictionarySize++;
  }

  fclose(dictionaryPointer);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) { return dictionarySize; }

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  for (int i = 0; i < N; i++) {
    node *new = table[i];
    while (new != NULL) {
      node *tmp = new;
      new = new->next;

      free(tmp);
    }
    if (new == NULL && i == N - 1) return true;
  }
  return false;
}
