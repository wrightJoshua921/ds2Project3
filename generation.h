/* 
 * File:   generation.h
 * Author: wrigh
 *
 * Created on October 15, 2015, 12:29 PM
 */

#ifndef GENERATION_H
#define	GENERATION_H
#include <stdlib.h>
#include "permut.h"
#include "graph.h"

#define pairs 2

typedef struct generation{
    PermuteT **permut;
    PermuteT *lastPermut;
    int length;
    int numMutations;
    int numElites;
}GenerationT;

GenerationT *createGeneration(int toursPerGeneration, double percMutations,
        double percElites, int permutLength, GraphT *graph);

void nextGeneration(GenerationT *generation);

void sortGeneration(GenerationT *generation);

void freeGeneration(GenerationT *generation);

#endif	/* GENERATION_H */

