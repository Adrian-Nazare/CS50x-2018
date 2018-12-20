#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Pyramid number =");
    }
    while (n < 0 || n > 23);

// Here we start printing the columns
    for (int i = 0; i < n; i++)
    {
        // Here we start printing the space rows
        for (int j = n; j > i + 1; j--)
        {
            printf(" ");
        }
        // Here we stare printing the # rows
        for (int j = i; j > 0; j--)
        {
            printf("#");
        }
        // Finally the 2 # at the end
        printf("#  #");

        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        printf("\n");
    }
}