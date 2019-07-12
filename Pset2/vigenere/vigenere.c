#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "cs50.h"
#define NEW_LINE printf("\n");
int obtainAlphaIndex(char letter);
int combine(char la, int amount);
// returns the letters starting index depending on if its capital or not
int checkCap(char letter)
{
    return isupper(letter) ? 65 : 97;
}

int main(int argc, char *argv[])
{
    // If the user inputs too many arguments, terminate the program
    if (argc > 2 || argc < 2)
    {
        printf("Too many args");
        return 1;
    }
    // Obtain the cipher text from the cmd line, and check if its full of valid letter
    char *cipherCode = argv[1];
    for (int l = 0, cl = strlen(cipherCode); l < cl; l++)
    {
        if(!isalpha(cipherCode[l]))
        {
            return 1;
        }
    }
    // Obtain the string to cipher from the user
    string name = get_string("plaintext: ");
    int cipherIndex = 0;
    printf("ciphertext: ");
    for (int i = 0, l = strlen(name), cl = strlen(cipherCode); i < l; i++)
    {
        // Checking to make sure the input is a letter
        if (isalpha(name[i]))
        {
            // obtaining the alpha numeric index of the parsing letter, as well as the cipher letter then merge them together to get the output
            int letterIndex = obtainAlphaIndex(name[i]);
            int ciph = obtainAlphaIndex(cipherCode[cipherIndex]);
            printf("%c", (combine(name[i], ciph) + checkCap(name[i])));
            // If the cipher text is at CLEARits length, then set it to the first letter, or continue incrementing
            cipherIndex = (cipherIndex >= cl - 1) ? 0 : cipherIndex + 1;
        }
        else
        {
            printf("%c", name[i]);
        }

    }
    printf("\n");
    return 0;
}
//Grabs the current letter, increments it by an amount, checks if it should be capital or not, then makes sure its still within the alphabetical bounds
int combine(char la, int amount)
{
    int indexer = checkCap(la);
    return (((int)la + amount) - indexer) % 26;
}
// Obtains a letters place in the alphabet by grabbing its ascii code minus the A or a to find out how many letters into the alphabet it is, then makes sure its constrained
int obtainAlphaIndex(char letter)
{
    int indexer = checkCap(letter);
    return (((int)letter - indexer)) % 26;
}