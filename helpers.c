#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int average(double totalColour, int noPixels);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of R, G, B
            float blue = (float) image[i][j].rgbtBlue;
            float green = (float) image[i][j].rgbtGreen;
            float red = (float) image[i][j].rgbtRed;
            BYTE average = round((blue + green + red) / 3.0);
            // Apply calculated gray value to outfile.bmp
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Obtain copies of original colour values
            float originalRed = (float) image[i][j].rgbtRed;
            float originalGreen = (float) image[i][j].rgbtGreen;
            float originalBlue = (float) image[i][j].rgbtBlue;
            // Calculate new red value
            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            // Calculate new green value
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            // Calculate new blue value
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Assign new values to outfile.bmp
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
    // Declare temporary RGBTRIPLE to store values
    RGBTRIPLE temp;
    // Calculate mid-width point
    int n = width / 2;
    // Reflect pixels per row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp.rgbtRed;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp.rgbtGreen;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create another matrix to hold average colour values
    RGBTRIPLE(*avg)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (avg == NULL)
    {
        printf("Could not make a new matrix 'avg'.");
        return;
    }

    // Declare common variables for blur function
    double totalBlue = 0;
    double totalGreen = 0;
    double totalRed = 0;
    int pixels = 0;


    // Calculate colour average of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int y = i - 1; y <= i + 1 && y < height; y++)
            {
                // Cannot obtain pixel outside of image matrix (for edge pixels)
                if (y < 0)
                {
                    y = 0;
                }
                for (int x = j - 1; x <= j + 1 && x < width; x++)
                {
                    // Cannot obtain pixel outside of image matrix (for edge pixels)
                    if (x < 0)
                    {
                        x = 0;
                    }
                    totalBlue += image[y][x].rgbtBlue;
                    totalGreen += image[y][x].rgbtGreen;
                    totalRed += image[y][x].rgbtRed;
                    pixels++;
                }
            }
            avg[i][j].rgbtBlue = average(totalBlue, pixels);
            avg[i][j].rgbtGreen = average(totalGreen, pixels);
            avg[i][j].rgbtRed = average(totalRed, pixels);

            // Reset common variables
            totalBlue = 0;
            totalGreen = 0;
            totalRed = 0;
            pixels = 0;
        }
    }

    // Copy over calculated averages to outfile.bmp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = avg[i][j].rgbtBlue;
            image[i][j].rgbtGreen = avg[i][j].rgbtGreen;
            image[i][j].rgbtRed = avg[i][j].rgbtRed;
        }
    }
    free(avg);
    return;
}

// Calculate average for blur function
int average(double totalColour, int noPixels)
{
    int avgColour = round(totalColour / noPixels);
    return avgColour;
}



