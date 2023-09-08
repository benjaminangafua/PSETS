height = int(input("Number: "))

# Validate pyramid height
while True:
    if height < 1 or height > 8:
        height = int(input("Number: "))

    break
# each row
for r in range(1, height + 1):
    # each column
    for c in range(1, height + 1):
        if c <= height - r:
            print(" ", end="")
            # Print space and line break
        else:
            # Build pyramid
            print("#", end="")
    print(" ", end="")
    print(" ", end="")
    if r <= height:
        print(r * "#")