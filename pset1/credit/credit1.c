#include <cs50.h>
#include <stdio.h>

int main(void)
{

    long creditCard, start_digit;
    int placeValue = 0, finalCredit = 0, digits, length = 0;

    while (creditCard != 0)
    {
        /* code */
        creditCard = get_long("Number: ");
        start_digit = creditCard;

        // while (creditCard > 0)
        // {
            // reduce credit to 0
            //credit % 10 ==> 0, placeValue 0

            if (placeValue % 2 != 0)
            {
                // second digits

                // Multiply every other digit by 2,
                digits = 2 * (creditCard % 10);

                if (digits > 9)
                {
                    // Controlling two digits number

                    finalCredit = finalCredit + (digits / 10) + (digits % 10);
                }
                else
                {
                    // The sum of digits that are multiplied by 2
                    finalCredit = finalCredit + digits;   //The last digit
                }
            }
            else
            {
                //  The sum of the digits that weren’t multiplied by 2 (first digits)
                finalCredit = finalCredit + creditCard % 10;
            }
            //update
            creditCard = creditCard / 10;       // Keep diving untill the last digit is 0
            placeValue++;
            length++;
        // }
    }
    // Validating types of card
    if (finalCredit % 10 == 0)
    {
        long amex = start_digit / 10000000000000;
        long master = start_digit / 100000000000000;
        long visa = start_digit /   1000000000000;
        // American express
        if ((amex == 34  || amex == 37) && length == 15)
        {
            printf("AMEX\n");
            return 0;
        }
        // MasterCard
        else if ((master >= 51 && master <= 55) && (length == 16))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        // Visa
        else if ((visa == 4 || master / 10 == 4) && (length >= 13 && length <= 16))
        {
            printf("VISA\n");
            return 0;
        }
    }
    printf("INVALID\n");
}