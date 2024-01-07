#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./recover forensicimage\n");
    return 1;
  }

  FILE *image = fopen(argv[1], "r");
  if (image == NULL) {
    printf("Could not open %s\n", argv[1]);
    return 1;
  }

  uint8_t buffer[512];
  int recoveredImages = 0;
  FILE *imagePointer = NULL;
  char fileName[8];

  while (fread(&buffer, 512, 1, image) == 1) {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] >= 0xe0 || buffer[3] <= 0xef)) {
      if (!(recoveredImages == 0)) fclose(imagePointer);
      sprintf(fileName, "%03i.jpg", recoveredImages);
      imagePointer = fopen(fileName, "w");
      if (imagePointer == NULL) {
        printf("Could not create %s\n", argv[1]);
        return 1;
      }
      recoveredImages++;
    }
    if (!(recoveredImages == 0)) fwrite(&buffer, 512, 1, imagePointer);
  }
  fclose(imagePointer);
  fclose(image);

  return 0;
}
