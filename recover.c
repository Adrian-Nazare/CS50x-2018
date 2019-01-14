#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error 1: Incorrect number of arguments");
        return 1;
    }

    FILE *inptr = fopen (argv[1], "r");
    if (!inptr)
    {
        fprintf (stderr, "Error 2: File could not be opened for reading");
        return 2;
    }

    int i = 0; int j;
    unsigned char c;
    char *outfile = malloc (3);
    //c = getc(inptr);
    while (getc(inptr) != EOF)
    {
        fseek (inptr, -1, SEEK_CUR);
        if (getc(inptr) == 0xff)
            if (getc(inptr) == 0xd8)
                if (getc(inptr) == 0xff)
                {
                    c = getc(inptr);
                    if (c >= 0xe0 && c <= 0xef)
                    {
                        fseek (inptr, -4, SEEK_CUR);

                        //it begins
                        FILE *outptr = malloc (sizeof(FILE));
                       // c = getc(inptr);
                        while (getc(inptr) != EOF)
                        {
                            fseek (inptr, -1, SEEK_CUR);
                            if (getc(inptr) == 0xff)
                            {
                                if (getc(inptr) == 0xd8)
                                {
                                    if (getc(inptr) == 0xff)
                                    {
                                        c = getc(inptr);
                                        if (c >= 0xe0 && c <= 0xef)
                                        {
                                            i++;
                                            fseek (inptr, -4, SEEK_CUR);

                                            sprintf (outfile, "%d.jpg", i);
                                            outptr = fopen (outfile, "w");

                                            for (j = 0; j < 512; j++)
                                                fputc (getc(inptr), outptr);
                                        }
                                        else
                                        {
                                            fseek (inptr, -4, SEEK_CUR);
                                            for (j = 0; j < 512; j++)
                                                fputc (getc(inptr), outptr);
                                        }
                                    }
                                    else
                                    {
                                        fseek (inptr, -3, SEEK_CUR);
                                        for (j = 0; j < 512; j++)
                                                fputc (getc(inptr), outptr);
                                    }
                                }
                                else
                                {
                                    fseek (inptr, -2, SEEK_CUR);
                                    for (j = 0; j < 512; j++)
                                                fputc (getc(inptr), outptr);
                                }
                            }
                            else
                            {
                                fseek (inptr, -1, SEEK_CUR);
                                for (j = 0; j < 512; j++)
                                                fputc (getc(inptr), outptr);
                            }

                        }
                        fclose (inptr);
                        fclose (outptr);
                        return 0;
                    }
                }
    }
    //sprintf(outfile, "%d", i + 1);


}