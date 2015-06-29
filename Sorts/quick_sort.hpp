/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "sort.hpp"

/**
 * QuickSort
 *
 * Class implementing the Quick Sort algorithm.
 */
class QuickSort : public Sort
{
public:
    QuickSort();
    virtual ~QuickSort();

    virtual bool quickSort(int* data, int dataSize) override;
};
