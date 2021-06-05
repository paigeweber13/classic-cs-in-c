//
// Created by Paige Riley Weber on 6/5/21.
//

#include <stdio.h>
#include "insertion-sort.h"

#include "test.h"

const char RESULT_HEADER[200] = " status,sorting_algorithm,array_type,"
                                "array_size,num_iterations,run_time_s,"
                                "elements_per_second\n";
const char FORMAT_STRING[200] = "%7s,%17s,%10s,%10u,"
                                "%14u,%10f,"
                                "%19f\n";

void printResultHeader() {
  printf(RESULT_HEADER);
}

void testSortMulti(SortAlgorithm sortAlgorithm, ArrayType
                   arrayType, size_t sizeInit, size_t sizeFinal) {
  // used across runs
  float* arr = aligned_alloc(ALIGNMENT, sizeof(float) * sizeFinal);
  double runTime;
  char arrayTypeString[20];
  char sortAlgorithmString[20];
  char successString[8];

  // initialize all iterators
  size_t n = sizeInit;
  size_t numIter = sizeFinal;
  size_t resultsI = 0;

  while (n < sizeFinal) {
    switch (arrayType) {
      case initRandom:
        generateRandomArray(arr, n);
        strcpy(arrayTypeString, "random");
      case initSorted:
        generateSortedArray(arr, n);
        strcpy(arrayTypeString, "sorted");
      case initReverse:
        generateReverseSortedArray(arr, n);
        strcpy(arrayTypeString, "reversed");
    }

    switch (sortAlgorithm) {
      case sortInsertion:
        runTime = testSortSingle((void*) insertionSort, arr, n, numIter);
        strcpy(sortAlgorithmString, "insertion");
    }

    if (isArraySorted(arr, n)) strcpy(successString, "SUCCESS");
    else strcpy(successString, "FAILURE");

    printf(FORMAT_STRING, successString, sortAlgorithmString, arrayTypeString,
           n, numIter, runTime, runTime/ ((double)n) );
//    resultsArray[resultsI].arraySize = n;
//    resultsArray[resultsI].numRuns = numIter;
//    resultsArray[resultsI].arrayType = arrayType;
//    resultsArray[resultsI].sortAlgorithm = sortAlgorithm;

    // update all variables
    n *= 2;
    numIter /= 2;
    resultsI ++;
  }

  free(arr);
}

double testSortSingle(void* sortFunction, float* arr, size_t n,
    size_t numIter) {
  TestResult result;
  const SECONDS_TO_MICROSECONDS = 1000000;

  // thanks to https://www.techiedelight.com/find-execution-time-c-program
  // for helping me time code
  struct timeval start, end;

  gettimeofday(&start, NULL);
  insertionSort(arr, n);
  gettimeofday(&end, NULL);

  double seconds = (double)(end.tv_sec - start.tv_sec);
  double micros = (double)(end.tv_usec - start.tv_usec);

  double runTime = seconds + (micros / SECONDS_TO_MICROSECONDS);

  return runTime;
}
