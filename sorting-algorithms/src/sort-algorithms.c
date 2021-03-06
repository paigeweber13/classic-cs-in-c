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
  // base case: an array of size 1 is always sorted
  if(n == 1)
    return;
  
  // create new pointers and sizes for the left and right halves. This is how
  // we "split" the array
  size_t left_n = n/2;
  float * left_array = array;
  float * left_buffer = buffer;

  size_t right_n = n - n/2;
  float * right_array = array + left_n;
  float * right_buffer = buffer + left_n;

  // mergesort each half
  mergesort(left_array, left_buffer, left_n);
  mergesort(right_array, right_buffer, right_n);

  // merge the sorted portions back together
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
    // for small n, use sequential code. Avoid creating very small tasks.
    mergesort(array, buffer, n/2);
    mergesort(array + n/2, buffer + n/2, n - n/2);
  }
  else {
    #pragma omp task
    mergesort_parallel(array, buffer, n/2);

    #pragma omp task
    mergesort_parallel(array + n/2, buffer + n/2, n - n/2);
  }

  // taskwait ensures that both mergesorts are completed before merging
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

  // we want to move from right to left, because big numbers will be towards
  // the right

  // start at i = n/2 because anything at indices greater than n/2 will be a
  // leaf node
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

// recursive part of quicksort
void quicksort(float* arr, size_t i, size_t n) {
  if ((n - i) < 2) return;

  // pivot is first item
  size_t pivot_i = i;

  for (size_t j = i+1; j < n; j++) {
    // check if other is less than pivot. If so, move pivot to the right and
    // place other immediately before pivot.
    if (arr[j] < arr[pivot_i]) {
      swap(&arr[pivot_i], &arr[pivot_i+1]);
      pivot_i++;

      // this case is important! This covers the instance where j immediately
      // follows the pivot, and so moving the pivot also swapped other before
      // the pivot.
      if(j != pivot_i) {
        swap(&arr[j], &arr[pivot_i-1]);
      }
    }
  }

  // recursively quicksort left and right halves
  quicksort(arr, i, pivot_i);
  quicksort(arr, pivot_i+1, n);
}

// wrapper to match function signature
void quickSort(float* arr, size_t n) {
  quicksort(arr, 0, n);
}

// recursive part of modified quicksort
void quicksort_modified(float* arr, size_t i, size_t n) {
  // insertion sort on small parts
  if (n - i < 16) {
    insertionSort(arr + i, n-i);
    return;
  }

  // the three indices for median-of-three
  size_t hi = n-1;
  size_t lo = i;
  size_t mid = lo + ((hi - lo) / 2);

  // these three if statements ensure elements at lo, mid, and hi are sorted in
  // relation to each other. This way we know that mid is our median-of-three.
  if (arr[mid] < arr[lo]) swap(&arr[mid], &arr[lo]);
  if (arr[hi] < arr[lo]) swap(&arr[hi], &arr[lo]);
  if (arr[mid] > arr[hi]) swap(&arr[mid], &arr[hi]);

  lo++;
  hi--;

  // check left side of pivot for anything that is larger than pivot
  while (lo < mid) {
    if (arr[lo] > arr[mid]) {
      swap(&arr[mid], &arr[mid-1]);
      mid--;

      if (lo != mid) swap(&arr[lo], &arr[mid+1]);
    }
    else lo++;
  }

  // check right side of pivot for anything smaller than pivot
  while (hi > mid) {
    if (arr[hi] < arr[mid]) {
      swap(&arr[mid], &arr[mid+1]);
      mid++;

      if (hi != mid) swap(&arr[hi], &arr[mid-1]);
    }
    else hi--;
  }

  // recursively quicksort left and right halves
  quicksort_modified(arr, i, mid);
  quicksort_modified(arr, mid+1, n);
}

// wrapper to match function signature
void quickSortModified(float* arr, size_t n) {
  quicksort_modified(arr, 0, n);
}
