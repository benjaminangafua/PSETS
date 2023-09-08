#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    int cent, coins;

    do
    {
        //Money obtain from the user

        dollars = get_float("Change owed: ");

        //Convert money to cent
        cent = round(dollars * 100);
    }
    while (dollars < 0);

    for (coins = 0; cent != 0;)
    {
        // dividing every  change by bills:
        // quarter, dimes, nickle and penny and storing a remainder in cent int
        coins += cent / 25;
        cent  = cent  % 25
        coins += cent / 10;
        cent  =  cent  % 10;

        coins += cent / 5;
        cent  = cent  % 5;

        coins = cent / 1;
        cent  = cent %  1;
        /* code */
    }


    printf("%i\n", coins);
}