#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
     height = get_int("Height: ");
    }
      while (height < 1 || height > 8);

    //Looping rows for each iteration
    for (int row = 0; row < height; row++)
    {
        // Looping the columns
        for (int space = 0; space <= height - row; space++)
        {
             
                printf(" ");
        }
        for (int hash = 0; hash <= row; hash++)
            {
                printf("#");
            }
        printf("\n");
    } 
}