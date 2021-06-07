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

// assumes a and b are contiguous in memory, with 'a' first
void merge(float * a, size_t a_n, float * b, size_t b_n, float * buffer) {
  size_t a_i = 0; // index of array a
  size_t b_i = 0; // index of array b

  size_t buffer_i = 0;

  while(a_i < a_n && b_i < b_n) {
    if(a[a_i] > b[b_i]) {
      // then b should come first
      buffer[buffer_i] = b[b_i];
      b_i++;
    }
    else {
      // else a is <= b so we put a next
      buffer[buffer_i] = a[a_i];
      a_i++;
    }

    buffer_i++;
  }

  // if either 'a' or 'b' has items left, copy them to 'merged'
  if(a_i < a_n) {
    memcpy(buffer + buffer_i, a + a_i, sizeof(float) * (a_n - a_i));
  }
  if(b_i < b_n) {
    memcpy(buffer + buffer_i, b + b_i, sizeof(float) * (b_n - b_i));
  }

  // then move stuff from 'buffer' back into original array
  memcpy(a, buffer, sizeof(float) * (a_n+b_n));
}

// recursively merge-sorts an array in-place.
void mergesort(float * array, float * buffer, size_t n) {
  if(n == 1)
    return;
  
  size_t left_n = n/2;
  float * left_array = array;
  float * left_buffer = buffer;

  size_t right_n = n - n/2;
  float * right_array = array + left_n;
  float * right_buffer = buffer + left_n;

  mergesort(left_array, left_buffer, left_n);
  mergesort(right_array, right_buffer, right_n);

  merge(left_array, left_n, right_array, right_n, buffer);
}

// helper function to match signature of other functions
void mergeSort(float* arr, size_t n) {
  float * buffer = aligned_alloc(ALIGNMENT, sizeof(float) * n);

  mergesort(arr, buffer, n);

  free(buffer);
}

void mergesort_parallel(float * array, float * buffer, size_t n) {
  // there is no free lunch: this parameter will need tuning per-machine
  const size_t MIN_PARALLEL_N = (size_t)1e6;

  if (n < MIN_PARALLEL_N) {
    // for small n, use sequential code. Avoid creating thousands of tasks.
    mergesort(array, buffer, n/2);
    mergesort(array + n/2, buffer + n/2, n - n/2);
  }
  else {
    #pragma omp task
    mergesort_parallel(array, buffer, n/2);

    #pragma omp task
    mergesort_parallel(array + n/2, buffer + n/2, n - n/2);
  }

  #pragma omp taskwait
  merge(array, n/2, array + n/2, n - n/2, buffer);
}

void mergeSortParallel(float* arr, size_t n) {
  float * buffer = aligned_alloc(ALIGNMENT, sizeof(float) * n);

  mergesort_parallel(arr, buffer, n);

  free(buffer);
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
