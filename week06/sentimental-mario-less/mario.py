height = -1
while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Not an integer")

for row in range(height):
    for column in range(height):
        if row + column >= height - 1:
            print("#", end="")
        else:
            print(" ", end="")
    print()
