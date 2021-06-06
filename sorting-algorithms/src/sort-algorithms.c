//
// Created by Paige Riley Weber on 6/4/21.
//

#include "sort-algorithms.h"

void insertionSort(float* arr, size_t n) {
  for (size_t i = 1; i < n; i++) {
    size_t j = i;
    while (j > 0 && arr[j] < arr[j-1]) {
      swap(&arr[j], &arr[j-1]);
      j--;
    }
  }
}

// turn array[root:n] into max heap
void heapify(float* arr, size_t n, size_t root) {
  int largest = root;
  int left = 2*root + 1;
  int right = 2*root + 2;

  // compare root to its children to see which is largest
  if (left < n && arr[left] > arr[largest]) largest = left;
  if (right < n && arr[right] > arr[largest]) largest = right;

  if (largest != root) {
    // then we are not done. Swap and heapify again
    swap(&arr[root], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(float* arr, size_t n) {
  // heapify all subtrees (create initial max heap)
  size_t currentRoot;

  // we want to move from right to left
  for (size_t i = n/2 - 1; i > 0; i--) {
    heapify(arr, n, i);
  }

  // last iteration (since size_t is unsigned we can't rely on it being
  // negative as a condition to end the for loop)
  heapify(arr, n, 0);

  // move largest element to end
  for (size_t i = n-1; i > 0; i--) {
    swap(&arr[0], &arr[i]);

    // heapify with 0 as root. Only heapify to i
    heapify(arr, i, 0);
  }
}
