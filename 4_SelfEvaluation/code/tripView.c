#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<assert.h>
#include "PQueue.h"
typedef struct{
    char name[20];
    int transTime;
    int vertices[MAX_NODES];
} station;
typedef struct{
    char stopName[20];
    char time[5];
}timetable;
//set several global arguments, which includes the limits n, m, s etc.
station stations[MAX_NODES];
timetable timetables[MAX_NODES];
int n, m, s;
struct{
    int bestPred[MAX_NODES];
    int bestDistance, bestEnd;
    char latestStart[5];
} res;
//convert hhmm to minutes
int convert(char* time);
//this function can add new timetable to a station and try to insert transfer route
void checkPreStops(int cnt, Graph g, Edge e);
//dijkstra algorithm
void dijkstra(Graph g, Vertex source, char* to, char* due);
//output the route
void showPath(int v, int pred[]);
int main(){
/* 
Name: Mingxin Li
ID: z5433288
Time complexity: O({n^3}*{m^2}*log(mn))
Explanation: the biggest loop is in step 3, I use n to denote "while loop" times.
    For 2 "for loop" one is n times, and another for loop one average is m/2 times
    Then is the dijkstra algorithm, it is using PQueue which overall cost is O(E + V*log V); the number of E is around m*s; and the upper limit of V is n*m hence we got O(m*s + m*n*log m*n)
    So overall, the time complexity is O({n^3}*{m^2}*log(mn))
Start date: 2023-10-29  
*/
    //1. store the stations and transfer time
    printf("Size of network: ");
    scanf("%d", &n);
    assert(stations != NULL);
    for(int i=0; i<n; i++){
        scanf("%s", stations[i].name);
        scanf("%d", &stations[i].transTime);
    }

    //2. store the timetables & create vertex mapping & initialize the graph
    printf("Number of timetables: ");
    scanf("%d", &m);
    assert(timetables != NULL);
    for(int i=0; i<n; i++){
        memset(stations[i].vertices, -1, sizeof(stations[i].vertices));
    }
    Graph g = newGraph(m*n);
    int cnt = 0; //this is the index of vertices
    Edge e;
    //initialize the graph
    for(int i=0; i<m; i++){
        printf("Number of stops: ");
        scanf("%d", &s);
        for(int j=0; j<s; j++){
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
            cnt++;
        }
    }
    //3. input start & destination
    char from[20], to[20], due[5];
    printf("\nFrom: ");
    while(scanf("%s", from) && strcmp(from, "done")){
        printf("To: ");
        scanf("%s", to);
        printf("Arrive at or before: ");
        scanf("%s", due);

        res.bestDistance = INT_MAX;
        strcpy(res.latestStart, "0000");
        //find the from station
        for(int i=0; i<n; i++){
            if(!strcmp(stations[i].name, from)){
                //find the shortest path from start
                int j=0;
                int source = stations[i].vertices[j];
                while(source>=0 && j<m){
                    if(strcmp(due, timetables[source].time)>0){
                        dijkstra(g, source, to, due);
                    }
                    source = stations[i].vertices[++j];
                }

                //output the best plan
                printf("\n");

                if(res.bestDistance == INT_MAX) printf("No connection.\n");
                else showPath(res.bestEnd, res.bestPred);
                break;
            }
        }

        printf("\nFrom: ");
    }
    printf("Bye\n");

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
                preVertex = stations[i].vertices[++j]; 
            }
            //record this vertex to the stations
            stations[i].vertices[j] = cnt;
            return;
        }                    
    }
}
void showPath(int v, int pred[]) {
    if(pred[v] == -1) {
        printf("%s %s\n", timetables[v].time, timetables[v].stopName);
    }else{
        showPath(pred[v], pred);
        if(!strcmp(timetables[pred[v]].stopName, timetables[v].stopName)){
            //change line
            printf("Change at %s\n", timetables[v].stopName);
        }
        printf("%s %s\n", timetables[v].time, timetables[v].stopName);
    }
}
void dijkstra(Graph g, int source, char* to, char* due) {
   int  dist[MAX_NODES];
   int  pred[MAX_NODES];
   bool vSet[MAX_NODES];  // vSet[v] = true <=> v has not been processed
   int i, j;

   PQueueInit();
   int nV = numOfVertices(g);
   for (i = 0; i < nV; i++) {
      joinPQueue(i);
      dist[i] = INT_MAX;
      pred[i] = -1;
      vSet[i] = true;
   }
   dist[source] = 0;
   while (!PQueueIsEmpty()) {
      i = leavePQueue(dist);
      vSet[i] = false;
      if(dist[i] == INT_MAX) continue;
      for (j = 0; j < nV; j++) {
         if (vSet[j]) {
            int weight = adjacent(g,i,j);
            if (weight > 0 && dist[i]+weight < dist[j]) {
               dist[j] = dist[i] + weight;  // relax along (s,t,weight)
               pred[j] = i;
            }
         }
      }
   }
   for (i = 0; i< nV; i++) {
      //if this node is destination, arrive in time, latest possible.
      if (!strcmp(timetables[i].stopName, to) && strcmp(due, timetables[i].time)>=0) {
        int difference = strcmp(timetables[source].time, res.latestStart);
        if(difference>0 || (difference == 0 && dist[i] < res.bestDistance)){
            res.bestDistance = dist[i];
            memcpy(res.bestPred, pred, sizeof(pred));
            res.bestEnd = i;
            strcpy(res.latestStart, timetables[source].time);
        }
      }
   }
}