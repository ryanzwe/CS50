// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize size infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int resizeAmt = atoi(argv[1]);
    if (resizeAmt <= 0 || resizeAmt > 100)
    {
        printf("Min: 1, Max: 100");
        return 2;
    }
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfResize;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, biResize;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // Creating the header & infoheader for the new bitmap
    bfResize = bf;
    biResize = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // initializing the dimensions of the new bmp
    biResize.biWidth *= resizeAmt;
    biResize.biHeight *= resizeAmt;
    // Calculating the padding for the new & old bmp
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingResize = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //Calculating the new total size of the image in bytes (pixel and pad, no headers)
    biResize.biSizeImage = ((sizeof(RGBTRIPLE) * biResize.biWidth) + paddingResize) * abs(biResize.biHeight);
    //Calculating the new total size of the file in size including the headers
    bfResize.bfSize = biResize.biSizeImage + sizeof(bfResize) + sizeof(biResize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    printf("biHeight = %i ", abs(biResize.biHeight));

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < resizeAmt; j++)
        {
            RGBTRIPLE rowPX[3 * resizeAmt];
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int l = 0; l < resizeAmt; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // adding in padding if required
            for (int l = 0; l < paddingResize; l++)
            {
                fputc(0x00, outptr);
            }
            // moving the pointer back to the start of the line by offsetting the size of the line * how many bytes are in the struct
            if (j < resizeAmt - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
