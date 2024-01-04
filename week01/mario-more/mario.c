#include <stdio.h>

int main(void) {
  int height = -1;
  do {
    printf("Height: ");
    scanf("%d", &height);
  } while (height < 1 || height > 8);
  height -= 1;

  for (int rowLeft = 0; rowLeft <= height; rowLeft++) {
    for (int column = 0; column <= height; column++) {
      if (rowLeft + column >= height)
        printf("#");
      else
        printf(" ");
    }
    printf("  ");

    int rowRight = height - rowLeft;
    for (int column = 0; column <= height; column++) {
      if (rowRight + column <= height)
        printf("#");
    }
    printf("\n");
  }
}
