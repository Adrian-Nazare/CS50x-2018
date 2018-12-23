#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // daca doar 2 argumente, verificam daca toate caracterele sunt litere
    if (argc == 2)
    {
        // initializam i si n - lungimea cuvantului cheie, plus k ca primul cuvant, cel cheie
        int i = 0;
        string k = argv[1];
        int n = strlen(k);

        while (isalpha(k[i]) && i < n)
        {
            i++;
        }

        //daca sunt doar 2 argumente si i n-a ajuns la capat, deci are cifre:
        if ((argc == 2) && (i == n))
        {
            for (i = 0; i < n; i++)
            {
                k[i] = toupper(k[i]);
            }
            i = 0;

            string p = get_string("plain text: ");
            // refolosim i, initializam j - counterul pt cuv. cheie; cat timp i< lungimea cuvantului, incriptam literele:
            for (int j = 0, m = strlen(p); i < m; i++)
            {
                if (p[i] >= 'a' && p[i] <= 'z')
                {
                    p[i] = 97 + ((p[i] - 97) + (k[j % n] - 65)) %  26;
                    j++;
                }
                else if (p[i] >= 'A' && p[i] <= 'Z')
                {
                    p[i] = 65 + ((p[i] - 65) + (k[j % n] - 65)) %  26;
                    j++;
                }

            }
            printf("ciphertext: %s\n", p);
            return 0;
        }

        else
        {
            printf("Error!\n");
            return 1;
        }

    }
    else
    {
        printf("Error!\n");
    }
    return 1;
}