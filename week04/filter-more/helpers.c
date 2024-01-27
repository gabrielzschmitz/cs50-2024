#include "helpers.h"

#include <math.h>

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE temp[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      float sumRed = 0, sumGreen = 0, sumBlue = 0;
      int counter = 0;

      for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
          int ni = i + r;
          int nj = j + c;

          if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
            sumRed += image[ni][nj].rgbtRed;
            sumGreen += image[ni][nj].rgbtGreen;
            sumBlue += image[ni][nj].rgbtBlue;
            counter++;
          }
        }
      }

      temp[i][j].rgbtRed = round(sumRed / counter);
      temp[i][j].rgbtGreen = round(sumGreen / counter);
      temp[i][j].rgbtBlue = round(sumBlue / counter);
    }
  }

  // Update the original image with the blurred values
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = temp[i][j];
    }
  }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE temp[height][width];

  int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int gxRed = 0, gyRed = 0, gxGreen = 0, gyGreen = 0, gxBlue = 0,
          gyBlue = 0;

      for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
          int ni = i + r;
          int nj = j + c;

          if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
            gxRed += image[ni][nj].rgbtRed * gx[r + 1][c + 1];
            gyRed += image[ni][nj].rgbtRed * gy[r + 1][c + 1];
            gxGreen += image[ni][nj].rgbtGreen * gx[r + 1][c + 1];
            gyGreen += image[ni][nj].rgbtGreen * gy[r + 1][c + 1];
            gxBlue += image[ni][nj].rgbtBlue * gx[r + 1][c + 1];
            gyBlue += image[ni][nj].rgbtBlue * gy[r + 1][c + 1];
          }
        }
      }

      int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
      int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
      int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

      temp[i][j].rgbtRed = (red > 255) ? 255 : red;
      temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
      temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
    }
  }

  // Update the original image with the edge-detected values
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = temp[i][j];
    }
  }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int avg = round(
        (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) /
        3.0);
      image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
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
