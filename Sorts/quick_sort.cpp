/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods associated with the QuickSort class.
 */
#include <cmath>

#include "quick_sort.hpp"

using namespace std;

/**
 * QuickSort()
 *
 * Default constructor
 */
QuickSort::QuickSort()
{
}

/**
 * ~QuickSort()
 *
 * Destructor
 */
QuickSort::~QuickSort()
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
bool QuickSort::quickSort(int* data, int dataSize)
{
    if ((data == nullptr) || (dataSize <= 1))
    {
        return false;
    }

    recursiveQuickSort(data, dataSize, 0, dataSize - 1);
    return true;
}
