//
// Created by Paige Riley Weber on 6/4/21.
//

#ifndef SORTING_ALGORITHMS_UTILS_H
#define SORTING_ALGORITHMS_UTILS_H

#include <stdlib.h>
#include <time.h>

typedef unsigned long UL;

#define TRUE 1
#define FALSE 0

#define ALIGNMENT (size_t) 64
//#define ALIGNMENT 64

// fast pseudo-random number generator taken from
// http://www.cse.yorku.ca/~oz/marsaglia-rng.html
#define znew (z=36969*(z&65535)+(z>>16))
#define wnew (w=18000*(w&65535)+(w>>16))
#define MWC ((znew<<16)+wnew )
#define fastRand MWC

// enums for sorting types array types
typedef enum {
  sortInsertion, sortMerge, sortMergeParallel, sortHeap, sortQuick,
  sortQuickModified
} SortAlgorithm;

typedef enum {
  initRandom, initSorted, initReverse
} ArrayType;

// seed random numbers
static UL z=362436069, w=521288629;

// used for swap: only allocate once
float temp;

int compare(float a, float b);
void swap(float* a, float* b);
int isArraySorted(float* arr, size_t n);

// these functions expect memory to already be allocated, they just change
// the contents
void generateRandomArray(float* arr, size_t n);
void generateSortedArray(float* arr, size_t n);
void generateReverseSortedArray(float* arr, size_t n);

float* printArray(float* arr, size_t n);

#endif //SORTING_ALGORITHMS_UTILS_H
