#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Here we declare the cEnts and the minimum number of Coins
    int e, c;
    float h;
    // Here we initialize the cHange you're owned
    do
    {
        h = get_float("How much change are you owned? ($) \n");
    }
    while (h < 0);
    //here we assign that value to an integer e
    e = round(h * 100);

    c = e / 25;
    e = e % 25;
    c = c + e / 10;
    e = e % 10;
    c = c + e / 5;
    e = e % 5;
    c = c + e;

    printf("%i\n", c);

}