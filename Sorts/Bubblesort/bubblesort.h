/**
 * @author Daniel Sebastian Iliescu
 * @file bubblesort.h
 */

#pragma once

#include "datasort.h"

/**
 * BubbleSorter
 *
 * Class implementing the Bubble Sort algorithm.
 */
class BubbleSorter : public DataSorter
{
public:
    BubbleSorter();
    virtual ~BubbleSorter();

    virtual bool bubbleSort(int* data, int dataSize);
};
