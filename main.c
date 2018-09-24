//
//  main.c
//  MergeSort
//
//  Created by fast-algo on 9/18/18.
//  Copyright © 2018 fast-algo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "funcTimer.h"

void testMergeSort(void);

// Merge Sort using loops for copying
void mergeSort(int *theData, int theLen);
void combine(int *leftData, int leftLen, int *rightData, int rightLen);

// Compare function needed for stdlib mergesort
static int int_compare(const void *p1, const void *p2);

int *sorted = NULL;

#define NUM_RAND_INT 11000000 // 11 million integers to sort
#define NUM_TIMING_LOOPS 10

int main(int argc, const char * argv[])
{
    srand((int)time(NULL));
    
    // Need 2 copies of the same data to compare the different sort implementations
    int *data1 = malloc(NUM_RAND_INT * sizeof(int));
    int *data2 = malloc(NUM_RAND_INT * sizeof(int));
    memset(data1, 0, NUM_RAND_INT);
    memset(data2, 0, NUM_RAND_INT);

    // Pre-allocate this block here to avoid doing it 11 million times later!
    sorted = malloc(NUM_RAND_INT * sizeof(int));
    memset(sorted, 0, NUM_RAND_INT * sizeof(int));

    double totStdTime = 0;
    double totTime = 0;
    
    for (int timingLoop = 0; timingLoop < NUM_TIMING_LOOPS; timingLoop++)
    {
        for (int i = 0; i < NUM_RAND_INT; i++)
        {
            int randInt = (int)(rand() % (10 * NUM_RAND_INT)); // 10x to reduce the number of duplicates
            // Want identical copies of the random list for fair comparison
            data1[i] = randInt;
            data2[i] = randInt;
        }
        
        // Merge Sort with loops
        startFuncTimer(0);
        mergeSort(data1, NUM_RAND_INT);
        stopFuncTimer(0);
        totTime += getFuncTime(0);

        // Stdlib mergesort
        startFuncTimer(1);
        mergesort(data2, NUM_RAND_INT, sizeof(int), int_compare);
        stopFuncTimer(1);
        totStdTime += getFuncTime(1);
    }

    for (int i = 0; i < NUM_RAND_INT; i++)
    {
        if (data1[i] != data2[i])
        {
            // One of the implementations is potentially wrong
            printf("RESULTS ARE DIFFERENT\n");
            return -1;
        }
    }
    
    printf("MergeSort of %d integers with stdlib took %lf seconds.\n", NUM_RAND_INT, totStdTime / NUM_TIMING_LOOPS);
    printf("MergeSort of %d integers took %lf seconds.\n", NUM_RAND_INT, totTime / NUM_TIMING_LOOPS);
    
    if (sorted)
        free(sorted);
    
    if (data1)
        free(data1);
    
    if (data2)
        free(data2);
    
    return 0;
}

void testMergeSort()
{
    int dataLen = 6;
    int testData[] = {3,1,6,4,8,5};
    
    mergeSort(testData, dataLen);
    
    printf("Sorted Data...\n");
    for (int i = 0; i < dataLen; i++)
        printf("%d ", testData[i]);
    
    printf("\n\n");
}

void mergeSort(int *theData, int theLen)
{
    if (theLen == 1)
        return;
    
    int *leftData = theData;
    int leftLen = theLen / 2;
    int *rightData = leftData + leftLen;
    int rightLen = theLen - leftLen;
    
    mergeSort(leftData, leftLen);
    mergeSort(rightData, rightLen);
    combine(leftData, leftLen, rightData, rightLen);
}

void combine(int *leftData, int leftLen, int *rightData, int rightLen)
{
    int i = 0, j = 0, k = 0;
    int totLen = leftLen + rightLen;

    while ( (i < leftLen) && (j < rightLen) )
    {
        if (leftData[i] <= rightData[j])
            sorted[k++] = leftData[i++];
        else if (rightData[j] <= leftData[i])
            sorted[k++] = rightData[j++];
    }
    
    // Copy any remaining ints from leftData
    while (i < leftLen)
        sorted[k++] = leftData[i++];
    
    // Copy any remaining ints from rightData
    while (j < rightLen)
        sorted[k++] = rightData[j++];
    
    // Copy everything back into leftData
    for (k = 0; k < totLen; k++)
        leftData[k] = sorted[k];
}

static int int_compare(const void *p1, const void *p2)
{
    int left =  *(const int *)p1;
    int right = *(const int *)p2;
    return ((left > right) - (left < right));
}
