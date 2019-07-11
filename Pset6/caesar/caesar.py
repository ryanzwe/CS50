import cs50
from sys import argv


def main():
    # Make sure only one number is specified, if not, exit
    if(len(argv) != 2):
        print("usage: python caesar.py amount")
        exit(1)

    amt = int(argv[1])
    chipherWord = cs50.get_string("plaintext: ")
    cipheredWord = ""
    print("ciphertext: {}".format(ciph(chipherWord, amt)))


def ciph(word, amt):
    newWord = ""
    # Loop through the word and obtain its alpha index to encrypt
    for i in range(len(word)):
        if(word[i].isalpha()):
            isCap = 65 if word[i].isupper() else 97
            # Word[i] represents the base ascii, plus the amount we want to shift it by, then remove the idx which will be 65 or 97u as the letter A of ascii
            index = ((ord(word[i]) + amt) - isCap) % 26
            newLetter = chr(index + isCap)
            newWord += newLetter
        # If the word isnt alpha, it is most likely a space or comma
        else:
            newWord += word[i]
    return newWord


if __name__ == "__main__":
    main()
