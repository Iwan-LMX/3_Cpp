#include<bits/stdc++.h>
using namespace std;

int main(){
    char A[20];
    char s[20];
    strcpy(s, "TownHall");
    strcpy(A, "Central");
    if(strcmp(s, A) == 0){
        printf("0");
    }else if (strcmp(s, A) >0){
        printf("1");
    }
    return 0;
}