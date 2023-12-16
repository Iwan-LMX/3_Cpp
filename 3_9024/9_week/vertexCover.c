#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void approxVertexCover(Graph G, int *res, int* optimal);
int main(int argc, char **argv){
//argv[0]: program name, argv[1]: seeds, argv[2]: repetition
    // printf("Debug: %d\n",atoi(argv[1]));
    srand(atoi(argv[1]));
// first, the user is prompted for the number of vertices
    printf("Enter the number of vertices: ");
    int nV;
    scanf("%d", &nV);
    Graph g = newGraph(nV);
// then, the user is repeatedly asked to input an edge by entering a "from" vertex followed by a "to" vertex
    Edge e;
    printf("Enter an edge (from): ");
    while(scanf("%d", &e.v)){
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
//find the optimal cover
    int* res = malloc(sizeof(int) * nV);
    assert(res != NULL);
    int optimal = nV+1;
    for(int i=0; i<atoi(argv[2]); i++){
        approxVertexCover(g, res, &optimal);
    }
//output result
    printf("Best vertex cover:\n");
    for(int i=0; i<optimal; i++){
        printf("%d\n", res[i]);
    }

    free(res);
    freeGraph(g);
}
int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
void approxVertexCover(Graph G, int *res, int *optimal){
    assert(G != NULL);
    int* C = malloc(sizeof(int) * numOfVertices(G));
    assert(C != NULL);
    memset(C, -1, sizeof(int) * numOfVertices(G));
    int len =0;
    Graph copy = copyGraph(G);
    while(!graphIsEmpty(copy)){
        Edge unusedE = randomEdge(copy);
        C[len++]= unusedE.v;
        C[len++] = unusedE.w;
        removeIncidentEdges(copy, unusedE);
    }
    freeGraph(copy);
    if (len <= *optimal){
        qsort(C, len, sizeof(int), cmp);
        *optimal = len;
        for(int j=0; j<len; j++){
            res[j] = C[j];
        }
    }
}