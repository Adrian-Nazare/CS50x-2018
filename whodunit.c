#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Error 1, incorrect number of arguments\n");
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen (infile, "r");
    if (!inptr)
    {
        fprintf (stderr, "Error 2, could not open %s for reading\n", infile);
        return 2;
    }

    FILE *outptr = fopen (outfile, "w");
    if (!outptr)
    {
        fclose (inptr);
        fprintf(stderr, "Error 3, cpuld not open %s for writing\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose (inptr);
        fclose (outptr);
        fprintf(stderr, "Error 4, file %s is not a 24-bit bitmap 4.0 file\n", infile);
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int black = 0x000000;

    for (int i = 0, height = bi.biHeight; i < height; i++)
    {
        for (int j = 0, width = bi.biWidth; j < width; j++)
        {
            RGBTRIPLE triple;

            fread (&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtBlue > 0 && triple.rgbtRed < 0xff)
                fwrite (&black, sizeof(RGBTRIPLE), 1, outptr);
            else
                fwrite (&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        fseek (inptr, padding, SEEK_CUR);

        for (int k = 0; k < padding; k++)
            putc(0x00, outptr);
    }
    fclose (inptr);
    fclose (outptr);

    return 0;
}