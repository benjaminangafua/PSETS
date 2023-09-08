#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int validateKey(string k);
int main(int argc, string argv[])
{
    // Get key
    string s =  argv[1];
    if (argc != 2 || !validateKey(s))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //Get plain text
        string plaintext = get_string("plaintext: ");
        // Encipher plainText
        printf("ciphertext: ");
        //Maching cipher text alphabetically in accordance with plaintext
        int matching[26];
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            matching[i] = argv[1][i];
        }
        int p, i, len;
        char c; 
        //Loop over each letter
        for (i = 0, len = strlen(plaintext); i < len; i++)
        {
            char ptext = plaintext[i];
            //Shift text
            if (isalpha(ptext))
            {
                //Lower case letter
                if (islower(ptext))
                {
                    p = ptext - 97;
                    c = tolower(matching[p]);
                    // c+= 97;
                }
                // Upper case letter
                else if (isupper(ptext))
                {
                    p = ptext - 65;
                   c = toupper(matching[p]);
                    // c += 65;
                }
                printf("%c", c);
            }
            // Print characters that are not text
            else
            {
                printf("%c", ptext);
            }
        }
        printf("\n");
        return 0;
    }
}
// Validating key
int validateKey(string key)
{
    /**
     * Only alphabets
     * Length 26
     *No repetition of letter
    */
    int i = 0, len;
    //Avoiding repetitions of each letter
   int noDuplicate[26];
   for (i = 0; i < 26; i++)
   {
       noDuplicate[i] = 0;
   }
    for (i = 0, len = strlen(key); i < len; i++)
    {
        char keyPassed = key[i];
        //Only Alphabets
        if(!isalpha(keyPassed))
        {
            return false;
        }
        //If an alphabet repeats return fales
        if(noDuplicate[toupper(keyPassed)- 'A'] != 0)
        {
            return false;
        }
        //Accepting a single letter
        else
        {
            noDuplicate[toupper(keyPassed) - 'A'] = 1;
        }
    }
    //Length of the key per letter
    return i==26;
}