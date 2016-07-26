#include "graph.h"

GraphT *createGraph(int numNodes)
{
    int i;
    
    GraphT *graph = (GraphT *) malloc(sizeof(GraphT));
    graph->numNodes = numNodes;
    graph->adjMatrix = (double **) malloc(numNodes * sizeof(double *));
    
    for(i = 0; i < numNodes; i++)
    {
        graph->adjMatrix[i] = (double *) malloc(numNodes * sizeof(double));
    }
    
    return graph;
}
void freeGraph(GraphT *graph)
{
    int i;
    
    for(i = 0; i < graph->numNodes; i++)
    {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}