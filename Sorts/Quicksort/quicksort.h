/**
 * @author Daniel Sebastian Iliescu
 * @file quicksort.h
 */

#pragma once

#include "datasort.h"

/**
 * QuickSorter
 *
 * Class implementing the Quick Sort algorithm.
 */
class QuickSorter : public DataSorter
{
public:
    QuickSorter();
    virtual ~QuickSorter();

    virtual bool quickSort(int* data, int dataSize);
};
