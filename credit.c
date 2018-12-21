#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string c, v = "INVALID";
    int s0 = 0, s2 = 0;
    long n = get_long_long("Number ");
    long p12 = pow(10, 12);
    long p13 = pow(10, 13);
    long p14 = pow(10, 14);
    long p15 = pow(10, 15);
    long p16 = pow(10, 16);
// Checking of the size and first numbers are correct
    if ((n >= p15 && n < p16) && (n / p14 == 51 || n / p14 == 52 || n / p14 == 53 || n / p14 == 54 || n / p14 == 55))
    {
        c = "MASTERCARD";
    }
    else if (((n >= p15 && n < p16) && (n / p15 == 4)) || ((n >= p12 && n < p13 && (n / p12 == 4))))
    {
        c = "VISA";
    }
    else if (n / p13 == 34 || n / p13 == 37)
    {
        c = "AMEX";
    }
    else
    {
        c = "INVALID";
    }

// if they are, we'll check the sums next
    if (strcmp(c, v) != 0)
    {
        int j;
        for (int i = 1; n > 0; n /= 10)
        {
            j = n % 10;
            if (i % 2 == 1)
            {
                s0 = s0 + j;
            }
            else
            {
                if (j * 2 >= 10)
                {
                    s2 = s2 + ((j * 2) / 10) + ((j * 2) % 10);
                }
                else
                {
                    s2 = s2 + 2 * j;
                }
            }
            i++;
        }

    }
    if ((s0 + s2) % 10 != 0)
    {
        c = "INVALID";
    }
    printf("%s\n", c);
}
