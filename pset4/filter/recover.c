#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define BYTE_SIZE 512

int main(int argc, char *argv[])
{
    //validate command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open file from command-line argument to read
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    BYTE buff[BYTE_SIZE];
    size_t bytesRead;
    size_t written_file;

    int FIRST_JPEG = 0;
    int FIND_JPEG = 0;

    FILE *img_file;
    char new_img_file[BYTE_SIZE];
    int count_file = 0;


    //open memory card
    //Repeat until end of card
    while (true)
    {
        //Read 512 bytes inot buffer
        bytesRead = fread(buff, sizeof(BYTE), BYTE_SIZE, file);

        if (bytesRead == 0)
        {
            break; //end of file
        }

        //If start a new  jpeg
        if ((buff[0] == 0xff) && (buff[1] == 0xd8) && (buff[2] == 0xff) && (buff[3] & 0xf0) == 0xe0)
        {
            FIND_JPEG = 1;
            //if firt jpeg
            //mark first jpeg
            if (!FIRST_JPEG)
            {
                FIRST_JPEG = 1;

            }
            else
            {
                //else close the current file beign written to, open new file
                fclose(img_file);
            }
            // Create new image beginning with 000.jpeg
            sprintf(new_img_file, "%03i.jpg", count_file);
            img_file = fopen(new_img_file, "w");
            written_file = fwrite(buff, sizeof(BYTE), bytesRead, img_file);
            count_file++;
        }
        else
        {
            // else if already found, keep writing to it
            if (FIND_JPEG)
            {
                // keep writing to it
                written_file = fwrite(buff, sizeof(BYTE), bytesRead, img_file);
            }
        }

    }
    //Close all open files
    fclose(file);
    fclose(img_file);
    return 0;
}