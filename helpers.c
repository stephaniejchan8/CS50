#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int average(double totalColour, float noPixels);

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
        return;
    }

    // Declare common variables for blur function
    double totalBlue = 0;
    double totalGreen = 0;
    double totalRed = 0;

    // Declare constant variables for calculating average
    const float CORNER = 4.0;
    const float EDGE = 6.0;
    const float CENTRE = 9.0;

    // Calculate colour averages of top left corner pixel
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 1; j++)
        {
            totalBlue += image[i][j].rgbtBlue;
            totalGreen += image[i][j].rgbtGreen;
            totalRed += image[i][j].rgbtRed;
        }
    }
    avg[0][0].rgbtBlue = average(totalBlue, CORNER);
    avg[0][0].rgbtRed = average(totalRed, CORNER);
    avg[0][0].rgbtGreen = average(totalGreen, CORNER);

    // Reset common variables
    totalBlue = 0;
    totalGreen = 0;
    totalRed = 0;

    // Calculate colour averages of top right corner pixel
    for (int i = 0; i <= 1; i++)
    {
        for (int j = width - 2; j < width; j++)
        {
            totalBlue += image[i][j].rgbtBlue;
            totalGreen += image[i][j].rgbtGreen;
            totalRed += image[i][j].rgbtRed;
        }
    }
    avg[0][width - 1].rgbtBlue = average(totalBlue, CORNER);
    avg[0][width - 1].rgbtRed = average(totalRed, CORNER);
    avg[0][width - 1].rgbtGreen = average(totalGreen, CORNER);

    // Reset common variables
    totalBlue = 0;
    totalGreen = 0;
    totalRed = 0;

    // Calculate colour averages of bottom left corner pixel
    for (int i = height - 1; i >= height - 2; i--)
    {
        for (int j = 0; j <= 1; j++)
        {
            totalBlue += image[i][j].rgbtBlue;
            totalGreen += image[i][j].rgbtGreen;
            totalRed += image[i][j].rgbtRed;
        }
    }
    avg[height - 1][0].rgbtBlue = average(totalBlue, CORNER);
    avg[height - 1][0].rgbtRed = average(totalRed, CORNER);
    avg[height - 1][0].rgbtGreen = average(totalGreen, CORNER);

    // Reset common variables
    totalBlue = 0;
    totalGreen = 0;
    totalRed = 0;

    // Calculate colour averages of bottom right corner pixel
    for (int i = height - 1; i >= height - 2; i--)
    {
        for (int j = width - 1; j >= width - 2; j--)
        {
            totalBlue += image[i][j].rgbtBlue;
            totalGreen += image[i][j].rgbtGreen;
            totalRed += image[i][j].rgbtRed;
        }
    }
    avg[height - 1][width - 1].rgbtBlue = average(totalBlue, CORNER);
    avg[height - 1][width - 1].rgbtRed = average(totalRed, CORNER);
    avg[height - 1][width - 1].rgbtGreen = average(totalGreen, CORNER);

    // Reset common variables
    totalBlue = 0;
    totalGreen = 0;
    totalRed = 0;

    // Calculate colour averages of the top border pixels
    for (int j = 1; j < width - 1; j++)
    {
        for (int y = 0; y <= 1; y++)
        {
            for (int x = j - 1; x <= j + 1; x++)
            {
                totalBlue += image[y][x].rgbtBlue;
                totalGreen += image[y][x].rgbtGreen;
                totalRed += image[y][x].rgbtRed;
            }
        }
        avg[0][j].rgbtBlue = average(totalBlue, EDGE);
        avg[0][j].rgbtGreen = average(totalGreen, EDGE);
        avg[0][j].rgbtRed = average(totalRed, EDGE);

        // Reset common variables
        totalBlue = 0;
        totalGreen = 0;
        totalRed = 0;
    }

    // Calculate colour averages of the bottom border pixels
    for (int j = 1; j < width - 1; j++)
    {
        for (int y = height - 1; y >= height - 2; y--)
        {
            for (int x = j - 1; x <= j + 1; x++)
            {
                totalBlue += image[y][x].rgbtBlue;
                totalGreen += image[y][x].rgbtGreen;
                totalRed += image[y][x].rgbtRed;
            }
        }
        avg[height - 1][j].rgbtBlue = average(totalBlue, EDGE);
        avg[height - 1][j].rgbtGreen = average(totalGreen, EDGE);
        avg[height - 1][j].rgbtRed = average(totalRed, EDGE);

        // Reset common variables
        totalBlue = 0;
        totalGreen = 0;
        totalRed = 0;
    }

    // Calculate colour averages of the left border pixels
    for (int i = 1; i < height - 1; i++)
    {
        for (int y = i - 1; y <= i + 1; y++)
        {
            for (int x = 0; x <= 1; x++)
            {
                totalBlue += image[y][x].rgbtBlue;
                totalGreen += image[y][x].rgbtGreen;
                totalRed += image[y][x].rgbtRed;
            }
        }
        avg[i][0].rgbtBlue = average(totalBlue, EDGE);
        avg[i][0].rgbtGreen = average(totalGreen, EDGE);
        avg[i][0].rgbtRed = average(totalRed, EDGE);

        // Reset common variables
        totalBlue = 0;
        totalGreen = 0;
        totalRed = 0;
    }

    // Calculate colour averages of the right border pixels
    for (int i = 1; i < height - 1; i++)
    {
        for (int y = i - 1; y <= i + 1; y++)
        {
            for (int x = width - 1; x >= width - 2; x--)
            {
                totalBlue += image[y][x].rgbtBlue;
                totalGreen += image[y][x].rgbtGreen;
                totalRed += image[y][x].rgbtRed;
            }
        }
        avg[i][width - 1].rgbtBlue = average(totalBlue, EDGE);
        avg[i][width - 1].rgbtGreen = average(totalGreen, EDGE);
        avg[i][width - 1].rgbtRed = average(totalRed, EDGE);

        // Reset common variables
        totalBlue = 0;
        totalGreen = 0;
        totalRed = 0;
    }

    // Calculate colour average of the non-border pixels
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            for (int y = i - 1; y <= i + 1; y++)
            {
                for (int x = j - 1; x <= j + 1; x++)
                {
                    totalBlue += image[y][x].rgbtBlue;
                    totalGreen += image[y][x].rgbtGreen;
                    totalRed += image[y][x].rgbtRed;
                }
            }
            avg[i][j].rgbtBlue = average(totalBlue, CENTRE);
            avg[i][j].rgbtGreen = average(totalGreen, CENTRE);
            avg[i][j].rgbtRed = average(totalRed, CENTRE);

            // Reset common variables
            totalBlue = 0;
            totalGreen = 0;
            totalRed = 0;
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
int average(double totalColour, float noPixels)
{
    int avgColour = round(totalColour / noPixels);
    return avgColour;
}



