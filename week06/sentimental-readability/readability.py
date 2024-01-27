"""
Program Description:
--------------------
The readability.py program, located in the sentimental-readability folder, is
designed to calculate the grade level of a given text using the Coleman-Liau
formula. The program prompts the user to input text and then outputs the
corresponding grade level.

Implementation Details:
-----------------------
- The count_infos function calculates the number of letters, words, and
sentences in the given text.
- The main function prompts the user for text input and calculates the L
(average number of letters per 100 words) and S (average number of sentences
per 100 words) values.
- The Coleman-Liau index is computed using the formula:
index = 0.0588 * L - 0.296 * S - 15.8.
- The program prints the corresponding grade level based on the calculated
index. If the index is less than 1, it prints "Before Grade 1." If the index is
greater than 16, it prints "Grade 16+."

Usage:
------
Execute the program by running the command: python readability.py

Note: The user should input the text when prompted.
"""


def count_infos(text):
    letters = sum(c.isalpha() for c in text)
    words = len(text.split())
    sentences = sum(c in ".?!" for c in text)
    return letters, words, sentences


def main():
    text = input("Text: ")

    letters, words, sentences = count_infos(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
