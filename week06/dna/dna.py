"""
Program Description:
--------------------
The DNA profiling program, implemented in the file dna.py within the dna folder,
is designed to identify the individual to whom a given sequence of DNA belongs.
Utilizing a database containing DNA information and a target DNA sequence, the
program employs a simple algorithm to determine the closest match in the
database.

Implementation Details:
-----------------------
- The program takes two command-line arguments: the path to a CSV file
containing DNA information (data.csv) and the path to a text file containing the
DNA sequence to be analyzed (sequence.txt).
- The load_database function reads the CSV file, containing DNA information of
individuals, and returns it as a list of dictionaries.
- The load_dna_sequence function reads the DNA sequence from the text file and
returns it as a string.
- The longest_match function calculates the length of the longest consecutive
run of a given subsequence within a DNA sequence.
- The main function orchestrates the overall execution of the program. It
calculates the longest match for each subsequence in the database and
identifies the individual with the closest match.
- The find_match function searches the database for an individual whose DNA
profile matches the calculated results for all subsequences.
- The program prints the name of the identified individual or "No match" if
there is no match in the database.

Usage:
------
Execute the program by running the command: python dna.py data.csv sequence.txt

Note: Ensure compatibility with Python 3 and that the required files are
properly formatted.
"""
import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    database_path = sys.argv[1]
    sequence_path = sys.argv[2]

    database = load_database(database_path)
    dna_sequence = load_dna_sequence(sequence_path)

    subsequences = list(database[0].keys())[1:]
    result = {
        subsequence: longest_match(dna_sequence, subsequence)
        for subsequence in subsequences
    }

    match_person = find_match(database, subsequences, result)

    if match_person is not None:
        print(match_person["name"])
    else:
        print("No match")


def load_database(database_path):
    with open(database_path, "r") as file:
        reader = csv.DictReader(file)
        return list(reader)


def load_dna_sequence(sequence_path):
    with open(sequence_path, "r") as file:
        return file.read()


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while sequence[i : i + subsequence_length] == subsequence:
            count += 1
            i += subsequence_length

        longest_run = max(longest_run, count)

    return longest_run


def find_match(database, subsequences, result):
    for person in database:
        if all(
            int(person[subsequence]) == result[subsequence]
            for subsequence in subsequences
        ):
            return person
    return None


if __name__ == "__main__":
    main()
