height = -1
while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Not an integer")

height -= 1
for rowLeft in range(height + 1):
    for column in range(height + 1):
        if rowLeft + column >= height:
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    rowRight = height - rowLeft
    for column in range(height + 1):
        if rowRight + column <= height:
            print("#", end="")
    print()
