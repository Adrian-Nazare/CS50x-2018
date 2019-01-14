#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main (int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Error 1, incorrect number of arguments\n");
        return 1;
    }

    if (argv[3][0] < 1 && argv[3][0] > 100)
    {
        fprintf(stderr, "Error 1,5, factor n is lot valid\n");
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    double n = atof(argv[3]);

    FILE *inptr = fopen (infile, "r");
    if (!inptr)
    {
        fprintf (stderr, "Error 2, could not open %s for reading\n", infile);
        return 1;
    }

    FILE *outptr = fopen (outfile, "w");
    if (!outptr)
    {
        fclose (inptr);
        fprintf(stderr, "Error 3, could not open %s for writing\n", outfile);
        return 1;
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
        return 1;
    }

    int paddingi = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int owidth = bi.biWidth;
    int oheight = bi.biHeight;
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    int paddingo = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage =  bi.biWidth * abs(bi.biHeight) * (bi.biBitCount / 8) + (bi.biHeight * paddingo);
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    float sumh = n;
    for (int i = 0; i < oheight; i++)
    {
        int j = 0;
        int m = 0;
        if (sumh >= 1.0)
        for ( ; m < sumh; m++)
        {
            float sumw = n;
            j = 0;
            for ( ; j < owidth; j++)
            {
                RGBTRIPLE triple;
                fread (&triple, sizeof(RGBTRIPLE), 1, inptr);

                int k = 0;
                if (sumw >= 1.0)
                {
                    for ( ; k < sumw; k++)
                        fwrite (&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                sumw = (sumw - k) + n;
            }

            for (int l = 0; l < paddingo; l++)
                    putc(0x00, outptr);

            fseek (inptr, -3 * j, SEEK_CUR);
        }
        sumh = (sumw - m) + n;
        fseek (inptr, (3 * j) + paddingi, SEEK_CUR);
    }

    fclose (inptr);
    fclose (outptr);

    return 0;
}
