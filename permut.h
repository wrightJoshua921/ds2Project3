/* 
 * File:   permut.h
 * Author: wrigh
 *
 * Created on October 8, 2015, 10:24 AM
 */

#ifndef PERMUT_H
#define	PERMUT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

#define MAX_CITY 20

typedef struct permut {
    int order[MAX_CITY];
    double weight;
    int length;
    GraphT *graph;
}PermuteT;

PermuteT *createPermut(int length, GraphT *graph);

void getNextPermut(PermuteT *permut, int array[], int n);

PermuteT *createNextPermut(PermuteT *permut);

PermuteT *copyPermut(PermuteT *permut);

void replacePermut(PermuteT **going, PermuteT *from);

void randomizePermut(PermuteT *permut);

void calcPermutCost(PermuteT *permut);

void quicksortPermuts(PermuteT *permut[], int left, int right);

int partition(PermuteT *permut[], int left, int right);

void swapPermuts(PermuteT **permut1, PermuteT **permut2);

void mutate(PermuteT *permut, int numPairs);

void freePermuts(PermuteT *permut);

void printPermuts(PermuteT *permut);

void swap(int *a, int *b);

#endif	/* PERMUT_H */

