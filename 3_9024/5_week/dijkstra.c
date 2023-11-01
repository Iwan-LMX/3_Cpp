// Starting code for Dijkstra's algorithm ... COMP9024 23T2

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "PQueue.h"

void showPath(int v, int pred[]) {
   if (pred[v] == -1) {
      printf("%d", v);
   } else {
      showPath(pred[v], pred);
      printf("-%d", v);
   }
}

void dijkstraSSSP(Graph g, Vertex source) {
   int  dist[MAX_NODES];
   int  pred[MAX_NODES];
   bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
   int s, t;

   PQueueInit();
   int nV = numOfVertices(g);
   for (s = 0; s < nV; s++) {
      joinPQueue(s);
      dist[s] = INT_MAX;
      pred[s] = -1;
      vSet[s] = true;
   }
   dist[source] = 0;
   while (!PQueueIsEmpty()) {
      s = leavePQueue(dist);
      vSet[s] = false;
      for (t = 0; t < nV; t++) {
         if (vSet[t]) {
            int weight = adjacent(g,s,t);
            if (weight > 0 && dist[s] < INT_MAX && dist[s]+weight < dist[t]) {
               dist[t] = dist[s] + weight;  // relax along (s,t,weight)
               pred[t] = s;
            }
         }
      }
   }
   for (s = 0; s < nV; s++) {
      printf("%d: ", s);
      if (dist[s] < INT_MAX) {
         printf("distance = %d, shortest path: ", dist[s]);
         showPath(s, pred);
         putchar('\n');
      } else {
         printf("no path\n");
      }
   }
}

int main(void) {
    Edge e; int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    int source;
    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter an edge (from): ");
    while(scanf("%d", &e.v)){
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        printf("Enter the weight: ");
        scanf("%d", &e.weight);
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    dijkstraSSSP(g, source);
}