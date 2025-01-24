from cs50 import get_string


def main():
    passage = get_string("Text: ")  # ask for input

    # Count the number of letters, words, and sentences in the text
    n_letters = letters(passage)
    n_words = words(passage)
    n_sen = sentences(passage)

    # Calculating L and S for the coleman-liau formula
    L = n_letters/n_words*100.0
    # print(f"L: {L}")

    S = 100.0 * n_sen/n_words
    # print(f"S: {S}")

    # Compute the Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)
    # print(f"grade: {grade}")

    # if statemants for printing grade
    if (grade < 1):
        print("Before Grade 1")
    elif (grade >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

# function to return the no. of letters in the passage


def letters(s):
    letter = 0
    for i in s:
        if (i.islower() == True):
            letter += 1
        elif (i.isupper() == True):
            letter += 1

    return letter


# function to return no. of words in the passage
def words(s):
    word = 1
    for i in s:
        if (i == ' '):
            word += 1

    return word

# function to return no. of sentences in the passage


def sentences(s):
    sentence = 0
    for i in s:
        if (i == '.' or i == '?' or i == '!'):
            sentence += 1

    return sentence


# calling the main function
main()
