//
// Created by Paige Riley Weber on 6/4/21.
//

#include <stdio.h>
#include "utils.h"

int compare(float a, float b) {
  return a < b ? TRUE : FALSE;
}

int isArraySorted(float* arr, size_t n) {
  for (size_t i = 0; i < n-1; i++) {
    if (!compare(arr[i], arr[i+1])) return FALSE;
  }
  return TRUE;
}

float* generateRandomArray(size_t n) {
  float* arr = (float*) aligned_alloc(ALIGNMENT, sizeof(float) * n);
  srand(time(NULL));

  for (size_t i = 0; i < n; i++) {
    arr[i] = fastRand;
  }

  return arr;
}

float* generateSortedArray(size_t n) {

}

float* generateReverseSortedArray(size_t n);

float* printArray(float* arr, size_t n){
  printf("[");
  for (size_t i = 0; i < n-1; i++) {
    printf("%f, ", arr[i]);
  }
  printf("%f", arr[n-1]);
  printf("]\n");
}
