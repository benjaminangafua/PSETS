# Prompt user for amount of change
dollars =  float(input("Change owed: "))

# Accept non-negative integer
while True:
    if dollars < 0:
        dollars =  float(input("Change owed: "))
    break

# Convert dollars to cent
cent = int(round(dollars * 100))
coins = 0

# dividing every  change by bills; quarter, dimes, nickle and penny and storing a remainder in cent int
while True:
    if not cent == 0:

        coins += int(cent / 25)
        cent = cent % 25

        coins += int(cent / 10)
        cent = cent % 10

        coins += int(cent / 5)
        cent = cent % 5

        coins += int(cent / 1)
        cent = cent % 1
    print(int(coins), end="")
    break
print()