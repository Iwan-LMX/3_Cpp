// Graph ADT
// Adjacency Matrix Representation
#include "GraphCC.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct GraphRep {
   int  **edges;   // adjacency matrix
   int    nV;      // #vertices
   int    nE;      // #edges
   int    nC;      // #connected components
   int   *cc;      /* which component each vertex is contained in
                      i.e. array [0..nV-1] of 0..nC-1 */
   bool  *visited; // to track exploration during path check
} GraphRep;

Graph newGraph(int V) {
   assert(V >= 0);
   int i;

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;
   g->nC = V;

   // allocate memory for connected components array
   g->cc = malloc(V * sizeof(int));
   assert(g->cc != NULL);
   // allocate memory for visited array
   g->visited = malloc(V * sizeof(bool));
   assert(g->visited != NULL);
   // allocate memory for each row
   g->edges = malloc(V * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (i = 0; i < V; i++) {
      g->cc[i] = i;
      g->edges[i] = calloc(V, sizeof(int));
      assert(g->edges[i] != NULL);
   }

   return g;
}

int numOfVertices(Graph g) {
   return g->nV;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));
   int c, d, i;

   if (!g->edges[e.v][e.w]) {                    // edge e not in graph
      g->edges[e.v][e.w] = 1;
      g->edges[e.w][e.v] = 1;
      g->nE++;
      if (g->cc[e.v] != g->cc[e.w]) {            // v,w in different components?
         if (g->cc[e.v] < g->cc[e.w]) {          // ⇒ merge components c and d
            c = g->cc[e.v];
            d = g->cc[e.w];
         } else {
            c = g->cc[e.w];
            d = g->cc[e.v];
         }         
         for (i = 0; i < g->nV; i++) {
            if (g->cc[i] == d) {
               g->cc[i] = c;                    // move node from component d to c
            } else if (g->cc[i] == g->nC - 1) {
               g->cc[i] = d;                    // replace largest component ID by d
            }
         }
         g->nC--;
      }
   }
}

bool dfsPathCheck(Graph g, Vertex v, Vertex dest) {
   assert(g != NULL);
   Vertex w;

   g->visited[v] = true;
   if (v == dest) {
      return true;
   } else {
      for (w = 0; w < numOfVertices(g); w++) {
         if (adjacent(g, v, w) && !g->visited[w]) {
            if (dfsPathCheck(g, w, dest)) {
               return true;
            }
         }
      }
   }
   return false;
}

bool hasPath(Graph g, Vertex src, Vertex dest) {
   assert(g != NULL);
   Vertex v;

   g->visited = malloc(numOfVertices(g) * sizeof(bool));
   for (v = 0; v < numOfVertices(g); v++) {
      g->visited[v] = false;
   }
   return dfsPathCheck(g, src, dest);
}

void dfsNewComponent(Graph g, Vertex v, int componentID) {
   Vertex w;

   g->cc[v] = componentID;
   for (w = 0; w < numOfVertices(g); w++) {
      if (adjacent(g, v, w)) {
         if (g->cc[w] != componentID) {
            dfsNewComponent(g, w, componentID);
         }
      }
   }
}

void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));
   if (g->edges[e.v][e.w]) {   // edge e in graph
      g->edges[e.v][e.w] = 0;  // set to false
      g->edges[e.w][e.v] = 0;
      g->nE--;
      if (!hasPath(g, e.v, e.w)) {
         dfsNewComponent(g, e.v, g->nC);
         g->nC++;
      }
   }
}

bool adjacent(Graph g, Vertex v, Vertex w) {
   assert(g != NULL && validV(g,v) && validV(g,w));

   return (g->edges[v][w] != 0);
}

void showGraph(Graph g) {
   assert(g != NULL);
   int i, j;

   printf("Number of vertices: %d\n", g->nV);
   printf("Number of edges: %d\n", g->nE);
   for (i = 0; i < g->nV; i++) {
      for (j = i+1; j < g->nV; j++) {
         if (g->edges[i][j]) {
            printf("Edge %d - %d\n", i, j);
         }
      }
   }
}

void showComponents(Graph g) {
   assert(g != NULL);
   int i;

   printf("Connected components:\n");
   for (i = 0; i < g->nV; i++) {
      printf("%d", g->cc[i]);
      if (i < g->nV-1) {
         printf(", ");
      } else {
         printf("\n");
      }
   }
}

void freeGraph(Graph g) {
   assert(g != NULL);

   int i;
   for (i = 0; i < g->nV; i++) {
      free(g->edges[i]);
   }
   free(g->edges);
   free(g->cc);
   free(g->visited);
   free(g);
}