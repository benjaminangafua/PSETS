#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int countletter(string letter); 
int computeWords(string word);
int computeSentences(string sentence);

int countWords = 0;  

int main(void)
{
    string statement = get_string("Text: ");

    int letter = countletter(statement);
    int sentence = computeSentences(statement);
    int word = computeWords(statement);

    int L = letter / word;
    int S = sentence / word + 1;

    float index = 0.588 * L - 0.296 * S - 15.8;

    int grade = round(index);
    if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;
}
int computeSentences(string sentence)
{
    int countSentence = 0;
    for (int i = 0, len = strlen(sentence); i < len; i++)
    {
        if (sentence[i] == 33 || sentence[i] == 46 || sentence[i] == 63)
        {
            countSentence++;
        }
    }
    return countSentence;
}
int computeWords(string word)
{
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        if (isspace(word[i]))
        {
             countWords ++;
        }
    }
    return countWords;
}

int countletter(string letter)
{ 
    int countLetter = 0;  
    for (int i = 0, l = strlen(letter); i < l; i++)
    {
        if (islower(letter[i]) || isupper(letter[i]))
        {
             countLetter++; 
        }
    }
    return countLetter;
} 

/*#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int countletter(string letter);
int computeWords(string word);
int computeSentences(string sentence);


int main(void)
{
    //Get user input
    string statement = get_string("Text: ");

    // Get counted value from letter, word and sentence functions
    int letter = countletter(statement);
    int sentence = computeSentences(statement);
    int word = computeWords(statement) + 1;

   

    float L = (letter * 100.0f) / word;
    float S = (sentence * 100.0f) / word;

    //Coleman-Liau index formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //Truncating the decimal part
    int grade = round(index);

    // printf("Grade %f\n %f\n %i\n", L, S, grade);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;
}

// Letters counting
int countletter(string letter)
{
    int countLetter = 0;
    for (int i = 0, l = strlen(letter); i < l; i++)
    {
        if (isalpha(letter[i]))
        {
            countLetter++;
        }
    }
    return countLetter;
}

// Word counting
int computeWords(string word)
{

    int countWords = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        if (isspace(word[i]))
        {
            countWords++;
        }
    }
    return countWords;
}


// Sentences counting
int computeSentences(string sentence)
{
    int countSentence = 0;
    for (int i = 0, len = strlen(sentence); i < len; i++)
    {
        if (sentence[i] == 33 || sentence[i] == 46 || sentence[i] == 63)
        {
            countSentence++;
        }
    }
    return countSentence;
}

 /**
     * L is the average number of letters per 100 words in the text
     * S is the average number of sentences per 100 words in the text.
    */
