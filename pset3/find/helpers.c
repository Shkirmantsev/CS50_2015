/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

#define SWAP(A, B) { int t = A; A = B; B = t; }

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Finding needle
    
    //First element of array
    
    size_t first = 0;
    
    /* Next after last element of array */
    size_t last = n;
    
    if (n == 0)
    {
        /* ampty array */
        return false;
    }
    else if (values[0] > value)
    {
        /* sought-for element is larger then all elements */
        return false;
    }
    else if (values[n - 1] < value)
    {
        /* sought-for element is smoller then all elements */
        return false;
    }
    
    /* if array is not ampty, first < last */
    
    while (first < last)
    {
        size_t mid = first + ((last - first) / 2);

        if (value < values[mid]) last = mid;
        else if(value == values[mid])
        {
            return true;
            break;
        }
        else first = mid + 1;
        
    }
    if (values[last] == value)
    {
        /* element is found */
        return true;
    }
    
    else /* element is not found */ return false; 
}  

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // sorting array implement an O(n^2) sorting algorithm
    int i, j;

    for (i = n - 1; i >= 0; i--)
    {
        for (j = 0; j < i; j++)
        {
        if (values[j] > values[j + 1])
            {
                SWAP( values[j], values[j + 1] );
            }
        }
    }
         
}
