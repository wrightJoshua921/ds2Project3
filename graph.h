/* 
 * File:   graph.h
 * Author: wrigh
 *
 * Created on October 8, 2015, 12:05 PM
 */

#ifndef GRAPH_H
#define	GRAPH_H
#define pairs 2

#include <stdlib.h>

typedef struct graph{
    int numNodes;
    double **adjMatrix;
}GraphT;


GraphT *createGraph(int numNodes);

void freeGraph(GraphT *graph);

#endif	/* GRAPH_H */

