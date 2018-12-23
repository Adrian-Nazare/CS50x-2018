#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        string p = get_string("plain text: ");
        for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (p[i] >= 'a' && p[i] <= 'z')
            {
                p[i] = 97 + ((p[i] - 97) + k) %  26;
            }
            else if (p[i] >= 'A' && p[i] <= 'Z')
            {
                p[i] = 65 + ((p[i] - 65) + k) %  26;
            }

            // if ((p[i] >= 'a' && p[i] <='z') || (p[i] >= 'A' && p[i] <='Z'))
        }
        printf("ciphertext: %s\n", p);
        return 0;
    }

    else
    {
        printf("Error!\n");
    }
    return 1;
}