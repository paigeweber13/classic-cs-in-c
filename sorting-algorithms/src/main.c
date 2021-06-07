//
// Created by Paige Riley Weber on 6/4/21.
//

#include "sort-algorithms.h"
#include "test.h"
#include "utils.h"

#define TEST_SIZE 10

int main() {
  #define SUPPORTEDALGOS_N 1
  const SortAlgorithm supportedAlgos[SUPPORTEDALGOS_N] = 
    {sortQuickModified};
  // const size_t maxSize = 11;
  // const size_t initSize = 10;

  // #define SUPPORTEDALGOS_N 5
  // const SortAlgorithm supportedAlgos[SUPPORTEDALGOS_N] = 
  //   {sortInsertion, sortMerge, sortMergeParallel, sortHeap, sortQuick};

  #define ARRAYSFORTEST_N 3
  const ArrayType arraysForTest[ARRAYSFORTEST_N] = 
    {initRandom, initSorted, initReverse};

  const size_t maxSize = 1000000;
  // const size_t maxSize = 10000000; // for longer tests
  const size_t maxSizeInsertion = 16001;
  // const size_t maxSizeInsertion = 64001; // for longer tests
  const size_t initSize = 1000;

  printResultHeader();

  for (size_t i = 0; i < SUPPORTEDALGOS_N; i++)
    for (size_t j = 0; j < ARRAYSFORTEST_N; j++)
      if(supportedAlgos[i] == sortInsertion) 
        testSortMulti(supportedAlgos[i], arraysForTest[j], initSize, 
          maxSizeInsertion);
      else
        testSortMulti(supportedAlgos[i], arraysForTest[j], initSize, maxSize);

  return 0;
}
