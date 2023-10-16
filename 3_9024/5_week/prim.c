// Prim's algorithm to compute MST ... COMP9024 23T2
#include "Set.h"
#include "WGraph.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

Graph prim(Graph g, int* res) {
    int nV = numOfVertices(g);
    Graph mst = newGraph(nV);
    Set usedV = newSet();
    
    Vertex v, w;
    Edge bestEdge, bestEdge2;
    int weight, minWeight;
    addtoSet(usedV, 0);
    /* NEEDS TO BE COMPLETED */
    while(sizeSet(usedV) < nV){
        minWeight = INT_MAX;
        for(v=0; v<nV; v++){
            if(memberOfSet(usedV, v))
                for(w=0; w<nV; w++){
                    weight = adjacent(g, v, w);
                    if(weight&& weight < minWeight && !memberOfSet(usedV, w)){
                        bestEdge.v = v;
                        bestEdge.w = w;
                        bestEdge.weight = minWeight = weight;
                    }
                }
        }
        insertEdge(mst, bestEdge); //WGraph是个有向图!
        bestEdge2.v=bestEdge.w; bestEdge2.w=bestEdge.v; bestEdge2.weight = bestEdge.weight;
        insertEdge(mst, bestEdge2);
        *res += bestEdge.weight;
        addtoSet(usedV, bestEdge.w);
    }
    return mst;
}

int main(void) {
    int num_v;
    // input
    printf("Enter the number of vertices: ");
    scanf("%d", &num_v);
    Graph g = newGraph(num_v);
    Edge e, s;
    printf("Enter an edge (from): ");
    while(scanf("%d", &e.v)){
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        //WGraph is proccess directed graph!
        s = e; s.v=e.w; s.w = e.v;
        insertEdge(g, e); insertEdge(g, s);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    // Processing
    int res = 0;
    prim(g, &res);
    //output
    printf("Sum of edge weights in Minimum Spanning Tree: %d", res);
    freeGraph(g);
    return 0;
}