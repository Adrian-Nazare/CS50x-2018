#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // daca doar 2 argumente, verificam daca toate caracterele sunt litere
    if (argc == 2)
    {
        char a[52] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char p[10] = "";
        string key = argv[1];
        char salt[2];
        salt[0] = key[0];
        salt[1] = key[1];
        int i = 0;
        while (strlen(p) <= 5)
        {
            i = 0;
            while (true) //start from position 0, increment once, go up only after hitting z, then restart from i+1
            {
                // if this is the last letter of the alpphabet:
                if (p[i] == a[51])
                {
                    // start again from 'A' and get to the next character
                    p[i] = a[0];
                    i++;
                    // you won't check here, because passwords would repeat, the initialization of the next char is done next loop
                }
                // if it is not initialized yet, you initialize it, exit the loop and restart counting:
                else if (p[i] == 0)
                {
                    p[i] = a[0];
                    //printf("%s  ", p);
                    if (strcmp(key, crypt(p, salt)) == 0)
                    {
                        printf("The Correct Key is %s\n", p);
                        return (0);
                        exit(0);
                    }
                    break;
                }
                else if (p[i] == a[25])
                {
                    // increment it by jumping 7 positions from 'Z' in order to reach 'a' is ASCII
                    p[i] += 7;
                    //printf("%s  ", p);
                    if (strcmp(key, crypt(p, salt)) == 0)
                    {
                        printf("The Correct Key is %s\n", p);
                        return (0);
                        exit(0);
                    }
                    break;
                }
                else
                {
                    // increment the counter
                    p[i] += 1;
                    //printf("%s  ", p);
                    if (strcmp(key, crypt(p, salt)) == 0)
                    {
                        printf("The Correct Key is %s\n", p);
                        return (0);
                        exit(0);
                    }
                    break;
                }
            }
        }
    }
    else
    {
        printf("Error, please input only one command line argument: a hashed password\n");
        return (1);
    }
}