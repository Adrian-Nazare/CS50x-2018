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

    if (argv[1][0] < 1 && argv[1][0] > 100)
    {
        fprintf(stderr, "Error 2, factor n is lot valid\n");
        return 2;
    }
    //saving the filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    //saving the ratio to n
    double n = atof(argv[1]);
    //making a pointer to reading from the first file
    FILE *inptr = fopen (infile, "r");
    if (!inptr)
    {
        fprintf (stderr, "Error 3, could not open %s for reading\n", infile);
        return 3;
    }
    //making a pointer to writing to the output file
    FILE *outptr = fopen (outfile, "w");
    if (!outptr)
    {
        fclose (inptr);
        fprintf(stderr, "Error 4, could not open %s for writing\n", outfile);
        return 4;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //checking if the file is valid
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose (inptr);
        fclose (outptr);
        fprintf(stderr, "Error 5, file %s is not a 24-bit bitmap 4.0 file\n", infile);
        return 5;
    }
    //finding the padding of the input file
    int paddingi = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //modifying the header after saving the old values
    int owidth = bi.biWidth;
    int oheight = abs(bi.biHeight);

    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;

    //finding the padding of the 2nd file
    int paddingo = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //finding the new filesizes of the output file
    bi.biSizeImage =  bi.biWidth * abs(bi.biHeight) * (bi.biBitCount / 8) + (abs(bi.biHeight) * paddingo);
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    //writing the headers
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //writing the picture data

    //variable for the total number of pixels written in the output file for every line
    int total;
    //declaring a sum for the height, increasing with n each time. if it's >1, it writes sum%1 pixels, else it skips that pixel
    float sumh = n;
    //i points to each line of the original file
    for (int i = 0; i < oheight; i++)
    {
        //declaring j to keep track how many pixels we are traversing on each line
        int j = 0;
        //declaring m to keep track of how many times the line is duplicated, contingent on sumh
        int m = 0;
        if (sumh >= 1.0)
        //here we begin to write the pixels
        for ( ; m < sumh; m++)
        {
            total = 0;
            //declaring a sum for the width
            float sumw = n;
            j = 0;
            RGBTRIPLE triple;
            for ( ; j < owidth; j++)
            {

                fread (&triple, sizeof(RGBTRIPLE), 1, inptr);
                //declaring k to keep track of how many times the line is duplicated, contingent on sumw
                int k = 0;
                if (sumw >= 1.0)
                {
                    for ( ; k < sumw; k++)
                        {fwrite (&triple, sizeof(RGBTRIPLE), 1, outptr);
                         total++;}
                }
                //k is then subtracted from sumw and we repeat
                sumw = (sumw - k) + n;
            }
            //making sure that the number of pixels on each line match the width of the output file
            if (total < bi.biWidth) fwrite (&triple, sizeof(RGBTRIPLE), 1, outptr);
            else if (total > bi.biWidth) fseek (outptr, -3, SEEK_CUR);
            //add the new file's padding
            for (int l = 0; l < paddingo; l++)
                    putc(0x00, outptr);
            //reset the input file's pointer to the beginning of the line
            fseek (inptr, -3 * j, SEEK_CUR);
        }
        //m is then subtracted from sumh and we repeat
        sumh = (sumh - m) + n;
        //before we repeat for the next line, we need to advance the input file's pointer to the next line
        fseek (inptr, (owidth * 3 + paddingi), SEEK_CUR);
    }

    fclose (inptr);
    fclose (outptr);

    return 0;
}
