"""
Program Description:
--------------------
The mario.py program, located in the sentimental-mario-less folder, recreates a
half-pyramid using hashes (#) for blocks. The program prompts the user to input
the height of the pyramid and then generates the corresponding pattern.

Implementation Details:
-----------------------
- The program prompts the user for the height of the pyramid and ensures that
the input is a valid integer between 1 and 8.
- For each row in the specified height, the program calculates the number of
spaces and hashes needed and prints the pattern accordingly.
- The number of spaces is determined by subtracting the current row index from
the total height and then subtracting 1 to ensure proper spacing.
- The number of hashes is determined by adding 1 to the current row index to
create an incremental pattern.
- The program prints each row with the required spaces and hashes to form the
half-pyramid.

Usage:
------
Execute the program by running the command: python mario.py

Note: The user should input the desired height when prompted.
"""
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        print("Not an integer")

for row in range(height):
    spaces = " " * (height - row - 1)
    hashes = "#" * (row + 1)
    print(spaces + hashes)
