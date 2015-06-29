/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once
#include <iostream>

/**
 * Sort
 *
 * Base class for all sorting algorithms.
 * It implements the basic helper methods.
 */
class Sort
{
public:
    Sort();
    virtual ~Sort();

    virtual bool bubbleSort(int* data, int dataSize);
    virtual bool quickSort(int* data, int dataSize);
    virtual bool heapSort(int* data, int dataSize);
    virtual bool mergeSort(int* data, int dataSize);
    
    static void show(std::ostream& output, int* data, int dataSize);
    static void show(std::ostream& output, int* data, int dataSize, int start, int end);
    static void copy(int* dest, int* source, int start, int end);

protected:
    static void swap(int* data, int index1, int index2);
    static void merge(int* source, int* dest, int start, int middle, int end);
    static int partition(int* data, int dataSize, int start, int end, int pivot);
    static void recursiveQuickSort(int* data, int dataSize, int start, int end);
    static void bubbleSortHelper(int* source, int* dest, int dataSize);
};
