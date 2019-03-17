// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "dictionary.h"

typedef struct _hashtable
    {
        char *string;
        struct _hashtable *next;
    } node;

int hash_function (char *word)
{
    int length = strlen (word);
    if (length > 5)
        length = 5;
    int total = 0;
    for (int i = 0; i < length; i++)
    {
        total = total * 10 + word[i];
    }
    total = total % 25000;
    return total;
}

void destroy(node *ptr)
{
    if (ptr)
        {
            destroy (ptr -> next);
            free (ptr -> string);
            free (ptr);
        }
}
// Returns true if word is in dictionary else false
node *hashtable[25000];

bool check(const char *word)
{
    int total_length = strlen(word) + 1;
    char *small_word = malloc (total_length * sizeof(char));
    for (int i = 0; i < total_length; i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
            small_word[i] = word[i] + 32;
        else small_word[i] = word [i];
    }
    int hash_index = hash_function(small_word);
    node *ptr = hashtable[hash_index];
    while (ptr)
    {
        if (strcmp (ptr -> string, small_word) == 0)
        {
            free (small_word);
            return true;
        }
        ptr = ptr -> next;
    }
    free (small_word);
    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int word_index = 0;
    int hash_index = 0;
    for (int i = 0; i < 25000; i++)
        hashtable[i] = NULL;
    node *ptr;
    char *dword = malloc (46 * sizeof(char));
    FILE *file = fopen (dictionary, "r");
    if ((!file) || (!dword)) return false;
    for (int a = fgetc(file); a != EOF; a = fgetc(file))
    {
        if (a == 10)
        {
            dword[word_index] = '\0';
            hash_index = hash_function(dword);
            if (hashtable[hash_index] == NULL)
            {
                hashtable[hash_index] = malloc (sizeof(node));
                hashtable[hash_index] -> string = malloc ((word_index + 1) * sizeof(char));
                for (int j = 0; j <= word_index; j++)
                    hashtable[hash_index] -> string[j] = dword[j];
               // strcpy (hashtable[hash_index] -> string, dword);
                hashtable[hash_index] -> next = NULL;
            }
            else
            {
                ptr = hashtable[hash_index];
                while (ptr -> next != NULL)
                {
                    ptr = ptr -> next;
                }
                ptr -> next = malloc (sizeof(node));
                ptr = ptr -> next;
                ptr -> string = malloc ((word_index + 1) * sizeof(char));
                for (int j = 0; j <= word_index; j++)
                    ptr -> string[j] = dword[j];
                //strcpy (ptr -> string, dword);
                ptr -> next = NULL;
            }
            word_index = 0;
        }
        else
        {
            dword[word_index] = a;
            word_index++;
        }
    }
    free(dword);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node *ptr;
    int words = 0;
    for (int i = 0; i < 25000; i++)
    {
        ptr = hashtable[i];
        while (ptr)
        {
            words ++;
            ptr = ptr -> next;
        }
    }
    return words;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i;
    for (i = 0; i < 25000; i++)
        destroy (hashtable[i]);
    return true;
}
