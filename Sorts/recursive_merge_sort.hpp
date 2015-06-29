/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "sort.hpp"

/**
 * RecursiveMergeSort
 *
 * Class implementing the recursive version of Merge Sort algorithm.
 */
class RecursiveMergeSort : public Sort
{
public:
    RecursiveMergeSort();
    virtual ~RecursiveMergeSort();
 
    virtual bool mergeSort(int* data, int dataSize) override;

private:
    static void recursiveMergeSort(int* data, int* temp, int start, int end);
};
