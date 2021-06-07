//
// Created by Paige Riley Weber on 6/4/21.
//

#include <stdio.h>
#include "utils.h"

void swap(float* a, float* b) {
  temp = *a;
  *a = *b;
  *b = temp;
}

int isArraySorted(float* arr, size_t n) {
  for (size_t i = 0; i < n-1; i++) {
    if (arr[i] > arr[i+1]) return FALSE;
  }
  return TRUE;
}

void generateRandomArray(float* arr, size_t n) {
  // optional: seed fastRand to current time
//  z = time(NULL);

  for (size_t i = 0; i < n; i++) {
    arr[i] = fastRand;
  }
}

void generateSortedArray(float* arr, size_t n) {
  for (size_t i = 0; i < n; i++) {
    arr[i] = i;
  }
}

void generateReverseSortedArray(float* arr, size_t n) {
  for (size_t i = 0; i < n; i++) {
    arr[i] = n-i;
  }
}

float* printArray(float* arr, size_t n){
  printf("[");
  for (size_t i = 0; i < n-1; i++) {
    printf("%f, ", arr[i]);
  }
  printf("%f", arr[n-1]);
  printf("]\n");
}
