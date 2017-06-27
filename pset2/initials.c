#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string name = GetString(); // ask user for input
    if (name != NULL) // make sure GetString returns a string
    {
        for (int i = 0, n = strlen(name); i < n; i++) // iterate over the character in name one at a time
        {
            if (i == 0 || name[i-1] == ' ')
            {
            printf("%c", toupper (name[i])); //print i'th char in s
            }
        }
    }    
    printf("\n");
}
