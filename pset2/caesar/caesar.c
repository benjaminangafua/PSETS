#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Get key
    string s = argv[1];

    int k = atoi(s); 
    int p, i, len;
    char c;
    
  if (argc != 2 && k != 1)
    {
        printf("Usage ./caesar key\n");
        return 1;
    } 
    else
    {
        //Get plain text
        string plaintext = get_string("plaintext: ");

        // Encipher plainText
        printf("ciphertext: ");

        //Loop over each letter
        for (i = 0, len = strlen(plaintext); i < len; i++)
        {
            //Shift text
            if (isalpha(plaintext[i]))
            {
                //Lower case letter
                if (islower(plaintext[i]))
                {
                    p = plaintext[i] - 97;
                    c = (p + k) % 26;
                    c += 97;
                }
                // Upper case letter
                else if (isupper(plaintext[i]))
                {
                    p = plaintext[i] - 65;
                    c = (p + k) % 26;
                    c += 65;
                }
                printf("%c", c);
            }
            // Print characters that are not text
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");

        return 0;
    }
    
}
