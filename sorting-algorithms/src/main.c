//
// Created by Paige Riley Weber on 6/4/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "insertion-sort.h"

#define TEST_SIZE 10

int main() {
  float* arr = generateRandomArray(TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is random array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);
  printf("\n");

  arr = generateSortedArray(TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is sorted array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);
  printf("\n");

  arr = generateReverseSortedArray(TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is reverse array sorted? %d\n", isArraySorted(arr, TEST_SIZE));
  insertionSort(arr, TEST_SIZE);
  printArray(arr, TEST_SIZE);
  printf("Is array sorted after sort? %d\n", isArraySorted(arr, TEST_SIZE));
  free(arr);

  return 0;
}
