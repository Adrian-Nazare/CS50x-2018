// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "dictionary.h"

typedef struct hash_chain
{
    char *string;
    struct hash_chain *next;

} node;

void calculator (node *ptr, unsigned int *s)
{
    if (ptr -> next != NULL)
        calculator (ptr -> next, s);
    *s = *s + 1;
}

void destroy (node *ptr)
{
    if (ptr -> next != NULL)
        destroy (ptr -> next);
    free (ptr);
}

node *ptr;
node *hashtable[25000];
char *dword;
unsigned long *s;

bool check(const char *word)
{   int f;
    char *small_word = malloc (strlen(word) * sizeof(char));
    int length = strlen(word);
    *s = 0;
    for (int i = 0; i < length; i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
            small_word[i] = word[i] + 32;
        else small_word[i] = word [i];
        *s = *s + word[i] * i * i;
    }
    f = *s % 25000;
    ptr = hashtable[f];
    while (ptr -> next != NULL)
    {
        if (strcmp (ptr -> string, small_word) == 0)
            return true;
        ptr = ptr -> next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int i, f, a;
    FILE *file = fopen(dictionary, "r");
    ptr = NULL;
    for (i = 0; i < 25000; i++)
        hashtable[i] = calloc (1, sizeof(node));
    dword = malloc (46 * sizeof(char));
    s = malloc (sizeof(int));
    if ((!file) || (!hashtable[0]) || (!dword) || (!s)) return false;
    i = 0; *s = 0;
    do
    {
        a = fgetc(file);
        if (a == 0x0a)
        {
            dword[i] = '\0';
            f = *s % 25000;
            i = 0; *s = 0;
            if (hashtable[f] -> next == NULL)
            {
                hashtable[f] -> next = calloc (1, sizeof(node));
                hashtable[f] -> string = malloc (strlen(dword) * sizeof(char));
                strcpy (hashtable[f] -> string, dword);
            }
            else
            {
                ptr = hashtable[f];
                while (ptr -> next != NULL)
                    ptr = ptr -> next;
                ptr -> next = calloc (1, sizeof(node));
                ptr -> string = malloc (strlen(dword) * sizeof(char));
                strcpy (ptr -> string, dword);
            }
        }
        else
        {
            dword[i] = a;
            *s = *s + a * i * i;
            i++;
        }
    } while (a != EOF);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int *sum = malloc (sizeof (unsigned int));
    *sum = 0;
    for (int i = 0; i < 25000; i++)
        calculator (hashtable[i], sum);
    int total = *sum;
    return total;
    free (sum);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i;
    for (i = 0; i < 25000; i++)
        destroy (hashtable[i]);
    if (i == 25000)
        return 1;
    else return 0;
}
