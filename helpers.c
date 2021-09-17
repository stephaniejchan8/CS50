#include "helpers.h"
#include <math.h>

int avgB(double sumColour, float pixels);
int Sobel(double sumColourX, double sumColourY);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of red, green, blue values per pixel
            gray = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            //  Apply average values to red, green, blue values per pixel
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary pixel to store values
    RGBTRIPLE temp;
    // Calculate halfway width to determine which pixels to reflect per row
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            // Calculate which pixel position to reflect with
            int swap = width - j - 1;
            // Assign left pixel's values to temp pixel
            temp.rgbtRed = image[i][j].rgbtRed;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            // Assign right pixel's values to left pixel
            image[i][j].rgbtRed = image[i][swap].rgbtRed;
            image[i][j].rgbtBlue = image[i][swap].rgbtBlue;
            image[i][j].rgbtGreen = image[i][swap].rgbtGreen;
            // Assign left pixel's values via the temp pixel to right pixel
            image[i][swap].rgbtRed = temp.rgbtRed;
            image[i][swap].rgbtBlue = temp.rgbtBlue;
            image[i][swap].rgbtGreen = temp.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image to store average blur pixels
    RGBTRIPLE temp[height][width];

    // Create temporary variables to store sum of red, green and blue values
    double sumRed = 0;
    double sumBlue = 0;
    double sumGreen = 0;
    float pixels = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate averages per pixel within 1 row and 1 column
            for (int y = i - 1; y <= i + 1 && y < height; y++)
            {
                // Ensure looking for vertical values within the image's height
                if (y < 0)
                {
                    y = 0;
                }
                for (int x = j - 1; x <= j + 1 && x < width; x++)
                {
                    // Ensure looking for horizonal values within the image's width
                    if (x < 0)
                    {
                        x = 0;
                    }
                    sumRed += image[y][x].rgbtRed;
                    sumBlue += image[y][x].rgbtBlue;
                    sumGreen += image[y][x].rgbtGreen;
                    pixels++;
                }
            }
            // Assign average colour values to temp image's pixels
            temp[i][j].rgbtRed = avgB(sumRed, pixels);
            temp[i][j].rgbtGreen = avgB(sumGreen, pixels);
            temp[i][j].rgbtBlue = avgB(sumBlue, pixels);

            // Reset sum and pixel count variables
            sumRed = 0;
            sumBlue = 0;
            sumGreen = 0;
            pixels = 0;
        }
    }

    // Copy average colour values to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary image to store values
    RGBTRIPLE edge[height][width];

    // Create temporary multiplier variables for Gx
    float multx[3][3];
    multx[0][0] = -1.0;
    multx[0][1] = 0;
    multx[0][2] = 1;
    multx[1][0] = -2.0;
    multx[1][1] = 0;
    multx[1][2] = 2.0;
    multx[2][0] = -1.0;
    multx[2][1] = 0;
    multx[2][2] = 1.0;
    int YM = 0;
    int XM = 0;

    // Create temporary multiplier variables for Gy
    float multy[3][3];
    multy[0][0] = -1.0;
    multy[0][1] = -2.0;
    multy[0][2] = -1.0;
    multy[1][0] = 0;
    multy[1][1] = 0;
    multy[1][2] = 0;
    multy[2][0] = 1.0;
    multy[2][1] = 2.0;
    multy[2][2] = 1.0;

    // Create temporary variables to store sum values
    double sumRedX = 0;
    double sumBlueX = 0;
    double sumGreenX = 0;
    double sumRedY = 0;
    double sumBlueY = 0;
    double sumGreenY = 0;

    // Calculate Gx and Gy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int y = i - 1; y <= i + 1 && y < height; y++)
            {
                for (int x = j - 1; x <= j + 1 && x < width; x++)
                {
                    // Equivalent to applying black border around vertical border
                    if (y < 0)
                    {
                        y = 0;
                        YM = 1;
                    }

                    // Equivalent to applying black border around horizontal border
                    if (x < 0)
                    {
                        x = 0;
                        XM = 1;
                    }
                    sumRedX = sumRedX + (image[y][x].rgbtRed * multx[YM][XM]);
                    sumRedY = sumRedY + (image[y][x].rgbtRed * multy[YM][XM]);
                    sumBlueX = sumBlueX + (image[y][x].rgbtBlue * multx[YM][XM]);
                    sumBlueY = sumBlueY + (image[y][x].rgbtBlue * multy[YM][XM]);
                    sumGreenX = sumGreenX + (image[y][x].rgbtGreen * multx[YM][XM]);
                    sumGreenY = sumGreenY + (image[y][x].rgbtGreen * multy[YM][XM]);
                    XM++;
                }
                YM++;
            }
            // Assign Sobel values per colour to "edge" copy of image
            edge[i][j].rgbtRed = Sobel(sumRedX, sumRedY);
            edge[i][j].rgbtBlue = Sobel(sumBlueX, sumBlueY);
            edge[i][j].rgbtGreen = Sobel(sumGreenX, sumGreenY);

            // Reset variables
            XM = 0;
            YM = 0;
            sumRedX = 0;
            sumBlueX = 0;
            sumGreenX = 0;
            sumRedY = 0;
            sumBlueY = 0;
            sumGreenY = 0;
        }
    }

    // Assign "edge" image pixels to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edge[i][j].rgbtRed;
            image[i][j].rgbtBlue = edge[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edge[i][j].rgbtGreen;
        }
    }
    return;
}

// Calculate average value for "blur" filter
int avgB(double sumColour, float pixels)
{
    int average = round(sumColour / pixels);
    return average;
}

// Sobel algorithm for "edge" filter
int Sobel(double sumColourX, double sumColourY)
{
    // Declare constant integer to apply power of 2
    const int TWO = 2;
    int n = round(sqrt(pow(sumColourX, TWO) + pow(sumColourY, TWO)));

    // Ensure value is >= zero
    if (n <= 0)
    {
        return 0;
    }
    // Ensure value is <= 255
    else if (n >= 255)
    {
        return 255;
    }
    else
    {
        return n;
    }
}
