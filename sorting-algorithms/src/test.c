//
// Created by Paige Riley Weber on 6/5/21.
//

#include "sort-algorithms.h"

#include "test.h"

const char RESULT_HEADER[200] = " status,sorting_algorithm,array_type,"
                                "array_size,num_iterations,total_time_s,"
                                "min_time_s,max_time_s,avg_time_s,"
                                "avg_elements_per_second\n";
const char FORMAT_STRING[200] = "%7s,%17s,%10s,"
                                "%10lu,%14lu,%12f,"
                                "%10f,%10f,%10f,"
                                "%23f\n";

void printResultHeader() {
  printf(RESULT_HEADER);
}

void testSortMulti(SortAlgorithm sortAlgorithm, ArrayType
                   arrayType, size_t sizeInit, size_t sizeFinal) {
  // used across runs
  float* arr = aligned_alloc(ALIGNMENT, sizeof(float) * sizeFinal);
  RunTimeAggregate runTime;
  char arrayTypeString[20];
  char sortAlgorithmString[20];
  char successString[8];

  void (*sortFunction)(float*, size_t);
  void (*generatorFunction)(float*, size_t);

  // initialize all iterators
  size_t n = sizeInit;
  size_t numIter = 10;
//  if (sizeFinal > 1000) numIter = sizeFinal / 100;
//  else numIter = 10;

  while (n < sizeFinal) {
    switch (arrayType) {
      case initRandom:
        generatorFunction = generateRandomArray;
        strcpy(arrayTypeString, "random");
        break;
      case initSorted:
        generatorFunction = generateSortedArray;
        strcpy(arrayTypeString, "sorted");
        break;
      case initReverse:
        generatorFunction = generateReverseSortedArray;
        strcpy(arrayTypeString, "reversed");
        break;
    }

    switch (sortAlgorithm) {
      case sortInsertion:
        sortFunction = insertionSort;
        strcpy(sortAlgorithmString, "insertion");
        break;
      case sortHeap:
        sortFunction = heapSort;
        strcpy(sortAlgorithmString, "heap");
        break;
      case sortMerge:
        sortFunction = mergeSort;
        strcpy(sortAlgorithmString, "merge");
        break;
      case sortMergeParallel:
        sortFunction = mergeSortParallel;
        strcpy(sortAlgorithmString, "merge_parallel");
        break;
      case sortQuick:
        sortFunction = quickSort;
        strcpy(sortAlgorithmString, "quick");
        break;
      case sortQuickModified:
        sortFunction = quickSortModified;
        strcpy(sortAlgorithmString, "quick_modified");
        break;
    }

    runTime = testSortSingle(sortFunction, generatorFunction, arr, n,
                             numIter);

    if (isArraySorted(arr, n)) strcpy(successString, "SUCCESS");
    else strcpy(successString, "FAILURE");

    printf(FORMAT_STRING, successString, sortAlgorithmString, arrayTypeString,
           n, numIter, runTime.runTimeTotal, runTime.runTimeMin,
           runTime.runTimeMax, runTime.runTimeAvg,
           ((double)n) / runTime.runTimeAvg );

    // update all variables
    n *= 2;
    if (numIter > 10)
      numIter /= 2;
  }

  free(arr);
}

RunTimeAggregate testSortSingle(void (*sortFunction)(float*, size_t),
                      void (*generatorFunction)(float*, size_t),
                      float*arr, size_t n, size_t numIter) {
  const size_t SECONDS_TO_MICROSECONDS = 1000000;

  double seconds, micros, runTime;

  RunTimeAggregate result = {.runTimeMin = INFINITY};

  // thanks to https://www.techiedelight.com/find-execution-time-c-program
  // for helping me time code
  struct timeval start, end;

  for (size_t i = 0; i < numIter; i++) {
    generatorFunction(arr, n);

    gettimeofday(&start, NULL);
    sortFunction(arr, n);
    gettimeofday(&end, NULL);

    seconds = (double)(end.tv_sec - start.tv_sec);
    micros = (double)(end.tv_usec - start.tv_usec);

    runTime = seconds + (micros / SECONDS_TO_MICROSECONDS);
    result.runTimeTotal += runTime;
    if (runTime < result.runTimeMin) result.runTimeMin = runTime;
    if (runTime > result.runTimeMax) result.runTimeMax = runTime;
  }

  result.runTimeAvg = result.runTimeTotal / ((double) numIter);

  return result;
}
