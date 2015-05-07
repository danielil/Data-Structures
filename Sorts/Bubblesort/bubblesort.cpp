/**
 * @author Daniel Sebastian Iliescu
 * @file bubblesort.cpp
 *
 * This file contains the methods associated with the BubbleSorter class.
 */

#include <cmath>
#include <cstring>
#include <iostream>

#include "bubblesort.h"

using namespace std;

/**
 * BubbleSorter()
 *
 * Default constructor
 */
BubbleSorter::BubbleSorter()
{
}

/**
 * ~BubbleSorter()
 *
 * Destructor
 */
BubbleSorter::~BubbleSorter()
{
}

/**
 * bubbleSort(int* data, int dataSize)
 *
 * Method for sorting data according to Bubble Sort algorithm.
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool BubbleSorter::bubbleSort(int* data, int dataSize)
{
    if ((data == NULL) || (dataSize <= 1))
    {
        return false;
    }

    bubbleSortHelper(data, NULL, dataSize);

    return true;
}
