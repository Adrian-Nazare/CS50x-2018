// Helper functions for music

#include <cs50.h>
#include "helpers.h"
#include <math.h>
#include <string.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    return ((int) round(8*((float) atoi(&fraction[0]) / (float) atoi(&fraction[2]))));
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char notes[13] = {'C', 0, 'D', 0, 'E', 'F', 0, 'G', 0, 'A', 0, 'B'};
    int i;
    for (i = 0; i < 12; i++)
        {
            if (note[0] == notes[i])
            break;
        }
    if (strlen(note) == 2)
    {
         return (int) round(pow(2, ((float) (12 * (atoi(&note[1])) - (12 - i) - 45) / 12)) * 440);
    }
    else if (strlen(note) == 3)
        if (note[1] == '#')
        {
            return (int) round(pow(2, ((float) (12 * (atoi(&note[2])) - (11 - i) - 45) / 12)) * 440);
        }
        else if (note[1] == 'b')
        {
            return (int) round(pow(2, ((float) (12 * (atoi(&note[2])) - (13 - i) - 45) / 12)) * 440);
        }
        else return 1;
    else return 1;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "")) return false;
    else return true;
}
