import cs50
import crypt
from sys import argv


# Function to return an indexed letter, or null depending on the index inputted as the argument
def returnLetter(idx):
    letters = "etainoshrdlucmfwygpbvkqjxzETAINOSHRDLUCMFWYGPBVKQJXZ"
    if idx == 0:
        return ""
    return letters[idx - 1]
    

# Function to loop through 5 letters of a generated alphabet testing each combination to see if it is the password
def passwordCheck(len, hashedPw, salt):
    pwGuess = ""
    for L in range(len):
        for LR in range(len):
            for M in range(len):
                for RL in range(len):
                    for R in range(len):
                        pw = [returnLetter(L), returnLetter(LR), returnLetter(
                            M), returnLetter(RL), returnLetter(R)]
                        pwGuess = "".join(pw)
                        guess = crypt.crypt(pwGuess, salt)
                        if guess == hashedPw:
                            return hashedPW
    return ":("
    

# Main function to crack the users password
def main():
    # Make sure only one password is specified, if not, exit
    if(len(argv) != 2):
        print("usage: python crack.py passwd")
        exit(1)
    hashedPW = argv[1]
    lettersCount = 26 + 26 + 1  # lowercase + uppercase
    salt = hashedPW[:2]  # Grab the salt of the password
    print(passwordCheck(lettersCount, hashedPW, salt))


if __name__ == "__main__":
    main()
