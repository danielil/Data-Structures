/**
 * @author Daniel Sebastian Iliescu
 * @file quicksort.cpp
 *
 * This file contains the methods associated with the QuickSorter class.
 */
#include <cmath>
#include <cstring>
#include <iostream>

#include "quicksort.h"

using namespace std;

/**
 * QuickSorter()
 *
 * Default constructor
 */
QuickSorter::QuickSorter()
{
}

/**
 * ~QuickSorter()
 *
 * Destructor
 */
QuickSorter::~QuickSorter()
{
}

/**
 * quickSort(int* data, int dataSize)
 *
 * Method for sorting data according to Quick Sort algorithm.
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool QuickSorter::quickSort(int* data, int dataSize)
{
    if ((data == NULL) || (dataSize <= 1))
    {
        return false;
    }

    recursiveQuickSort(data, dataSize, 0, dataSize - 1);
    return true;
}
