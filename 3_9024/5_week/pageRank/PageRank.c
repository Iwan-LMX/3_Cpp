#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "WGraph.h"
typedef struct{
    int v, inbound, outbound;
    int score;
    
} rank;
void insertionSort(rank array[], int n) {
   for (int i = 0; i < n; i++) {
      rank node = array[i];
      int j=i-1;
      while(j>=0 && (array[j].inbound<node.inbound || (array[j].inbound==node.inbound && array[j].score < node.score))){
        array[j+1] = array[j];
        j--;
      }
      array[j+1] = node;
   }
}
int main(){
    int n_webs, links;
    Edge e;
    //initialise the graph
    printf("Enter the number of webpages: ");
    scanf("%d", &n_webs);
    Graph g = newGraph(n_webs);
    //input the vertices
    printf("Enter a webpage: ");
    while(scanf("%d", &e.v) == 1){
        printf("Enter the number of links on webpage %d: ", e.v);
        scanf("%d", &links);
        for(int i=0; i<links; i++){
            printf("Enter a link on webpage %d: ", e.v);
            scanf("%d", &e.w);
            e.weight = 1;
            insertEdge(g, e);
        }
        printf("Enter a webpage: ");
    }
    printf("Done.\n\n");
    //process the nodes
    rank res[n_webs];
    for(int i=0; i<n_webs; i++){
        res[i].v = i;
        res[i].inbound=res[i].outbound=res[i].score=0;
    }

    for(int v=0; v<n_webs; v++)
    for(int w=0; w<n_webs; w++)
        if(adjacent(g, v, w)){
            res[v].outbound++;
            res[w].inbound++;
        }
    
    // calculate score
    for(int v=0; v<n_webs; v++){
        res[v].score = res[v].outbound;
        for(int w=0; w<n_webs; w++)
            if(adjacent(g, v, w)) 
                res[v].score +=  res[w].inbound;
    }
    insertionSort(res, n_webs);
    //output the result
    printf("Webpage ranking:\n");
    for(int i=0; i<n_webs; i++){
        printf("%d has %d inbound links and scores %d on outbound links.\n", res[i].v, res[i].inbound, res[i].score);
    }
    return 0;
}