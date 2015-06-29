/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "sort.hpp"

/**
 * BubbleSort
 *
 * Class implementing the Bubble Sort algorithm.
 */
class BubbleSort : public Sort
{
public:
    BubbleSort();
    virtual ~BubbleSort();

    virtual bool bubbleSort(int* data, int dataSize) override;
};
