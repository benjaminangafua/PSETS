def main():
    # Get user input
    statement = input("Text: ")

    # Get counted value from letter, word and sentence functions
    letter = countletter(statement)
    sentence = computeSentences(statement)
    word = computeWords(statement) + 1

    print(sentence)

    L = (letter * 100.00) / word
    S = (sentence * 100.00) / word

    # Coleman-Liau index formula
    index = 0.0588 * L - 0.296 * S - 15.8

    # Truncating the decimal part
    grade = round(index)

    # print("Grade {},{},{}".format(L, S, grade))

    if (grade >= 16):
        print("Grade 16+\n")
    elif (grade < 1):
        print("Before Grade 1\n")
    else:
        print(f"Grade {grade}")


# Compute letters
def countletter(letter):

    countLetter = 0
    for i in range(len(letter)):
        if (letter[i].isalpha()):
            countLetter += 1
    return countLetter


# Compute words
def computeWords(word):
    countWords = 0
    for i in range(len(word)):
        if (word[i].isspace()):
            countWords += 1
    return countWords


# Compute sentences
def computeSentences(sentence):
    countSentence = 0
    for i in range(len(sentence)):

        if (sentence[i] == '.' or sentence[i] == '!' or sentence[i] == '?'):
            countSentence += 1
    return countSentence


if __name__ == "__main__":
    main()
