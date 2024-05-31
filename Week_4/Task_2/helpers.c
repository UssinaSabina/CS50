#include "helpers.h"
#include <math.h>

int min(int num1, int num2);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Take average of red, green, and blue
            int rgb_avg = round((red + green + blue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = rgb_avg;
            image[i][j].rgbtGreen = rgb_avg;
            image[i][j].rgbtBlue = rgb_avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // take original color values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // the sepia color values
            int sepiaRed = min(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue), 255);
            int sepiaGreen = min(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue), 255);
            int sepiaBlue = min(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue), 255);

            // update pixel values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp;
            }
        }
        else
        {
            for (int j = 0; j < width / 2 + 1; j++)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // cumulatives for each color
            int red = 0;
            int green = 0;
            int blue = 0;
            // number of pixels surrounding the current pixel
            float counter = 0.0;
            // go throw all of the pixels that are within 1 row and column of the original pixel (3x3 box)
            for (int x = i - 1; x <= i + 1; x++)
            {
                if ((x < 0) || (x >= height))
                {
                    continue;
                }
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if ((y < 0) || (y >= width))
                    {
                        continue;
                    }
                    red += image[x][y].rgbtRed;
                    green += image[x][y].rgbtGreen;
                    blue += image[x][y].rgbtBlue;
                    counter += 1;
                }
            }
            // average the color values of neighbouring pixels and update pixel values
            copy[i][j].rgbtRed = round(red / counter);
            copy[i][j].rgbtGreen = round(green / counter);
            copy[i][j].rgbtBlue = round(blue / counter);
        }
    }
    // replace original pixels with blured pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// compares two integers abd returns the minimum
int min(int num1, int num2)
{
    return (num1 < num2 ) ? num1 : num2;
}
