/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods associated with the BubbleSort class.
 */

#include <cmath>

#include "bubble_sort.hpp"

using namespace std;

/**
 * BubbleSort()
 *
 * Default constructor
 */
BubbleSort::BubbleSort()
{
}

/**
 * ~BubbleSort()
 *
 * Destructor
 */
BubbleSort::~BubbleSort()
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
bool BubbleSort::bubbleSort(int* data, int dataSize)
{
    if ((data == nullptr) || (dataSize <= 1))
    {
        return false;
    }

    bubbleSortHelper(data, nullptr, dataSize);

    return true;
}
