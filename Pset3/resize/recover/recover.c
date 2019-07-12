#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int imageCount = 0;
    if (argc != 2)
    {
        fprintf(stderr, "./recover input");
        return 1;
    }
    //infile
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Invalid file");
        return 1;
    }
    //Creating the image file
    //allocating a 512b buffer to store the bytes
    unsigned char *buffer = malloc(512);

    // int files = fread(buffer, 512, 1, inptr);
    FILE *curImage = NULL;
    while (fread(buffer, 512, 1, inptr))
    {
        // Checking to see if we hit a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // This means we've already got a jpeg open
            if (imageCount > 0)
            {
                fclose(curImage);
            }
            //Creating the filename, 8 long for 3 nums + 3 letter + dot + null terminator and create a writeable file
            char fileName[8];
            sprintf(fileName, "%03i.jpg", imageCount);
            fileName[7] = '\0';
            curImage = fopen(fileName, "w");
            imageCount++;
        }
        //writing the buffer outside of the loop as the loop finds the START of a new jpg but not where it ENDS
        // whereas having it here writes start to end, then gets closed on new jpg found
        if (imageCount > 0)
        {
            //Writing the current read buffer to the file
            fwrite(buffer, 512, 1, curImage);
        }
    }
    //Closing the current open files, and preventnig memory leaks
    fclose(curImage);
    fclose(inptr);
    free(buffer);
    return 0;
}
