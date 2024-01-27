"""
Program Description:
--------------------
The mario.py program, located in the sentimental-mario-more folder, recreates a
half-pyramid using hashes (#) for blocks with enhanced spacing. The program
prompts the user to input the height of the pyramid and then generates the
corresponding pattern with additional spaces in the middle.

Implementation Details:
-----------------------
- The program prompts the user for the height of the pyramid and ensures that
the input is a valid integer between 1 and 8.
- For each row in the specified height, the program calculates the number of
spaces, hashes, and the spacing in the middle needed to print the pattern.
- The number of spaces on the left is determined by subtracting the current row
index from the total height and then subtracting 1 to ensure proper spacing.
- The number of hashes on the left is determined by adding 1 to the current row
index to create an incremental pattern.
- The middle spacing is a constant value of two spaces.
- The number of hashes on the right is the same as on the left, creating a
symmetrical pattern.
- The program prints each row with the required spaces, hashes, middle spacing,
and right hashes to form the enhanced half-pyramid.

Usage:
------
Execute the program by running the command: python mario.py

Note: The user should input the desired height when prompted.
"""
height = -1

while height < 1 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Not an integer")

for row in range(height):
    spaces_left = " " * (height - row - 1)
    hashes_left = "#" * (row + 1)
    spaces_middle = "  "
    hashes_right = "#" * (row + 1)

    print(spaces_left + hashes_left + spaces_middle + hashes_right)
