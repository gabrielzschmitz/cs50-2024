#include <stdio.h>
#define BUFFERSIZE 100

int main(void) {
  char name[BUFFERSIZE];

  printf("What's your name? ");
  scanf("%s", name);

  printf("hello, %s\n", name);

  return 0;
}
