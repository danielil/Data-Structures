/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "sort.hpp"

/**
 * HeapSort
 *
 * Class implementing the Heap Sort algorithm.
 */
class HeapSort : public Sort
{
public:
    HeapSort();
    virtual ~HeapSort();

    bool heapSort(int* data, int dataSize) override;

private:
    static void heapify(int* data, int dataSize);
    static void siftDown(int* data, int start, int end);
};
