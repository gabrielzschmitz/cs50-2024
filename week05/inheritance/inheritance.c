/*
  Program Description:
  --------------------
  This C program, named inheritance.c, simulates the inheritance of blood types
  for each member of a family over multiple generations. The program models the
  random passing of alleles from parents to children, considering the possible
  blood type combinations: OO, OA, OB, AO, AA, AB, BO, BA, and BB.

  Implementation Details:
  -----------------------
  - The program defines a structure called "person," representing an individual
  in the family. Each person has two parents and two alleles (blood type genes).
  - The function create_family(generations) dynamically allocates memory for a
  person and recursively creates a family tree with specified generations. It
  randomly assigns alleles for each person based on the alleles of their
  parents.
  - The function free_family(p) frees the dynamically allocated memory for the
  family tree.
  - The function print_family(p, generation) recursively prints the family tree,
  displaying each person's blood type and generation.
  - The main function initializes the random seed, creates a family with three
  generations, prints the family tree, and frees the allocated memory.

  Usage:
  ------
  To use the program, compile the source code and execute the resulting
  executable. The program will simulate the inheritance of blood types in a
  family tree and display the results.

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GENERATIONS   3
#define INDENT_LENGTH 4

typedef struct person {
  struct person *parents[2];
  char alleles[2];
} person;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void) {
  srand(time(NULL));

  person *p = create_family(GENERATIONS);
  print_family(p, 0);
  free_family(p);

  return 0;
}

person *create_family(int generations) {
  person *newPerson = (person *)malloc(sizeof(person));

  if (generations > 1) {
    person *parent0 = create_family(generations - 1);
    person *parent1 = create_family(generations - 1);
    newPerson->parents[0] = parent0;
    newPerson->parents[1] = parent1;
    newPerson->alleles[0] = parent0->alleles[rand() % 2];
    newPerson->alleles[1] = parent1->alleles[rand() % 2];
  } else {
    newPerson->parents[0] = NULL;
    newPerson->parents[1] = NULL;
    newPerson->alleles[0] = random_allele();
    newPerson->alleles[1] = random_allele();
  }

  return newPerson;
}

void free_family(person *p) {
  if (p == NULL) {
    return;
  }

  free_family(p->parents[0]);
  free_family(p->parents[1]);
  free(p);
}

void print_family(person *p, int generation) {
  if (p == NULL) {
    return;
  }

  for (int i = 0; i < generation * INDENT_LENGTH; i++) {
    printf(" ");
  }

  if (generation == 0) {
    printf("Child (Generation %i): blood type %c%c\n", generation,
           p->alleles[0], p->alleles[1]);
  } else if (generation == 1) {
    printf("Parent (Generation %i): blood type %c%c\n", generation,
           p->alleles[0], p->alleles[1]);
  } else {
    for (int i = 0; i < generation - 2; i++) {
      printf("Great-");
    }
    printf("Grandparent (Generation %i): blood type %c%c\n", generation,
           p->alleles[0], p->alleles[1]);
  }

  print_family(p->parents[0], generation + 1);
  print_family(p->parents[1], generation + 1);
}

char random_allele() {
  int r = rand() % 3;
  return (r == 0) ? 'A' : (r == 1) ? 'B' : 'O';
}
