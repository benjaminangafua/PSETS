#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Asking for user input
    string name = get_string("What is your name?\n");
    printf("hello, %s\n ", name);
}