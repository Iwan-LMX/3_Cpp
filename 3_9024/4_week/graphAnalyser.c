#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "Graph.c"
#define MAX_NODES 1000

// determine and output the sequence of vertex degrees
void degrees(Graph g) {
   int nV = numOfVertices(g);
   int v, w, degree;

   printf("Vertex degrees:\n");
   for (v = 0; v < nV; v++) {
      degree = 0;
      for (w = 0; w < nV; w++) {
         if (adjacent(g,v,w)) {
            degree++;
         }
      }
      printf("%d", degree);
      if (v < nV-1) {
         printf(", ");
      } else {
         printf("\n");
      }
   }
}

// show all 3-cliques of graph g
void show3Cliques(Graph g) {
   int i, j, k;
   int nV = numOfVertices(g);

   printf("Triplets:\n");
   for (i = 0; i < nV-2; i++) {
      for (j = i+1; j < nV-1; j++) {
         if (adjacent(g,i,j)) {
            for (k = j+1; k < nV; k++) {
               if (adjacent(g,i,k) && adjacent(g,j,k)) {
                  printf("%d-%d-%d\n", i, j, k);
               }
            }
         }
      }
   }
}

// calculate and output the density of undirected graph g
void density(Graph g) {
   int nV = numOfVertices(g);
   int nE = 0;
   int v, w;
   double density;

   for (v = 0; v < nV-1; v++) {
      for (w = v+1; w < nV; w++) {
         if (adjacent(g,v,w)) {
            nE++;
         }
      }
   }

   density = (2.0 * (double)nE) / ((double)nV * ((double)nV - 1.0));
   printf("Density: %.3lf\n", density);
}

int main(void) {
   Edge e;
   int nV;

   printf("Enter the number of vertices: ");
   scanf("%d", &nV);
   Graph g = newGraph(nV);

   printf("Enter an edge (from): ");
   while (scanf("%d", &e.v) == 1) {
      printf("Enter an edge (to): ");
      scanf("%d", &e.w);
      insertEdge(g, e);
      printf("Enter an edge (from): ");
   }
   printf("Done.\n");

   degrees(g);
   show3Cliques(g);
   density(g);
   freeGraph(g);

   return 0;
}