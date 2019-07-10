#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

void PrintStair(int dir, int j, int i, bool drawWhiteSpace);
int Height;
int main(void)
{
    // While the player chooses a height outside the constraints, make them choose again
    do
    {
        Height = get_int("Height: ");
    }
    while (Height > 23 || Height < 0);
    //Contains how long the row should be, +2 for the spaces in middle, height * 2 for total space needed for # and space
    int rowLength = Height;  // * dir to invert the length, or forward
    // Loop through the height of the pyramid
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < rowLength; j++)
        {
            PrintStair(1, j, i, true);
        }
        printf("  ");
        for (int j = rowLength; j > 0; j--)
        {
            PrintStair(1, j - 1, i, false);
        }
        printf("\n");
    }

}
void PrintStair(int dir, int j, int i, bool drawWhiteSpace)
{
    int spacesReq = (Height - i - 1);
    if (j < spacesReq)
    {
        if(drawWhiteSpace)
        {
            printf(" ");
        }
    }
    else
    {
        printf("#");
    }
}