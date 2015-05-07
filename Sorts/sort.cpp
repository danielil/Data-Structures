/**
 * @author Daniel Sebastian Iliescu
 * @file datasort.cpp
 *
 * This file contains the methods associated with the DataSorter class.
 */

#include <cmath>
#include <cstring>
#include <iostream>

#include "datasort.h"

using namespace std;

/**
 * DataSorter()
 *
 * Default constructor
 */
DataSorter::DataSorter()
{
}

/**
 * ~DataSorter()
 *
 * Destructor
 */
DataSorter::~DataSorter()
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
bool DataSorter::bubbleSort(int* data, int dataSize)
{
    // Not implemented in this class
    return false;
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
bool DataSorter::quickSort(int* data, int dataSize)
{
    // Not implemented in this class
    return false;
}

/**
 * heapSort(int* data, int dataSize)
 *
 * Method for sorting data according to Heap Sort algorithm.
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool DataSorter::heapSort(int* data, int dataSize)
{
    // Not implemented in this class
    return false;
}

/**
 * mergeSort(int* data, int dataSize)
 *
 * Method for sorting data according to Merge Sort algorithm.
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is sorted
 * @return True if data was sorted; false otherwise.
 */
bool DataSorter::mergeSort(int* data, int dataSize)
{
    // Not implemented in this class
    return false;
}

/**
 * show(ostream& output, int* data, int dataSize)
 *
 * Helper method for pushing the data into an output stream.
 *
 * @param output Output stream
 * @param data The array containing the data.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL)
 * @post data array is pushed into the stream.
 */
void DataSorter::show(ostream& output, int* data, int dataSize)
{
    show(output, data, dataSize, 0, dataSize - 1);
}

/**
 * show(ostream& output, int* data, int dataSize, int start, int end)
 *
 * Helper method for pushing the data into an output stream.
 *
 * @param output Output stream
 * @param data The array containing the data.
 * @param dataSize The number of elements in data array
 * @param start Index of first element to show
 * @param end Index of last element to show
 * @pre data array should be valid (not NULL)
 * @post data array is pushed into the stream.
 */
void DataSorter::show(
    ostream& output,
    int* data,
    int dataSize,
    int start,
    int end)
{
    if ((data != NULL) && (dataSize > 0) && (start >= 0))
    {
        output << "\tData size: " << dataSize;
        for (int i = 0, j = start; j < dataSize; i++, j++)
        {
            if (j > end)
            {
                output << "\t...";
                break;
            }
            else if ((i % 4) == 0)
            {
                output << "\r\n";
            }
            output << "\t";
            output << data[j];
        }
        output << "\r\n";
    }
}

/**
 * copy(int* dest, int* source, int start, int end)
 *
 * Helper method for copying data from one array to another.
 *
 * @param dest The array to which the data is copied.
 * @param source The array supplying the data to copy.
 * @param dataSize The number of elements in data array
 * @param start Index of first element to copy
 * @param end Index of last element to copy
 * @pre data arrays should be valid (not NULL)
 * @post data is copied from one array to another.
 */
void DataSorter::copy(int* dest, int* source, int start, int end)
{
    if ((dest != NULL) && (source != NULL) && (start >= 0) && (start <= end)) 
    {
        for (int i = start; i <= end; i++)
        {
            dest[i] = source[i];
        }
    }
}

/**
 * swap(int* data, int index1, int index2)
 *
 * Helper method for swapping two elements within an array.
 *
 * @param data The array containing the data to swap.
 * @param index1 Index of first element
 * @param index2 Index of second element
 * @pre data arrays should be valid (not NULL)
 * @post The array locations are swapped.
 */
void DataSorter::swap(int* data, int index1, int index2)
{
    if ((data != NULL) && (index1 >= 0) && (index2 >= 0) && (index1 != index2))
    {
        int temp = data[index1];
        data[index1] = data[index2];
        data[index2] = temp;
    }
}

/**
 * merge(int* source, int* dest, int start, int middle, int end)
 *
 * Helper method for sort merging two adjacent groups of elements
 * within an array.
 *
 * @param source The array supplying the data to merge.
 * @param dest The array to which the merged data is copied.
 * @param start Index of first element to merge
 * @param middle Index of middle position defining the merge boundary 
 * @param end Index of last element to merge
 * @pre data arrays should be valid (not NULL)
 * @post data is merged and copied from one array to another.
 */
void DataSorter::merge(int* source, int* dest, int start, int middle, int end)
{
    if ((source != NULL) && (dest != NULL) &&
        (start >= 0) && (start < middle) && (middle < end))
    {
        int j1 = start;
        int j2 = middle;

        for (int i = start; i < end; i++)
        {
            if ((j1 < middle) && ((j2 >= end) || (source[j1] <= source[j2])))
            {
                dest[i] = source[j1];
                ++j1;
            }
            else
            {
                dest[i] = source[j2];
                ++j2;
            }
        }
    }
}

/**
 * partition(int* data, int dataSize, int start, int end, int pivot)
 *
 * Helper method for partitioning data within two boundaries as needed
 * by the Quick Sort algorithm. The data is dispersed based on selected
 * pivot (data smaller than the pivot is pushed to the left, while data
 * larger than the pivot is pushed to the right).
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @param start Index of first element to sort
 * @param end Index of last element to sort
 * @param pivot Index of element elected as partion pivot
 * @pre data array should be valid (not NULL)
 * @post data array is sorted
 * @return The new position of the pivot element.
 */
int DataSorter::partition(
    int* data,
    int dataSize,
    int start,
    int end,
    int pivot)
{
    int position = pivot;

    if ((data != NULL) && (start >= 0) && (start < end) &&
        (end < dataSize) && (pivot >= start) && (pivot <= end))
    {
        int pivotValue = data[pivot];

        swap(data, pivot, end);         // move pivot to the rightmost end
        position = start;

        for (int i = start; i <= (end - 1); i++)
        {
            if (data[i] <= pivotValue)
            {
                swap(data, i, position);
                ++position;
            }
        }
        swap(data, position, end);    // move pivot to its final position
    }

    return position;
}

/**
 * recursiveQuickSort(int* data, int dataSize, int start, int end)
 *
 * Helper method for sorting data recursively based on Quick Sort algorithm.
 *
 * @param data The array containing the data to sort.
 * @param dataSize The number of elements in data array
 * @param start Index of first element to sort
 * @param end Index of last element to sort
 * @pre data array should be valid (not NULL)
 * @post data array is sorted
 */
void DataSorter::recursiveQuickSort(
    int* data,
    int dataSize,
    int start,
    int end)
{
    if ((data != NULL) && (start >= 0) && (start < end) && (end <= dataSize))
    {
        int pivot = partition(data, dataSize, start, end, ((start + end) / 2));
        recursiveQuickSort(data, dataSize, start, pivot - 1);
        recursiveQuickSort(data, dataSize, pivot + 1, end);
    }
}

/**
 * bubbleSortHelper(int* source, int* dest, int dataSize)
 *
 * Helper method for sorting data according to Bubble Sort algorithm.
 *
 * @param source The array supplying the data to sort.
 * @param dest The array to which the sorted data is copied.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL)
 * @post source data array is sorted and its content
 * is transfered to destination array.
 */
void DataSorter::bubbleSortHelper(int* source, int* dest, int dataSize)
{
    if ((source != NULL) && (dataSize > 0))
    {
        if (dataSize > 1)
        {
            bool sorted = false;
            while (!sorted)
            {
                sorted = true;
                for (int i = 0; i < (dataSize - 1); i++)
                {
                    if (source[i] > source[i + 1])
                    {
                        sorted = false;
                        swap(source, i, i + 1);
                    }
                }
            }
        }

        if (dest != NULL) 
        {
            copy(dest, source, 0, dataSize - 1);
        }
    }
}
