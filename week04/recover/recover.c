/*
  Program Description:
  --------------------
  This C program, named recover.c, aims to recover JPEG images from a memory
  card forensic image. The memory card may have JPEG images that were
  accidentally deleted but can potentially be recovered. The program reads the
  forensic image, identifies JPEG signatures in the data, and extracts and saves
  the JPEG files.

  Implementation Details:
  -----------------------
  - The program takes one command-line argument: the name of the forensic image
  file (e.g., forensicimage).
  - It opens the forensic image file and reads the data in blocks of 512 bytes.
  - For each block, it checks for the JPEG signature, which consists of the
  bytes 0xff, 0xd8, and 0xff at specific positions in the block.
  - If a JPEG signature is found, the program creates a new JPEG file and writes
  the corresponding block to it.
  - The recovered JPEG files are named sequentially as "000.jpg," "001.jpg," and
  so on.
  - Proper error handling is implemented for file opening and memory allocation.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./recover forensicimage
  The program reads the forensicimage file, identifies JPEG signatures, and
  recovers the JPEG files, saving them as "000.jpg," "001.jpg," and so on.

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

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

  uint8_t buffer[BLOCK_SIZE];
  FILE *imagePointer = NULL;
  char fileName[8];
  int recoveredImages = 0;

  while (fread(buffer, BLOCK_SIZE, 1, image) == 1) {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] >= 0xe0 && buffer[3] <= 0xef)) {
      if (imagePointer != NULL) fclose(imagePointer);

      sprintf(fileName, "%03i.jpg", recoveredImages);
      imagePointer = fopen(fileName, "w");

      if (imagePointer == NULL) {
        printf("Could not create %s\n", fileName);
        fclose(image);
        return 1;
      }

      recoveredImages++;
    }

    if (imagePointer != NULL) fwrite(buffer, BLOCK_SIZE, 1, imagePointer);
  }
  if (imagePointer != NULL) fclose(imagePointer);
  fclose(image);

  return 0;
}
