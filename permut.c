#include <stdio.h>
#include <stdlib.h>
#include "permut.h"

PermuteT *createPermut(int length, GraphT *graph)
{
    int i;
    
    PermuteT *permut = (PermuteT *) malloc(sizeof(PermuteT));
    permut->length = length;
    permut->graph = graph;
    
    for(i = 0; i < permut->length; i++)
    {
        permut->order[i] = i;
    }
    calcPermutCost(permut);
    
    return permut;
}
void getNextPermut(PermuteT *permut, int array[], int n)
{
    int m, k, p, q;
    
    m = permut->length - 2;
    
    while(array[m] > array[m +1])
    {
        m = m - 1;
    }
    k = n - 1;
    
    while(array[m] > array[k])
    {
        k = k - 1;
    }
    swap(&(array[m]), &(array[k]));
    
    p = m + 1;
    q = n - 1;
    
    while(p < q)
    {
        swap(&(array[p]), &(array[q]));
        p++; q--;
    }
    
    calcPermutCost(permut);
}
PermuteT *copyPermut(PermuteT *permut)
{
    int i;
    
    PermuteT *permut1 = (PermuteT *) malloc(sizeof(PermuteT));
    permut1->length = permut->length;
    permut1->weight = permut->weight;
    permut1->graph = permut->graph;
    
    for(i = 0; i < permut1->length; i++)
    {
        permut1->order[i] = permut->order[i];
    }
    
    return permut1;
}

void replacePermut(PermuteT **going, PermuteT *from)
{
    freePermuts(*going);
    *going = from;
}

void randomizePermut(PermuteT *permut)
{
    int i, j, k;
    
    for(i = 1; i < permut->length; i++)
    {
        while(1)
        {
            srandom((int) clock());
            k = (random() % (permut->length - 1)) + 1;
            for(j = 1; j < i; j++)
            {
                if(k == permut->order[j]) break;
            }
            if(j >= i || k != permut->order[j])
            {
                break;
            }
        }
        permut->order[i] = k;
    }
    calcPermutCost(permut);
}

void calcPermutCost(PermuteT *permut)
{
    int i;
    
    permut->weight = 0;
    
    for(i = 0; i < permut->length - 1; i++)
    {
        permut->weight += permut->graph->adjMatrix[permut->order[i]][permut->order[i+1]];
    }
    permut->weight += permut->graph->adjMatrix[permut->length - 1][permut->order[0]];
}

void quicksortPermuts(PermuteT *permut[], int left, int right)
{
    int index = partition(permut, left, right);
    
 
    if(left < index - 1)
        quicksortPermuts(permut, left, index - 1);
    
    if(index < right)
        quicksortPermuts(permut, index, right);
    
}

int partition(PermuteT *permut[], int left, int right)
{
   int i = left, j = right;
    int pivot = (left + right) / 2;
    
    while(i <= j)
    {
        while(permut[i]->weight < permut[pivot]->weight) 
            i++;
        
        while(permut[pivot]->weight < permut[j]->weight) 
            j--;
        
        if(i <= j)
        {
            swapPermuts(&permut[i], &permut[j]);
            i++, j--;
        }
    } 
    
    return i;
}

void swapPermuts(PermuteT **permut1, PermuteT **permut2)
{
    PermuteT *temp = *permut1;
    *permut1 = *permut2;
    *permut2 = temp;
}

void mutate(PermuteT *permut, int numPairs)
{
    int i, left, right;
    
    for(i = 0; i < numPairs; i++)
    {
        srandom((int) clock());
        left = (random() % (permut->length - 2)) + 1;
        
        do{
            srandom((int) clock());
            right = (random() % (permut->length - 1)) + 1;
        }while(right < left);
        swap(&permut->order[left], &permut->order[right]);
    }
    
    calcPermutCost(permut);
}

void freePermuts(PermuteT *permut)
{
    free(permut);
}

void printPermuts(PermuteT *permut)
{
    int i;
    
    printf("              Order: ");
    
    for(i = 0; i < permut->length; i++)
    {
        printf(" %d ", permut->order[i]);
    }
    
    printf("\n");
    printf("                Weight: %lf\n    ", permut->weight);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
