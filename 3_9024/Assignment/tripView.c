/* 
    Name: Mingxin Li
    ID: z5433288
    Time complexity:
    Start date: 2023-10-29  
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"WGraph.h"
typedef struct{
    char* name;
    int time;
} station;
typedef struct{
    char* stop;
    char time[5];
}timetable;
int main(){
    //1. store the stations
    int n;
    printf("Size of network: ");
    scanf("%d", &n);
    station* stations = (station*) malloc(sizeof(*stations) * n);
    for(int i=0; i<n; i++){
        stations[i].name = (char*) malloc(20 * sizeof(char));
        scanf("%s", stations[i].name);
        scanf("%d", &stations[i].time);
    }

    //2. store the timetables and initialize the graph
    int m, s;
    printf("Number of timetables: ");
    scanf("%d", &m);
    timetable* timetables =(timetable*) malloc(m*n* sizeof(*timetables));
    Graph g = newGraph(m*n);
    int cont = 0; //this is the index of vertices
    
    for(int i=0; i<m; i++){//initialize the graph
        printf("Number of stops: ");
        scanf("%d", &s);
        for(int j=0; j<s; j++){
            timetables[cont].stop = (char*) malloc(20 * sizeof(char));
            //update timetables
            scanf("%s", timetables[cont].stop);
            scanf("%s", timetables[cont].time);
            //insert edges
            
        }
    }


    //free the memory
    free(stations);
    free(timetables);
    freeGraph(g);
    return 0;
}