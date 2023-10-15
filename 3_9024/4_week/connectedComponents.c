#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GraphCC.h"

int main(void) {
   Edge e;
   int n;
   char c;

   printf("Enter the number of vertices: ");
   scanf("%d", &n);
   Graph g = newGraph(n);

   printf("[i]nsert or [r]emove an edge: ");
   while (scanf(" %c %d %d", &c, &e.v, &e.w) == 3) {
      if (c == 'i') {
         insertEdge(g, e);
      } else if (c == 'r') {
         removeEdge(g, e);
      }
      printf("[i]nsert or [r]emove an edge: ");
   }

   showComponents(g);
   freeGraph(g);
   return 0;
}