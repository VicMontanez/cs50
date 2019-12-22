//Resize

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4 || !isdigit(*argv[1]))
    {
        printf("Try Again Please\n");
        return 1;
    }


    char *n = argv[1];
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    int number = atoi(n);

    if (number < 1 || number > 100)
    {
        printf("The number must be more than 1 but less than 100\n");
    }
// else
//     {
//          printf("Yup that is a good number\n");
//     }
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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //old width
    LONG biWidthOld = bi.biWidth;

    // new width and height
    bi.biWidth *= number;
    bi.biHeight *= number;

    //old padding for scanlines
    int paddingOld = (4 - (biWidthOld * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((3 * bi.biWidth) + padding) * abs(bi.biHeight);

    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) +  sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / number; i < biHeight; i++)
    {

        for (int j = 0; j < number; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < biWidthOld; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int l = 0; l < number; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }
            if (j < number - 1)

                fseek(inptr, -(biWidthOld * (int)sizeof(RGBTRIPLE)), SEEK_CUR);

        }
        // skip over padding, if any
        fseek(inptr, paddingOld, SEEK_CUR);
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;

}