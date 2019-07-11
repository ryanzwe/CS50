from cs50 import get_string
from sys import argv


def main():
     # Make sure only one dictionary is specified
    if(len(argv) != 2):
        print("usage: python bleep.py dictionary")
        exit(1)
    
    # Opening the banned file text and outputting it to a list
    bannedFile = open(argv[1], "r")
    bannedWords = list()
    for wordLine in bannedFile:
        # Append the words to the list and remove the \n
        bannedWords.append(wordLine.strip())

    inputString = get_string(
        "What message would you like to censor? \n").split()
    for i in range(len(inputString)):
        if(inputString[i].lower() in bannedWords):
            inputString[i] = "*" * len(inputString[i])
    print(" ".join(inputString))
    return


if __name__ == "__main__":
    main()
