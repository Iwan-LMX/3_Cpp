#include<bits/stdc++.h>
using namespace std;

int main(){
    char A[20]="1014";
    char s[5] = "0923";
    printf("%d\n", strcmp(A, s));
    if(strcmp(A, s)>0){
        printf("Hello\n");
    }else if(strcmp(A, s)<0){
        printf("2\n");
    }
    return 0;
}