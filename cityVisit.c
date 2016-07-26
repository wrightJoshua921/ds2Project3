/* 
 * File:   cityVisit.c
 * Author: wrigh
 *
 * Created on October 8, 2015, 10:23 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "permut.h"
#include "generation.h"
#define CITIES 20
#define BILLION 1000000000L;

typedef struct stuff{
    int tours;
    int generations;
    int cities;
    double mutations;
    double elites;
}stuffT;


void printResults(PermuteT *badPerm, PermuteT *bestBrutePerm, PermuteT *bestGeneticPerm, double geneticTime, double bruteTime);
void args(int argc, char *argv[], GraphT **graph, stuffT *things);
long factorial(int base);
/*
 * 
 */
int main(int argc, char **argv) 
{
    GraphT *places;
    stuffT things;
    PermuteT *currentPerm, *bestBrutePerm, *bestGeneticPerm, *badPerm;
    GenerationT *currentGeneration;
    struct timespec start, finish;
    double bruteTime, geneticTime;
    long i, nfact;
    
    args(argc, argv, &places, &things);
    nfact = factorial(things.cities - 1);
    
    //**********************************************Brute Force************************************************

    clock_gettime(CLOCK_REALTIME, &start);
    currentPerm = createPermut(things.cities, places);
    bestBrutePerm = copyPermut(currentPerm);
    badPerm = copyPermut(currentPerm);
    for(i = 0; i < nfact; i++)
    {
        getNextPermut(currentPerm, currentPerm->order, currentPerm->length);
        
        //check if best permutation yet
        if(currentPerm->weight < bestBrutePerm->weight)
        {
            replacePermut(&bestBrutePerm, copyPermut(currentPerm));
        }
        
        //check if worse permutation yet
        if(currentPerm->weight > badPerm->weight)
        {
            replacePermut(&badPerm, copyPermut(currentPerm));
        }
    }
    
    clock_gettime(CLOCK_REALTIME, &finish);
    bruteTime = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BILLION;
   
    //*************************************************Genetic Algorithm******************************************
    
    clock_gettime(CLOCK_REALTIME, &start);
    currentGeneration = createGeneration(things.tours, things.mutations, things.elites, things.cities, places);
    sortGeneration(currentGeneration);
    for(i = 0; i < things.generations; i++)
    {
        nextGeneration(currentGeneration);
        sortGeneration(currentGeneration);
    }
    bestGeneticPerm = copyPermut(currentGeneration->permut[0]);
    clock_gettime(CLOCK_REALTIME, &finish);
    geneticTime = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BILLION;
    
    
    
    printResults(badPerm, bestBrutePerm, bestGeneticPerm, geneticTime, bruteTime);
    
    //Free Stuff
    freeGraph(places);
    freeGeneration(currentGeneration);
    freePermuts(currentPerm);
    freePermuts(bestGeneticPerm);
    freePermuts(bestBrutePerm);
    freePermuts(badPerm);
    
    
    
    
    return (EXIT_SUCCESS);
}
void printResults(PermuteT *badPerm, PermuteT *bestBrutePerm, PermuteT *bestGeneticPerm, double geneticTime, double bruteTime)
{
    printf("***************BRUTE FORCE RESULTS***************\n\n\n");
    printf("               ~Optimal Cost~                \n\n");
    printPermuts(bestBrutePerm);
    printf("\n");
    printf("           ~Percentage of best solution~         \n\n");
    printf("                   %lf\n\n", 100.0 * (badPerm->weight / bestBrutePerm->weight));
    printf("                 ~Execution Time~                        \n\n");
    printf("                     %lf\n", bruteTime);
    printf("\n\n\n");
    printf("***************GENETIC ALGORITHM RESULTS***************\n\n\n");
    printf("               ~Best Permutation~                     \n\n");
    printPermuts(bestGeneticPerm);
    printf("\n");
    printf("      ~Percentage of best brute force solution~\n");
    printf("                   %lf\n\n", 100.0 * (bestGeneticPerm->weight / bestBrutePerm->weight));
    printf("                  Execution Time\n");
    printf("                     %lf\n", geneticTime);
}
void args(int argc, char *argv[], GraphT **graph, stuffT *things)
{
    FILE *fp;
    int i, j;
    
    fp = fopen("thePresets.txt", "r");
    
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open ThePresets.txt\n");
        exit(1);
    }
    
    fscanf(fp, "%d", &(things->tours));
    fscanf(fp, "%d", &(things->generations));
    fscanf(fp, "%lf", &(things->mutations));
    fscanf(fp, "%lf", &(things->elites));
    fscanf(fp, "%d", &(things->cities));
    fclose(fp);
    
    *graph = createGraph(CITIES);
    
    fp = fopen("theCities.txt", "r");
    
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open theCities.txt\n");
        exit(1);
    }
    
    for(i = 0; i < CITIES; i++)
    {
        for(j = 0; j < CITIES; j++)
        {
            if(i != j)
            {
                fscanf(fp, "%lf", &((*graph)->adjMatrix[i][j]));
            } else {
                (*graph)->adjMatrix[i][j] = 0;
            }
        }
    }
    fclose(fp);
}
long factorial(int base)
{
    if(base < 0)
    {
        fprintf(stderr, "invalid factorial\n");
        exit(1);
    }
    
    if(base == 0 || base == 1)
    {
        return 1;
    }
    
    int i = base;
    long result = base;
    while(i > 2)
    {
        result *= --i;
    }
    
    return result;
}
