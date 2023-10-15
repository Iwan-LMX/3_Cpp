#include<stdio.h>
#include "Graph.h"
#define MAX_NODES 1000
int visited[MAX_NODES];

bool dfsCycleCheck(Graph g, Vertex v,ertex u){
    visited[v] = true;
    Vertex w;
    for (w = 0; w < numOfVertices(g); w++)
    {
        if (adjacent(g, v, w)){
            if (!visited[w]){
                if (dfsCycleCheck(g, w, v))
                    return true;
            }
            else if (w != u){
                return true;
            }
        }
    }
    return false;
}

bool hasCycle(Graph g){
    int v, nV = numOfVertices(g);
    for (v = 0; v < nV; v++)
        visited[v] = false;
    for (v = 0; v < nV; v++)
        if (!visited[v])
            if (dfsCycleCheck(g, v, v))
                return true;
    return false;
}
int main(){
    return 0;
}