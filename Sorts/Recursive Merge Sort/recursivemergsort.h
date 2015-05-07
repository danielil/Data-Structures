/**
 * @author Daniel Sebastian Iliescu
 * @file recursivemergesort.h
 */

#pragma once

#include "datasort.h"

/**
 * RecursiveMergeSorter
 *
 * Class implementing the recursive version of Merge Sort algorithm.
 */
class RecursiveMergeSorter : public DataSorter
{
public:
    RecursiveMergeSorter();
    virtual ~RecursiveMergeSorter();
 
    virtual bool mergeSort(int* data, int dataSize);

private:
    static void recursiveMergeSort(int* data, int* temp, int start, int end);
};
