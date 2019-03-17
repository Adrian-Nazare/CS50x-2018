// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "dictionary.h"

typedef struct _trie
    {
        bool found;
        struct _trie *letter[27];

    } node;
node *root;
node *ptr;

void addup (node *pointer, int *s)
    {
        if (pointer -> found == true)
        *s = *s + 1;
        for (int i = 0; i < 27; i++)
        {
            if (pointer -> letter[i] != NULL)
            {
                addup (pointer -> letter[i], s);
            }
        }
    }

void destroy (node *pointer)
{
    for (int i = 0; i < 27; i++)
    {
        if (pointer -> letter[i] != NULL)
        destroy (pointer -> letter[i]);
    }
    free (pointer);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    ptr = root;
    for (int i = 0; i < strlen (word); i++)
    {
        //check for apostrophe
        if (word[i] == 39)
        {
            if (ptr -> letter[26] != NULL)
            {ptr = ptr -> letter[26];}
            else return false;
        }
        //check for uppercase
        else if (word[i] >= 65 && word[i] <= 90)
        {
            if (ptr -> letter[word[i]-65] != NULL)
            {ptr = ptr -> letter[word[i]-65];}
            else return false;
        }
        //check for lowercase
        else
        {
            if (ptr -> letter[word[i]-97] != NULL)
            {ptr = ptr -> letter[word[i]-97];}
            else return false;
        }

    }
    if (ptr -> found == true)
    return true;
    else return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = calloc (1, sizeof(node));
    if (!root) return false;
    ptr = root;

    FILE *file = fopen(dictionary, "r");
    if (!file) return false;

    for (int a = fgetc(file); a != EOF; a = fgetc(file))
    {
        //if end of the line is reached, it means a new word is completed
        if (a == 0x0a)
        {ptr -> found = true; ptr = root;}
        else
        {
            //if character is an apostrophe, assign it on the last node of trie
            if (a == 0x27)
            {
                if (ptr->letter[26] == NULL)
                {
                    ptr->letter[26] = calloc (1, sizeof(node));
                    ptr = ptr->letter[26];
                }
                else ptr = ptr->letter[26];
            }
            //if it's a letter (always lowercase), assign it to the corresponding node
            else
            {
                if (ptr->letter[a - 97] == NULL)
                {
                    ptr->letter[a - 97] = calloc (1, sizeof(node));
                    ptr = ptr->letter[a - 97];
                }
                else ptr = ptr->letter[a - 97];
            }
        }
    }
    fclose (file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!root) return 0;
    //declaring a pointer to an int so that it can be modified outside of the function
    int *s = calloc (1, sizeof (unsigned int));
    *s = 0;
    addup (root, s);
    int sum = *s;
    free (s);
    return sum;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!root) return 0;
    destroy (root);
    return true;
}
