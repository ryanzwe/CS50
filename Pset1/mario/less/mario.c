#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Choose a positive height less than 23\n");
    int Height = -1;
    // While the player chooses a height outside the constraints, make them choose again
    while (Height > 23 || Height < 0)
    {
        Height = get_int("Height: ");
    }
    //Contains how long the row should be
    int rowLength = Height + 1;
    // Loop through the height of the pyramid
    for (int i = 0; i < Height; i++)
    {
        //Calculates how much blank space there should be per row, prior to adding stars
        int spacesRequired = Height - i - 1;
        for (int j = 0; j < rowLength; j++)
        {
            // Once there are enough spaces, add stars instead
            if (j < spacesRequired)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}