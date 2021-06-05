//
// Created by Paige Riley Weber on 6/5/21.
//

#ifndef SORTING_ALGORITHMS_TEST_H
#define SORTING_ALGORITHMS_TEST_H

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "utils.h"

typedef struct TestResult {
  SortAlgorithm sortAlgorithm;
  ArrayType arrayType;
  size_t numRuns;
  size_t arraySize;
  double runTime;
} TestResult;

void printResultHeader();

void testSortMulti(SortAlgorithm sortAlgorithm, ArrayType
                   arrayType, size_t sizeInit, size_t sizeFinal);

// returns runtime of test
double testSortSingle(void* sortFunction, float* arr, size_t n,
                                 size_t numIter);

#endif //SORTING_ALGORITHMS_TEST_H
