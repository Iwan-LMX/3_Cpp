#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include<string.h>
typedef struct{
    char* name;
    int transTime;
    int* vertices;
} station;
typedef struct{
    char* stopName;
    char time[5];
}timetable;
//set several global arguments, which includes the limits n, m, s etc.
station* stations;
timetable* timetables;
int n, m, s;
struct{
    int* bestPred;
    int bestDistance, bestEnd;
} res;
int main(){
    //1. store the stations and transfer time
    printf("Size of network: ");
    scanf("%d", &n);
    stations = (station*) malloc(sizeof(stations) * n);
    for(int i=0; i<n; i++){
        stations[i].name = (char*) malloc(20 * sizeof(char));
        scanf("%s", stations[i].name);
        scanf("%d", &stations[i].transTime);
    }
    for(int i=0; i<n; i++){
        printf("%s %d\n", stations[i].name, stations[i].transTime);
    }
    return 0;
}
