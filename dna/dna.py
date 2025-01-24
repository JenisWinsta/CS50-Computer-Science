import csv
from sys import argv
import sys


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("format: dna.py [database file] [txt file]")
        sys.exit(1)

    # TODO: Read database file into a variable
    rows = []
    with open(f"{argv[1]}") as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    # print(rows)
    # TODO: Read DNA sequence file into a variable
    with open(f"{argv[2]}") as file:
        dna_seq = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    str_names = reader.fieldnames[1:]  # Skip the "name" column

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for str_name in str_names:
        str_counts[str_name] = longest_match(dna_seq, str_name)

    # TODO: Check database for matching profiles
    for row in rows:
        match = True
        for str_name in str_names:
            # Compare the STR counts with the database values
            if int(row[str_name]) != str_counts[str_name]:
                match = False
                break

        if match:
            print(row["name"])
            return

    # If no match is found
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
