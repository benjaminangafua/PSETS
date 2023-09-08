height = int(input("Height: \n"))

# Validate pyramid height
while True:
    if height < 1 or height > 8:
        height = int(input("Height: \n"))
    break
# each row
for r in range(1, height + 1):
    # each column
    for c in range(1, height + 1):
        if c <= height - r:
            # Print space and line break
            print(" ", end="")
        else:
            # Build pyramid
            print("#", end="")
    print("")