//
// Created by Paige Riley Weber on 6/5/21.
//

#ifndef SORTING_ALGORITHMS_TEST_H
#define SORTING_ALGORITHMS_TEST_H

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "utils.h"

typedef struct RunTimeAggregate {
  double runTimeTotal;
  double runTimeMin;
  double runTimeMax;
  double runTimeAvg;
} RunTimeAggregate;

void printResultHeader();

void testSortMulti(SortAlgorithm sortAlgorithm, ArrayType
                   arrayType, size_t sizeInit, size_t sizeFinal);

// returns average runtime
RunTimeAggregate testSortSingle(void (*sortFunction)(float*, size_t),
                      void (*generatorFunction)(float*, size_t),
                      float*arr, size_t n, size_t numIter);

#endif //SORTING_ALGORITHMS_TEST_H
