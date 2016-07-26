#include "generation.h"

GenerationT *createGeneration(int toursPerGeneration, double percMutations, double percElites, int permutLength, GraphT *graph)
{
    int i;
    
    GenerationT *newGeneration = (GenerationT *) malloc(sizeof(GenerationT));
    newGeneration->length = toursPerGeneration;
    newGeneration->permut = (PermuteT **) malloc(newGeneration->length * sizeof(PermuteT *));
    newGeneration->numMutations = (int) (percMutations * newGeneration->length);
    newGeneration->numElites = (int) (percElites * newGeneration->length);
    
    for(i = 0; i < newGeneration->length; i++)
    {
        newGeneration->permut[i] = createPermut(permutLength, graph);
        randomizePermut(newGeneration->permut[i]);
    }
    
    newGeneration->lastPermut = copyPermut(newGeneration->permut[newGeneration->length - 1]);
    
    return newGeneration;
}

void nextGeneration(GenerationT *newGeneration)
{
    int i, j;
    
    for(i = newGeneration->numElites; i < (newGeneration->numElites + newGeneration->numMutations); i++)
    {
        mutate(newGeneration->permut[i], pairs);
    }
     
    for(i = (newGeneration->numElites + newGeneration->numMutations), j = 0; i < newGeneration->length; i++)
    {
        while(j < newGeneration->numElites && i < newGeneration->length)
        {
            replacePermut(&(newGeneration->lastPermut), copyPermut(newGeneration->permut[j]));
            mutate(newGeneration->lastPermut, pairs);
            replacePermut(&(newGeneration->permut[i]), copyPermut(newGeneration->lastPermut));
            j++; i++;
        }
        getNextPermut(newGeneration->lastPermut, &(newGeneration->lastPermut->order[1]), newGeneration->lastPermut->length - 1);
        replacePermut(&(newGeneration->permut[i]), copyPermut(newGeneration->lastPermut));
    }
    
    randomizePermut(newGeneration->lastPermut);
}



void sortGeneration(GenerationT *newGeneration)
{
    quicksortPermuts(newGeneration->permut, 0, newGeneration->length - 1);
}

void freeGeneration(GenerationT *newGeneration)
{
    int i;
    for(i = 0; i < newGeneration->length; i++)
    {
        freePermuts(newGeneration->permut[i]);
    }
    free(newGeneration->permut);
    free(newGeneration->lastPermut);
    free(newGeneration);
}
