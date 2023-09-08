#include "helpers.h"
#include <maths.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp = image[i][j];
            int red = temp.rgbRed;
            int green = temp.rgbGreen;
            int blue = temp.rgbBlue;

            //Calculate average pixel value
            int average = round(red + green + blue / 3);

            //setting the average color value
            image[i][j].rgbRed = average;
            image[i][j].rgbGreen = average;
            image[i][j].rgbBlue = average;
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
            RGBTRIPLE temp = image[i][j];
            int red = temp.rgbRed;
            int green = temp.rgbGreen;
            int blue = temp.rgbBlue;

            int sepiaRed = round((0.393 * temp.rgbRed) + (0.769 * temp.rgbGreen) + (0.189 * temp.rgbBlue));
            int sepiaGreen = round((0.349 * temp.rgbRed) + (0.686 * temp.rgbGreen) + (0.168 * temp.rgbBlue));
            int sepiaBlue = round((0.272 * temp.rgbRed) + (0.534 * temp.rgbGreen) + (0.131 * temp.rgbBlue));

            (sepiaRed > 255)? image[i][j].rgbRed = 255 : image[i][j].rgbRed = sepiaRed; 
            (sepiaGreen > 255)? image[i][j].rgbGreen = 255 : image[i][j].rgbGreen = sepiaGreen; 
            (sepiaBlue > 255)? image[i][j].rgbBlue = 255 : image[i][j].rgbBlue = sepiaBlue; 
        } 
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
/*
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void swapImgPixel(RGBTRIPLE *x1, RGBTRIPLE *x2);
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE color =  image[i][j];

            int red = color.rgbtRed;
            int green = color.rgbtGreen;
            int blue = color.rgbtBlue;

            int average =  round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            RGBTRIPLE color =  image[i][j];

            int red = color.rgbtRed;
            int green = color.rgbtGreen;
            int blue = color.rgbtBlue;

            //sepia formula
            int newRedSepia = round((0.393 * red) + (0.769 * green) + (0.189 * blue));

            int newGreenSepia = round((0.349 * red) + (0.686 * green) + (0.168 * blue));

            int newBlueSepia = round((0.272 * red) + (0.534 * green) + (0.131 * blue));

            //sepia integer between 0 - 255
            if (newRedSepia > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = newRedSepia;
            }

            if (newGreenSepia > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = newGreenSepia;
            }

            if (newBlueSepia > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = newBlueSepia;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // RGBTRIPLE color =  image[i][j];

            swapImgPixel(&image[i][j], &image[i][width - 1 - j]);
        }
    }

    return;
}

void swapImgPixel(RGBTRIPLE *x1, RGBTRIPLE *x2)
{
    RGBTRIPLE buff = *x1;
    *x1 = *x2;
    *x2 = buff;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;

}
*/