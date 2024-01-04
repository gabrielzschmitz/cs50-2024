#include <stdio.h>

int main(void) {
  int height = -1;
  do {
    printf("Height: ");
    scanf("%d", &height);
  } while (height < 1 || height > 8);

  for (int row = 0; row < height; row++) {
    for (int column = 0; column < height; column++) {
      if (row + column >= height - 1)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }
}
