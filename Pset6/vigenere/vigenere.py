import cs50
from sys import argv


def main():
    #Make sure only one number is specified, if not, exit
    if(len(argv) != 2):
        print("usage: python vigenere.py k")
        exit(1)
    ciphWord = argv[1]
    for i in range(len(ciphWord)):
        if(not ciphWord[i].isalpha()):
            exit(1)
    cipherWord = cs50.get_string("plaintext: ")
    print("ciphertext: {}".format(ciph(cipherWord, ciphWord)))


# Returning an ascii base depending on if the character is cap
def capitalAscii(letter):
    return 65 if letter.isupper() else 97


# Returning the base alphabet letter incremented by an amount
def alphaIndex(letter, amt):
    return ((ord(letter) + amt) - capitalAscii(letter)) % 26


def ciph(word, ciphAmtWord):
    newWord = ""
    cryptIDX = 0
    # Loop through the word and obtain its alpha index to encrypt
    for i in range(len(word)):
        if(word[i].isalpha()):
            # The amount to shift by depending on the letter of the ciphering, looping
            amt = alphaIndex(ciphAmtWord[cryptIDX % len(ciphAmtWord)], 0)
            index = alphaIndex(word[i], amt)
            newLetter = chr(index + capitalAscii(word[i]))
            newWord += newLetter
            cryptIDX += 1
        # If the word isnt alpha, it is most likely a space or comma
        else:
            newWord += word[i]
    return newWord


if __name__ == "__main__":
    main()
