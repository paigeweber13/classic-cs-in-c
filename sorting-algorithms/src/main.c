//
// Created by Paige Riley Weber on 6/4/21.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort-algorithms.h"
#include "test.h"
#include "utils.h"

#define TEST_SIZE 10

int main() {
//  float* arr = (float*) aligned_alloc(ALIGNMENT, sizeof(float) * n);
  float* arr = aligned_alloc(ALIGNMENT, sizeof(float) * TEST_SIZE);

  generateRandomArray(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is random array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);
  printf("\n");

  generateSortedArray(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is sorted array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);
  printf("\n");

  generateReverseSortedArray(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is reverse array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);


  printResultHeader();
//  const size_t maxSize = 128001;
  const size_t maxSize = 64001;
  const size_t initSize = 1000;
  testSortMulti(sortHeap, initRandom, initSize, maxSize);
  testSortMulti(sortInsertion, initRandom, initSize, maxSize);

  return 0;
}
