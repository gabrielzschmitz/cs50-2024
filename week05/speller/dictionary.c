/*
  Program Description:
  --------------------
  This C program, implemented in the file dictionary.c, spell-checks a text file
  using a hash table. The program is designed to work in conjunction with the
  dictionary.h header file. It provides functions to load a dictionary into
  memory, check if a word is in the dictionary, retrieve the number of words in
  the dictionary, and unload the dictionary from memory.

  Implementation Details:
  -----------------------
  - The program defines a node structure representing a node in the hash table.
  Each node contains a word and a pointer to the next node.
  - The hash table is an array of linked lists (buckets), and the number of
  buckets is determined by the constant N.
  - The check function searches for a word in the hash table, ignoring case, and
  returns true if the word is found, else false.
  - The hash function generates a hash value for a word using a simple algorithm
  involving bitwise left shifts.
  - The load function loads a dictionary file into memory, creating nodes for
  each word and organizing them in the hash table.
  - The size function returns the number of words in the dictionary.
  - The unload function frees the allocated memory for the hash table, including
  all nodes in the linked lists.

  Usage:
  ------
  To use the spell-checker program, include the dictionary.h header file and
  call the provided functions in your main program. The program expects the
  dictionary file to be in a specified format.

  Note: Ensure proper compilation and linking with the dictionary.h header file
  for the desired functionality.
*/
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
  node *current = table[hashValue];

  while (current != NULL) {
    if (strcasecmp(word, current->word) == 0) return true;
    current = current->next;
  }
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
  unsigned int hashValue = 0;
  for (int i = 0; word[i] != '\0'; i++)
    hashValue = (hashValue << 2) ^ tolower(word[i]);
  return hashValue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  FILE *dictionaryPointer = fopen(dictionary, "r");
  if (dictionaryPointer == NULL) {
    fprintf(stderr, "Unable to open %s\n", dictionary);
    return false;
  }

  char next[LENGTH + 1];
  while (fscanf(dictionaryPointer, "%s", next) != EOF) {
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
      fclose(dictionaryPointer);
      return false;
    }

    strcpy(newNode->word, next);
    int hashValue = hash(next);

    newNode->next = table[hashValue];
    table[hashValue] = newNode;
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
