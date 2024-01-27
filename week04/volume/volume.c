/*
  Program Description:
  --------------------
  This C program, named volume.c, allows users to modify the volume of an audio
  file in WAV format. WAV files store audio as a sequence of samples, each
  represented by a 2-byte (16-bit) integer. The program reads the input WAV
  file, applies a scaling factor to each sample, and writes the modified audio
  data to the output WAV file. The user specifies the input file, output file,
  and the scaling factor via command-line arguments.

  Implementation Details:
  -----------------------
  - The program takes three command-line arguments: input.wav (the original
  audio file), output.wav (the modified audio file), and a scaling factor.
  - It opens the input and output files and reads the WAV header (first 44
  bytes) from the input file.
  - The scaling factor is applied to each audio sample, adjusting the volume of
  the audio.
  - The modified audio data is written to the output file, preserving the
  original WAV header.
  - Proper error handling is implemented for file opening and argument
  validation.

  Usage Example:
  --------------
  Suppose the user executes the program with the following command:
  ./volume input.wav output.wav 1.5
  The program reads the input.wav file, multiplies each audio sample by 1.5 to
  increase the volume, and writes the modified audio data to the output.wav
  file.

  Note: Ensure proper compilation and execution for the desired functionality.
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./volume input.wav output.wav factor\n");
    return 1;
  }

  FILE *input = fopen(argv[1], "rb");
  if (input == NULL) {
    printf("Could not open file.\n");
    return 1;
  }
  FILE *output = fopen(argv[2], "wb");
  if (output == NULL) {
    printf("Could not open file.\n");
    return 1;
  }
  float factor = atof(argv[3]);

  uint8_t header[HEADER_SIZE];
  fread(header, HEADER_SIZE, 1, input);
  fwrite(header, HEADER_SIZE, 1, output);

  int16_t buffer;
  while (fread(&buffer, sizeof(int16_t), 1, input)) {
    buffer *= factor;
    fwrite(&buffer, sizeof(int16_t), 1, output);
  }

  fclose(input);
  fclose(output);

  return 0;
}
