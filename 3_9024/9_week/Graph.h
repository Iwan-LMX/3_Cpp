// Graph ADT interface ... COMP9024 23T2
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);
Edge  randomEdge(Graph g);                   // returns a random element from the array of edges of g
Graph removeIncidentEdges(Graph g, Edge e);  // removes all edges from g that have at least one endpoint in common with e
Graph copyGraph(Graph g);                  // returns a newly created graph that is an exact copy of g
bool  graphIsEmpty(Graph g);                 // checks if graph g has no edges