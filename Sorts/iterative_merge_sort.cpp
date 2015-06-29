/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods associated with the IterativeMergeSort class.
 */
#include <algorithm>
#include <iostream>

#include "iterative_merge_sort.hpp"

using namespace std;

/**
 * IterativeMergeSort()
 *
 * Default constructor
 */
IterativeMergeSort::IterativeMergeSort()
{
}

/**
 * ~IterativeMergeSort()
 *
 * Destructor
 */
IterativeMergeSort::~IterativeMergeSort()
{
}

/**
 * mergeSort(int* data, int dataSize)
 *
 * Method for sorting data according to Merge Sort algorithm
 * (basic iterative version).
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool IterativeMergeSort::mergeSort(int* data, int dataSize)
{
    return mergeSort(data, dataSize, false, 0);
}

/**
 * mergeSort(int* data, int dataSize)
 *
 * Method for sorting data according to Merge Sort algorithm
 * (optimized iterative version).
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @param bubbleMode Optimization mode (Bubble vs. Quick)
 * @param switchThresholde Optimization threshold
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool IterativeMergeSort::mergeSort(int* data, int dataSize, bool bubbleMode, int switchThreshold)
{
    if ((data == nullptr) || (dataSize <= 1))
    {
        return false;
    }

    int* temp = new int[dataSize];
    bool tempSource = false;

    for (int width = 1; width < dataSize; width *= 2)
    {
        int* source = tempSource ? temp : data;
        int* dest = tempSource ? data : temp;
        int start = 0;
        int mid = start + width;
        int end = min(dataSize, mid + width);

        if (mid >= dataSize)
        {
            break;
        }

        // do merge sort
        while (mid < dataSize)
        {
            optimizedMerge(source, dest, start, mid, end, bubbleMode, switchThreshold);
            start = end;
            mid = start + width;
            end = min(dataSize, mid + width);
        }

        // copy over what the data left un-merged
        copy(dest, source, start, dataSize - 1);

        // toggle the flag indicatig the source
        tempSource = !tempSource;
    }

    if (tempSource)
    {
        copy(data, temp, 0, dataSize - 1);
    }

    delete [] temp;
    return true;
}

/**
 * optimizedMerge(int* source, int* dest, int start, int middle, int end,
                  bool bubbleMode, int switchThreshold)
 *
 * Helper method for optimized sort merging of two adjacent groups of
 * elements within an array.
 *
 * @param source The array supplying the data to merge.
 * @param dest The array to which the merged data is copied.
 * @param start Index of first element to merge
 * @param middle Index of middle position defining the merge boundary 
 * @param end Index of last element to merge
 * @param bubbleMode Optimization mode (Bubble vs. Quick)
 * @param switchThreshold Max. size at which optimization will be applied
 * @pre data arrays should be valid (not NULL)
 * @post data is merged and copied from one array to another.
 */
void IterativeMergeSort::optimizedMerge(
    int* source,
    int* dest,
    int start,
    int middle,
    int end,
    bool bubbleMode,
    int switchThreshold)
{
    if ((source != nullptr) && (dest != nullptr) &&
        (start >= 0) && (start < middle) && (middle < end))
    {
        if ((switchThreshold > 2) && ((end - start) <= switchThreshold))
        {
            if (bubbleMode)
            {
                bubbleSortHelper(&source[start], &dest[start], (end - start));
            }
            else
            {
                quickSortHelper(&source[start], &dest[start], (end - start));
            }
        }
        else
        {
            merge(source, dest, start, middle, end);
        }
    }
}

/**
 * quickSortHelper(int* source, int* dest, int dataSize)
 *
 * Helper method for sorting data according to Quick Sort algorithm.
 *
 * @param source The array supplying the data to sort.
 * @param dest The array to which the sorted data is copied.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL)
 * @post source data array is sorted and its content
 * is transfered to destination array.
 */
void IterativeMergeSort::quickSortHelper(int* source, int* dest, int dataSize)
{
    if ((source != nullptr) && (dataSize > 0))
    {
        if (dataSize > 1)
        {
            recursiveQuickSort(source, dataSize, 0, dataSize - 1);
        }
        if (dest != nullptr)
        {
            copy(dest, source, 0, dataSize - 1);
        }
    }
}
