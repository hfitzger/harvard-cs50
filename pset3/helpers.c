/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) // TODO: implement a searching algorithm
{ 
    int start = 0; // declare all the ints you will be using (start,mid,end) and the math associated with them
    int end = (n - 1);
    int middle = (start + end) / 2;
     
    while (end >= start)           //while length of list > 0
    {          
        if (values[middle] == value) //look at middle of list (if mid of array is same as value then return true)
        {
            return true;
        }
        else if (value < values[middle]) //else if value is smaller than mid of array (remember math; end/mid)
        {
            end = middle - 1;
            middle = (start + end) / 2;
        }
        else if (values[middle] < value)//else if value is bigger than mid of array (remember math; start/mid)
        {
            start = middle + 1;
            middle = (start + end) / 2;
        }
        else //else break
        {
            break; 
        }
    }   
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) // TODO: implement a sorting algorithm
//define sorting variables   //values [0] - values[n-1] is the array we are sorting
{
    for (int i = 1; i < n; i++) //iterate through entire array
    {
        //find the smallest element
        int small = values[i];
        int j = (i - 1);
        
        while ((small < values[j]) && (j >= 0))
        {
            values[j + 1] = values[j];
            j--;
        }
        
    values[j + 1] = small;
    }   
    
    return;
}
