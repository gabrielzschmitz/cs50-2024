#include "helpers.h"

#include <math.h>

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE temp[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      float sumRed = 0;
      float sumGreen = 0;
      float sumBlue = 0;
      float counter = 0;

      for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c++) {
          if (i + r < 0 || i + r > height - 1) continue;
          if (j + c < 0 || j + c > width - 1) continue;

          sumRed += image[i + r][j + c].rgbtRed;
          sumGreen += image[i + r][j + c].rgbtGreen;
          sumBlue += image[i + r][j + c].rgbtBlue;
          counter++;
        }
      }

      temp[i][j].rgbtRed = round(sumRed / counter);
      temp[i][j].rgbtGreen = round(sumGreen / counter);
      temp[i][j].rgbtBlue = round(sumBlue / counter);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j].rgbtRed = temp[i][j].rgbtRed;
      image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
      image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE temp[height][width];

  int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int gxRed = 0;
      int gyRed = 0;
      int gxGreen = 0;
      int gyGreen = 0;
      int gxBlue = 0;
      int gyBlue = 0;

      for (int r = -1; r < 2; r++) {
        for (int c = -1; c < 2; c++) {
          if (i + r < 0 || i + r > height - 1) continue;
          if (j + c < 0 || j + c > width - 1) continue;

          gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
          gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
          gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
          gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
          gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
          gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
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

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j].rgbtRed = temp[i][j].rgbtRed;
      image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
      image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
    }
  }

  return;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int rgbt = round(
        (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) /
        3.0);
      image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = rgbt;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    if (width % 2 == 0) {
      for (int j = 0; j < width / 2; j++) {
        RGBTRIPLE temp[height][width];
        temp[i][j] = image[i][j];
        image[i][j] = image[i][width - (j + 1)];
        image[i][width - (j + 1)] = temp[i][j];
      }
    } else {
      for (int j = 0; j < (width - 1) / 2; j++) {
        RGBTRIPLE temp[height][width];
        temp[i][j] = image[i][j];
        image[i][j] = image[i][width - (j + 1)];
        image[i][width - (j + 1)] = temp[i][j];
      }
    }
  }
  return;
}
