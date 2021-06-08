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
   - [ ] compare average case of each
   - [ ] compare cases where special cases were significantly different from random case
 - [ ] code
"""

# ╔═╡ aa573021-c79a-46c1-b4e0-021e4c3434ed
md"""
# Data Structures


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
Because mergesort is significantly more complicated to implement and the full source code is available in this repository, I will only cover key parts of the code here.

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

"""

# ╔═╡ 72ad1767-88e1-457c-8a76-33f119c7cc15
md"""
# Complexity Analysis


"""

# ╔═╡ 3a653422-4f34-42fe-a974-ff1a57d85a9b
md"""
# Results: Performance


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
# ╠═209e2ecb-af90-4c48-a583-e9dda280198f
# ╠═72ad1767-88e1-457c-8a76-33f119c7cc15
# ╠═3a653422-4f34-42fe-a974-ff1a57d85a9b
# ╠═d6a054e2-c7bf-11eb-3732-c3135a35f956
# ╠═3b969425-8ee1-4bfd-af35-27238bf7ae7b
