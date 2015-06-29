/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "sort.hpp"

/**
 * IterativeMergeSort
 *
 * Class implementing three versions of Merge Sort algorithm:
 * 1. Basic iterative version (no optimizations)
 * 2. Iterative version with optimizations based on Bubble sort.
 * 3. Iterative version with optimizations based on Quick sort.
 */
class IterativeMergeSort : public Sort
{
public:
    IterativeMergeSort();
    virtual ~IterativeMergeSort();
 
    virtual bool mergeSort(int* data, int dataSize) override;
    virtual bool mergeSort(
        int* data, int dataSize, bool bubbleMode, int switchThreshold);

private:
    static void optimizedMerge(
        int* source, int* dest, int start, int middle, int end,
        bool bubbleMode, int switchThreshold);
    static void quickSortHelper(int* source, int* dest, int dataSize);
};
