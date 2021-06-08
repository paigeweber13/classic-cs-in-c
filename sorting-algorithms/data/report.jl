### A Pluto.jl notebook ###
# v0.14.7

using Markdown
using InteractiveUtils

# ╔═╡ d6a054e2-c7bf-11eb-3732-c3135a35f956
# load libraries

begin
	using CSV
	using DataFrames
	using Plots
end

# ╔═╡ b2ca8e4b-fe95-43cb-a5bc-605f69d0d581
md"""
# Sorting Algorithms
*By Paige Weber*

This project covers the implementation, computational complexity, and real-world performance of several common sorting algorithms. The algorithms implemented and tested are insertion sort (the control), merge sort, heapsort, and quicksort. Mergesort is implemented both sequentially and in parallel. Quicksort is implemented naïvely (to demonstrate the worst-case performance on an already-sorted list) and then implemented with a median-of-three pivot.

C was chosen as the language each algorithm was written in.

TODO: 
 - [ ] data structures used
 - [ ] complexity analysis
 - [ ] results
 - [ ] code
"""

# ╔═╡ aa573021-c79a-46c1-b4e0-021e4c3434ed
md"""
# Data Structures

Lists were represented as simple arrays, contiguous in memory, allocated with `aligned_alloc`. 

The heap for heapsort is represented using a 1-dimensional array (in fact, the same array the initial list is stored in).

Accessing a known index has complexity `O(1)`. This is the only operation used. 

"""

# ╔═╡ e72161bc-dab5-4585-9cf8-bc32ec84e988
md"""
# Sample Code

All sorting code may be found in the file `src/sorting-algorithms.c`.
"""


# ╔═╡ 3723574c-959a-4b04-91bf-6207c4ff6fd5
md"""
## Insertion Sort
Insertion sort is quite simple, and only took ~5 lines of actual code:

```c
void insertionSort(float* arr, size_t n) {
  for (size_t i = 1; i < n; i++) {
    size_t j = i;
    while (j > 0 && arr[j] < arr[j-1]) {
      swap(&arr[j], &arr[j-1]);
      j--;
    }
  }
}
```

"""


# ╔═╡ 209e2ecb-af90-4c48-a583-e9dda280198f
md"""
## Merge Sort

Because every other algorithm is significantly more complicated to implement and the full source code is available in this repository, I will omit whatever possible without making the code snippets less clear. Removed code will be indicated by commenting `// (removed) ...`.

My implementation does not create new arrays for each split and then rejoin them on merge. Instead, it uses indices to track which part of the array should be considered for the current instance of `mergesort`. Because this approach may require many swaps, a separate "buffer" array is used to store the sorted part of the array, which is then copied back into the main array.

The actual mergesort function behaves as follows. "Splitting" the array in two just means assigning a new pointer to the beginning of the array (and buffer) and setting the size to the correct value.

```c
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
```

The merge is somewhat more complicated, requiring careful tracking of indices for both halves as well as the buffer.

```c
void merge(float * a, size_t a_n, float * b, size_t b_n, float * buffer) {
  size_t a_i = 0; size_t b_i = 0; buffer_i = 0;

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

  // (removed) if either 'a' or 'b' has items left, copy them to 'merged'
  // (removed) then move stuff from 'buffer' back into original array
}
```

As an extra exercise, I also parallelized mergesort, because one of the main advantages of this algorithm is the ease with which it can be parallelized. Performance improvements over sequential code will be considered later in the report.

```c

void mergesort_parallel(float * array, float * buffer, size_t n) {
  // (removed) small tasks are done sequentially
  
  #pragma omp task
  mergesort_parallel(array, buffer, n/2);

  #pragma omp task
  mergesort_parallel(array + n/2, buffer + n/2, n - n/2);

  // taskwait ensures that both mergesorts are completed before merging
  #pragma omp taskwait
  merge(array, n/2, array + n/2, n - n/2, buffer);
}
```

"""

# ╔═╡ fd11a60a-c3dd-4bb1-aeb3-e3be1b87f4f7
md"""
## Heapsort

The heap is created in-place. No additional memory is used. Because a heap is a complete binary tree, we can use a 1 dimensional array and know that for any node at index `i`, `i * 2 + 1` and `i * 2 + 2` are the left and right children of that node. In our case, the heap used is a max heap.

Heapsort only requires heapifying the array, then repeatedly swapping the largest element to the end and re-heapifying the root.

```c
void heapSort(float* arr, size_t n) {
  // heapify all subtrees (create initial max heap)

  // we want to move from right to left, because big numbers will be towards
  // the right

  // start at i = n/2 because anything at indices greater than n/2 will be a
  // leaf node
  for (int i = n/2 - 1; i > -1; i--) {
    heapify(arr, n, i);
  }

  // move largest element to end
  for (size_t i = n-1; i > 0; i--) {
    swap(&arr[0], &arr[i]);

    // heapify with 0 as root. Only heapify to i
    heapify(arr, i, 0);
  }
}
```

Heapify is also fairly simple. First, we check if either of a node's children are greater than itself. If so, we swap root with the larger child and repeat. The process terminates when the root is larger than both its children.

```c
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
```

"""

# ╔═╡ 1ca8d8c9-fdd1-4172-aa75-9206c48e0212
md"""
## Quicksort

This naïve implementation is very simple. First, we check if the size of the array is less than 2 (in which case we know it is already sorted). This is our base case. Then, we set the pivot to be the first element of the array and compare it with every other element in the array. If the other element is smaller than the pivot, the pivot is moved and that element is placed immediately before the pivot.

```c
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
```

This has very poor performance when the list is already sorted or reverse-sorted (both common cases). To overcome this, we also implemented a version of quicksort with the median-of-three strategy for choosing the pivot. This version also uses insertion sort for `n <= 15`, which acts as our base-case.

As we will show later, these changes have significant performance implications.

```c
// recursive part of modified quicksort
void quicksort_modified(float* arr, size_t i, size_t n) {
  // insertion sort on small parts
  if (n < 16) {
    insertionSort(arr, n);
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
```

"""

# ╔═╡ 72ad1767-88e1-457c-8a76-33f119c7cc15
md"""
# Complexity Analysis


"""

# ╔═╡ 3a653422-4f34-42fe-a974-ff1a57d85a9b
md"""
# Results: Performance

# TODO: performance
- [ ] graph of mergesort: sequential vs parallel
- [ ] graph of rabdom/average case for each
- [ ] graph of cases when special cases are significantly different from random case
"""

# ╔═╡ 3b969425-8ee1-4bfd-af35-27238bf7ae7b
# load csv data
begin
	CSV_FILE_NAME = "results-2021-06-07_0842.csv"
	
	df = CSV.File(CSV_FILE_NAME, normalizenames=true) |> DataFrame
	df.status
end

# ╔═╡ Cell order:
# ╠═b2ca8e4b-fe95-43cb-a5bc-605f69d0d581
# ╠═aa573021-c79a-46c1-b4e0-021e4c3434ed
# ╟─e72161bc-dab5-4585-9cf8-bc32ec84e988
# ╟─3723574c-959a-4b04-91bf-6207c4ff6fd5
# ╟─209e2ecb-af90-4c48-a583-e9dda280198f
# ╟─fd11a60a-c3dd-4bb1-aeb3-e3be1b87f4f7
# ╟─1ca8d8c9-fdd1-4172-aa75-9206c48e0212
# ╠═72ad1767-88e1-457c-8a76-33f119c7cc15
# ╠═3a653422-4f34-42fe-a974-ff1a57d85a9b
# ╠═d6a054e2-c7bf-11eb-3732-c3135a35f956
# ╠═3b969425-8ee1-4bfd-af35-27238bf7ae7b
