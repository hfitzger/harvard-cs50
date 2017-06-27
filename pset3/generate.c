/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // print error if argument count doesn't equal 2 and 3
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // interpret characters in array[1] to an integer
    int n = atoi(argv[1]);

    // if argument count equals 3, ???
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else //if argument count doesn't equal 3, ???
    {
        srand48((long) time(NULL));
    }

    
    for (int i = 0; i < n; i++) //for loop interpreting over each char in argv[1]
    {
        printf("%i\n", (int) (drand48() * LIMIT)); //print ????
    }

    // success
    return 0;
}
