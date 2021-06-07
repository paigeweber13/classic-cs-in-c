//
// Created by Paige Riley Weber on 6/4/21.
//

#ifndef SORTING_ALGORITHMS_SORT_ALGORITHMS_H
#define SORTING_ALGORITHMS_SORT_ALGORITHMS_H

#include <stdlib.h>
#include <string.h>

#include "utils.h"

void insertionSort(float* arr, size_t n);
void mergeSort(float* arr, size_t n);
void mergeSortParallel(float* arr, size_t n);
void heapSort(float* arr, size_t n);
void quickSort(float* arr, size_t n);

#endif //SORTING_ALGORITHMS_SORT_ALGORITHMS_H
