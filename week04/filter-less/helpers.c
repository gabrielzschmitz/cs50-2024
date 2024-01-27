#include "helpers.h"

#include <math.h>

// Average of three colors
int average(int a, int b, int c) { return round((a + b + c) / 3.0); }

// Cap the color values to be within the valid range [0, 255]
int cap(int value) { return (value > 255) ? 255 : (value < 0) ? 0 : value; }

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int avg = average(image[i][j].rgbtRed, image[i][j].rgbtGreen,
                        image[i][j].rgbtBlue);
      image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
    }
  }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int sepiaRed =
        cap(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                  .189 * image[i][j].rgbtBlue));
      int sepiaGreen =
        cap(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                  .168 * image[i][j].rgbtBlue));
      int sepiaBlue =
        cap(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                  .131 * image[i][j].rgbtBlue));

      image[i][j].rgbtRed = sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue;
    }
  }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width / 2; j++) {
      RGBTRIPLE temp = image[i][j];
      image[i][j] = image[i][width - 1 - j];
      image[i][width - 1 - j] = temp;
    }
  }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE temp[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int sumRed = 0, sumGreen = 0, sumBlue = 0;
      int counter = 0;

      for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
          if (i + r >= 0 && i + r < height && j + c >= 0 && j + c < width) {
            sumRed += image[i + r][j + c].rgbtRed;
            sumGreen += image[i + r][j + c].rgbtGreen;
            sumBlue += image[i + r][j + c].rgbtBlue;
            counter++;
          }
        }
      }

      temp[i][j].rgbtRed = round(sumRed / (float)counter);
      temp[i][j].rgbtGreen = round(sumGreen / (float)counter);
      temp[i][j].rgbtBlue = round(sumBlue / (float)counter);
    }
  }

  // Update the original image with the blurred values
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = temp[i][j];
    }
  }
}
