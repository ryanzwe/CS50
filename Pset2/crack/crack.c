#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>
//method declaration
bool checkMatch(string a, string b);
// 65 to 90 A-Z, 97 to 122, a-z
//VARS
int totalChecks = 0;
int main(int argc, char *argv[])
{

    // If the user inputs too many arguments, terminate the program
    if (argc != 2)
    {
        printf("Invalid arguments, use ./crack password");
        //return 1;
    }
    string hash = argv[1];
    // Grabbing the right two characters of the hashed password to obtain the salt, and adding a null terminator
    char salt[3];
    strncpy(salt, hash, 2);
    salt[2] = '\0';

    char guess[6];
    // alphabet organised by most used letters in the alphabet
    string letters = "\0etainoshrdlucmfwygpbvkqjxzETAINOSHRDLUCMFWYGPBVKQJXZ";
    int letters_count = 26 + 26 + 1; // lowercase + uppercase + null terminator
    // pos5 0----
    for (int left = 0; left < letters_count; left++)
    { // pos4 -0---
        for (int leftCenter = 0; leftCenter < letters_count; leftCenter++)
        { //pos3 --0--
            for (int middle = 0; middle < letters_count; middle++)
            { //pos2 ---0-
                for (int rightCenter = 0; rightCenter < letters_count; rightCenter++)
                { //pos1 ----0
                    for (int right = 1; right < letters_count; right++, totalChecks++)
                    {
                        guess[0] = letters[right];//0----
                        guess[1] = letters[rightCenter];//-0---
                        guess[2] = letters[middle];//--0--
                        guess[3] = letters[leftCenter];//---0-
                        guess[4] = letters[left];//----0
                        string cryptedGuess = crypt(guess, salt);
                        if (checkMatch(hash, cryptedGuess))
                        {
                            printf("%s \n", guess);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

bool checkMatch(string a, string b)
{
    bool returnVar = false;
    returnVar = (strcmp(a, b) == 0) ? true : false;
    return returnVar;
}
