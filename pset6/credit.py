check_sum = 1

starting_digit = 0
position = 0
final_credit = 0
each_digit = 0
length = 0 
# Card_number = input("Number: ")
check_sum = 4111111111111111

starting_digit = check_sum
while check_sum > 0:
    if position % 2 > 0:

        # second  to last digit product of two and sum
        secondToLast = int(check_sum % 10)
        each_digit =  int(2 * secondToLast)
        # print(each_digit)
        # // Controlling two each_digit number 
        if (each_digit > 9):
            quotient_digits = int(each_digit / 10)
            remainder_digit = int(each_digit % 10)

            final_credit += int(quotient_digits + remainder_digit)
            # print(final_credit)
        else:
            final_credit += each_digit
            # print(final_credit)
    else:
        final_credit += int(check_sum % 10)
    # update# Keep diving untill the last digit is 0
    check_sum = int(check_sum / 10)
    position += 1
    length += 1

# Validating types of card
if (final_credit % 10 == 0):
    amex = starting_digit // 10000000000000
    master = starting_digit // 100000000000000
    visa = starting_digit // 1000000000000000
    print(visa, starting_digit)

    # American express
    if ((amex == 34  or amex == 37) and length == 15):
        print("AMEX")

    # // MasterCard
    elif ((master >= 51 and master <= 55) and (length == 16)):
        print("MASTERCARD")

    # // Visa
    elif ((visa == 4 or master / 10 == 4) and (length >= 13 and length <= 16)):
        print("VISA")
else:
    print("INVALID")