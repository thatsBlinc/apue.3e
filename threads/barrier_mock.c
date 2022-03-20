// C implementation of Heap Sort
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
// A heap has current size and array of elements

pthread_barrier_t b;
#define NTHR   1
#define NUMNUM 8000000L
#define TNUM   NUMNUM/NTHR
long arr[NUMNUM];
long snums[NUMNUM];

struct MaxHeap
{
    long size;
    long* array;
};

// A utility function to swap to integers
void swap(long* a, long* b) { long t = *a; *a = *b;  *b = t; }

// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, long idx)
{
    long largest = idx;  // Initialize largest as root
    long left = (idx << 1) + 1;  // left = 2*idx + 1
    long right = (idx + 1) << 1; // right = 2*idx + 2

    // See if left child of root exists and is greater than
    // root
    if (left < maxHeap->size &&
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;

    // See if right child of root exists and is greater than
    // the largest so far
    if (right < maxHeap->size &&
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;

    // Change root, if needed
    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}

// A utility function to create a max heap of given capacity
struct MaxHeap* createAndBuildHeap(long *array, long size)
{
    long i;
    struct MaxHeap* maxHeap =
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// The main function to sort an array of given size
void heapSort(long* array, long size)
{
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);
    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}

// A utility function to print a given array of given size
void printArray(long* arr, long size)
{
    long i;
    for (i = 0; i < size-1; ++i)
        printf("%ld- ", arr[i]);
    printf("%ld\n",arr[size-1]);
}

/* Driver program to test above functions */



/*
 * Worker thread to sort a portion of the set of numbers.
 */
void *
thr_fn(void *arg)
{
    long    idx = (long)arg;
    heapSort(&arr[idx], TNUM);
    pthread_barrier_wait(&b);

    /*
     * Go off and perform more work ...
     */
    return((void *)0);
}

/*
 * Merge the results of the individual sorted ranges.
 */
void
merge()
{

    long    idx[NTHR];
    long    i, minidx, sidx, num;

    for (i = 0; i < NTHR; i++)
        idx[i] = i * TNUM;
    for (sidx = 0; sidx < NUMNUM; sidx++) {
        num = LONG_MAX;
        for (i = 0; i < NTHR; i++) {
            if ((idx[i] < (i+1)*TNUM) && (arr[idx[i]] < num)) {
                num = arr[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = arr[idx[minidx]];
        idx[minidx]++;
    }

}

void printSummary(double elapsed){
    printf("[number of elements]: %ld\n",NUMNUM);
    printf("[number of threads]: %d\n",NTHR);
    printf("sort took %.4f seconds\n", elapsed);
}

int main(int argc, char *argv[])
{

    unsigned long   i;
    struct timeval  start, end;
    long long       startusec, endusec;
    double          elapsed;
    pthread_t       tid;
    int             err;
    
    srandom(1);
    for (long i = 0; i < NUMNUM; i++)
        arr[i] = random();

    long size = sizeof(arr)/sizeof(arr[0]);
    gettimeofday(&start, NULL);

    pthread_barrier_init(&b, NULL, NTHR+1); //why +1? main thread is also considered 
    for (int i = 0; i < NTHR; i++) {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0)
            err_exit(err, "can't create thread");
    }
    //heapSort(arr, size);
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);
    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    
    printf("\nSorted array is \n");
    printArray(snums, 100);
    printf("\n");
    
    printSummary(elapsed);

    return 0;
}

