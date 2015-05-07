/**
 * @author Daniel Sebastian Iliescu
 * @file recursivemergesort.cpp
 *
 * This file contains the methods associated with the RecursiveMergeSorter
 * class.
 */
#include <cmath>
#include <cstring>
#include <iostream>

#include "recursivemergsort.h"

using namespace std;

/**
 * RecursiveMergeSorter()
 *
 * Default constructor
 */
RecursiveMergeSorter::RecursiveMergeSorter()
{
}

/**
 * ~RecursiveMergeSorter()
 *
 * Destructor
 */
RecursiveMergeSorter::~RecursiveMergeSorter()
{
}

/**
 * mergeSort(int* data, int dataSize)
 *
 * Method for sorting data according to Merge Sort algorithm
 * (recursive version).
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool RecursiveMergeSorter::mergeSort(int* data, int dataSize)
{
    if ((data == NULL) || (dataSize <= 1))
    {
        return false;
    }

    int* temp = new int[dataSize];

    recursiveMergeSort(data, temp, 0, dataSize);

    delete [] temp;
    return true;
}

/**
 * recursiveMergeSort(int* data, int* temp, int start, int end)
 *
 * Helper method for recursively sorting data within two array
 * boundaries based on Merge Sort algorithm
 *
 * @param data The array containing the data to sort.
 * @param temp Temporary array used as working memory.
 * @param start Index of first element to sort
 * @param end Index of last element to sort
 * @pre data array should be valid (not NULL)
 * @post data array is sorted within given limits
 */
void RecursiveMergeSorter::recursiveMergeSort(
    int* data,
    int* temp,
    int start,
    int end)
{
    if ((data != NULL) && (temp != NULL) &&
        (start >= 0) && ((start + 1) < end))
    {
        int middle = (start + end)/2;
        recursiveMergeSort(data, temp, start, middle);
        recursiveMergeSort(data, temp, middle, end);
        merge(data, temp, start, middle, end);
        for (int i = start; i < end; i++)
        {
            data[i] = temp[i];
        }
    }
}
