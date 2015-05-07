/**
 * @author Daniel Sebastian Iliescu
 * @file heapsort.h
 */

#pragma once

#include "datasort.h"

/**
 * HeapSorter
 *
 * Class implementing the Heap Sort algorithm.
 */
class HeapSorter : public DataSorter
{
public:
    HeapSorter();
    virtual ~HeapSorter();

    bool heapSort(int* data, int dataSize);

private:
    static void heapify(int* data, int dataSize);
    static void siftDown(int* data, int start, int end);
};
