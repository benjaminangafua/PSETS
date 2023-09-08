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

    //Each row of the ladder
    for (int row = 1; row <= height; row ++)
    {
        // Inserting spaces
        for (int spaces = 1; spaces <= height - row; spaces ++)
        { 
                printf(" ");  
        }
        //Inserting hashes
        for (int hash = 1; hash <= row; hash++)
        {
            printf("#");
        }
        // Spaces in between the ladder
        printf(" ");
        printf(" ");

        // The left side of the pyramid
        for (int left_align = 1; left_align <= row; left_align++)
        {
            printf("#");
        }
        // Break after each row
        printf("\n");
    } 
}