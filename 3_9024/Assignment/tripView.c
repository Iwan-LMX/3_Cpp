/* 
    Name: Mingxin Li
    ID: z5433288
    Time complexity:
    Start date: 2023-10-29  
 */
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include<string.h>
#include "PQueue.h"
typedef struct{
    char* name;
    int transTime;
    int* vertices;
} station;
typedef struct{
    char* stopName;
    int stationIndex;
    char time[5];
}timetable;
//set several global arguments, which includes the limits n, m, s etc.
station* stations;
timetable* timetables;
int n, m, s;
struct{
    int* bestPred;
    int bestDistance, bestStart;
} res;
//convert hhmm to minutes
int convert(char* time);
//check if the station can transfer
void addTransfer(int cnt);
//dijkstra algorithm
void dijkstra(Graph g, Vertex source, char* to, char* due);
int main(){
    //1. store the stations and transfer time
    printf("Size of network: ");
    scanf("%d", &n);
    stations = (station*) malloc(sizeof(*stations) * n);
    for(int i=0; i<n; i++){
        stations[i].name = (char*) malloc(20 * sizeof(char));
        scanf("%s", stations[i].name);
        scanf("%d", &stations[i].transTime);
    }

    //2. store the timetables & create vertex mapping & initialize the graph
    printf("Number of timetables: ");
    scanf("%d", &m);
    timetables =(timetable*) malloc(m*n* sizeof(*timetables));
    res.bestPred = (int*) malloc(m*n* sizeof(int));
    res.bestDistance = INT_MAX;
    for(int i=0; i<n; i++){
        stations[i].vertices = (int*) malloc(m * sizeof(int));
        memset(stations[i].vertices, -1, sizeof(int)*m);
    }
    Graph g = newGraph(m*n);
    int cnt = 0; //this is the index of vertices
    Edge e;
    //initialize the graph
    for(int i=0; i<m; i++){
        printf("Number of stops: ");
        scanf("%d", &s);
        for(int j=0; j<s; j++){
            timetables[cnt].stopName = (char*) malloc(20 * sizeof(char));
            //update timetables
            scanf("%s", timetables[cnt].stopName);
            scanf("%s", timetables[cnt].time);
            //calculate weight & insert edges
            if(j>=1){
                e.v = cnt - 1; e.w = cnt;
                e.weight = convert(timetables[cnt].time) - convert(timetables[cnt-1].time);
                insertEdge(g, e);
            }
            //check if this station has other depart time
            checkPreStops(cnt, g, e);
        }
    }
    //3. input start & destination
    char from[20], to[20], due[5];
    printf("\nFrom: ");
    while(scanf("%s", from) && !strcmp(from, "done")){
        printf("To: ");
        scanf("%s", to);
        printf("Arrive at or before: ");
        scanf("%s", due);

        //find the from station
        for(int i=0; i<n; i++){
            if(!strcmp(timetables[i].stopName, from)){
                //find the shortest path from start
                int j=0;
                int source = stations[i].vertices[j];
                while(source>=0 && strcmp(due, timetables[source].time)>0){
                    dijkstra(g, source, to, due);
                }

                //output the best plan
                printf("\n");
                showPath(res.bestStart, res.bestPred);
                break;
            }
        }

        printf("\nFrom: ");
    }
    printf("Bye\n");

    //free the memory
    for(int i=0; i<n; i++){
        free(stations[i].name);
        freeLL(stations[i].vertices);
    }
    free(stations);
    for(int i=0; i<n*m; i++){
        if(timetables == NULL) break;
        free(timetables[i].stopName);
        freeLL(timetables[i].time);
    }
    free(timetables);
    freeGraph(g);
    return 0;
}

int convert(char* time){
    int hh = (time[0]-'0')*10 + (time[1]-'0');
    int minutes = hh*60 + (time[2]-'0')*10 + (time[3]-'0');
    return minutes;
}
void checkPreStops(int cnt, Graph g, Edge e){
    for(int i=0; i<n; i++){
        if(!strcmp(timetables[cnt].stopName, stations[i].name)){
            //add an edge represent can transfer in a station 
            int j=0;
            int preVertex = stations[i].vertices[j]; 
            while(preVertex >= 0){//if this vertex existed
                e.weight = convert(timetables[preVertex].time) - convert(timetables[cnt].time);
                if(e.weight >= stations[i].transTime){
                    e.v = cnt; e.w = preVertex;
                    insertEdge(g, e);
                }else if(-e.weight >= stations[i].transTime){
                    e.v = preVertex; e.w = cnt;
                    e.weight = -e.weight;
                    insertEdge(g, e);
                }
                preVertex = stations[i].vertices[j++]; 
            }
            //record this vertex to the stations
            stations[i].vertices[j] = cnt;
            timetables[cnt].stationIndex = i;
            return;
        }                    
    }
}
void showPath(int v, int pred[]) {
   if (pred[v] == -1) {
      printf("%d", v);
   } else {
      showPath(pred[v], pred);
      printf("-%d", v);
   }
}
void dijkstra(Graph g, Vertex source, char* to, char* due) {
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
      //if this node is destination
      if (!strcmp(timetables[s].stopName, to) && dist[s] < res.bestDistance) {
         if(strcmp(due, timetables[s].time)>=0){
            res.bestDistance = dist[s];
            res.bestPred = pred;
            res.bestStart = s;
         }
      }
   }
}