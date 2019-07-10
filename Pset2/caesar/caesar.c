#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "cs50.h"
int obtainAlphaIndex(char letter, int amount);
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
    // Obtain the string to cipher as well as parsing the cmd line input for the amount
    //printf("plaintext:");
    string name = get_string("plaintext:");
    int amount = atoi(argv[1]);
    printf("ciphertext:");
    for (int i = 0, l = strlen(name); i < l; i++)
    {
        // Checking to make sure the input is a letter
        if (isalpha(name[i]))
        {
            int alphaIndex = obtainAlphaIndex(name[i], amount);
            printf("%c", alphaIndex + checkCap(name[i]));
        }
        else
        {
            printf("%c", name[i]);
        }

    }
    printf("\n");
    return 0;
}
int obtainAlphaIndex(char letter, int amount)
{
    int indexer = checkCap(letter);
    return (((int)letter + amount) - indexer) % 26;
}