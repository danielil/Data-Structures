/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods associated with the HeapSort class.
 */

#include <cmath>

#include "heap_sort.hpp"

using namespace std;

/**
 * HeapSort()
 *
 * Default constructor
 */
HeapSort::HeapSort()
{
}

/**
 * ~HeapSort()
 *
 * Destructor
 */
HeapSort::~HeapSort()
{
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
bool HeapSort::heapSort(int* data, int dataSize)
{
    if ((data == nullptr) || (dataSize <= 1))
    {
        return false;
    }

    int end = dataSize - 1;

    heapify(data, dataSize);

    while (end > 0)
    {
        swap(data, 0, end);
        end--;
        siftDown(data, 0, end);
    }

    return true;
}

/**
 * heapify(int* data, int dataSize)
 *
 * Helper method for organizing an array as heap suitable for Heap sorting.
 *
 * @param data The array containing the data to heapify.
 * @param dataSize The number of elements in data array
 * @pre data array should be valid (not NULL and size > 1)
 * @post data array is transformed into a heap
 */
void HeapSort::heapify(int* data, int dataSize)
{
    if ((data != nullptr) && (dataSize >= 2))
    {
        // Get the assigned the index in a of the last parent node
        int start = (dataSize - 2) / 2;

        while (start >= 0)
        {
            // sift down the node at index start to the proper place such
            // that all nodes below the start index are in heap order
            siftDown(data, start, dataSize - 1);
            start--;
        }

        // After sifting down the root all nodes/elements are in heap order
    }
}

/**
 * siftDown(int* data, int start, int end)
 *
 * Helper method to SIFT DOWN the root node in the heap tree until all its
 * children are smaller. It successively exchanges the root value with the
 * smaller of its two children. The operation continues until the value
 * reaches a position where it is less than both its children, or,
 * failing that, until it reaches a leaf.
 *
 * @param data The array containing the data to SIFT DOWN.
 * @param start The left boundary of the heap
 * @param end The right boundary of the heap
 * @pre data array should be valid (not NULL)
 * @post data array is re-arranged within given boundaries
 */
void HeapSort::siftDown(int* data, int start, int end)
{
    if ((data != nullptr) && (start >= 0) && (start <= end))
    {
        int root = start;

        while ((root * 2 + 1) <= end) 
        {
            // While root has at least one child:
            int child = root * 2 + 1;   // left child
            int temp = root;            // keeps track of child to swap with

            if (data[temp] < data[child])
            {
                temp = child;
            }

            if (((child + 1) <= end) && (data[temp] < data[child + 1]))
            {
                temp = child + 1;
            }

            if (temp == root)
            {
                break;
            }

            // Continue sifting down the child now
            swap(data, root, temp);
            root = temp;
        }
    }
}
