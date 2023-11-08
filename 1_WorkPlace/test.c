#include<stdio.h>
// #include<stdlib.h>
// #include <limits.h>
// #include<string.h>
// typedef struct{
//     char* name;
//     int transTime;
//     int* vertices;
// } station, *stationP;
int main(){
    int n;
    //1. store the stations and transfer time
    printf("Size of network: ");
    scanf("%d", &n);
    int str[n];
    // stationP stations[n];
    // scanf("%s", stations[0].name);
    for(int i=0; i<n; i++){
        printf("%d\n", str[i]);
    }
    return 0;
}
