#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int s, e, sdiv, ediv, yrs;
    // TODO: Prompt for start size
    do
    {
        s = get_int("Start Size: ");
    }
    while (s < 9);

    // TODO: Prompt for end size
    do
    {
        e = get_int("End Size: ");
    }
    while (e < s);

    // TODO: Calculate number of years
    for (yrs = 0; e > s; yrs++)
    {
        sdiv = s / 3;
        ediv = s / 4;
        s = s + sdiv - ediv;
    }

    // TODO: Print number of years
    {
        printf("Years: %i\n", yrs);
    }
}