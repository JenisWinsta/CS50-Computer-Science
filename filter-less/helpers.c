#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            int red= image[i][j].rgbtRed;
            int green= image[i][j].rgbtGreen;
            int blue= image[i][j].rgbtBlue;

            int avg=round((red+green+blue)/3.0);
            // printf("%i",avg);

            image[i][j].rgbtRed=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtBlue=avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            float red= image[i][j].rgbtRed;
            float green= image[i][j].rgbtGreen;
            float blue= image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            if(sepiaRed>255){
                sepiaRed=255;
            }
            if(sepiaGreen>255){
                sepiaGreen=255;
            }
            if(sepiaBlue>255){
                sepiaBlue=255;
            }

            image[i][j].rgbtRed=sepiaRed;
            image[i][j].rgbtGreen=sepiaGreen;
            image[i][j].rgbtBlue=sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height; i++){
        for(int j=0; j<width/2; j++){
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redSum = 0, greenSum = 0, blueSum = 0;
            int counter = 0;

            // Loop through the surrounding pixels in a 3x3 grid
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di; // Neighbor row index
                    int nj = j + dj; // Neighbor column index

                    // Check if the neighbor is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        redSum += copy[ni][nj].rgbtRed;
                        greenSum += copy[ni][nj].rgbtGreen;
                        blueSum += copy[ni][nj].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Calculate the average for each color channel
            image[i][j].rgbtRed = round(redSum / counter);
            image[i][j].rgbtGreen = round(greenSum / counter);
            image[i][j].rgbtBlue = round(blueSum / counter);
        }
    }

    return;
}
