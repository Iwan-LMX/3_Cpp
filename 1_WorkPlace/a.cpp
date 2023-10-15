#include<bits/stdc++.h>
using namespace std;
int unknown(int A[], int l, int r){
    if(l > r)
        return -1;
    else if(l == r) return A[l];
    else{
        int q = l + (r - l)/4;
        int ansL = unknown(A, l, q);
        int ansR = unknown(A, q+1, r);
        return ansL > ansR ? ansL:ansR;
    }
}
int main(){
    int A[] = {6, 4, 2, 9, 2, 8, 6, 5};
    int s;
    printf("%d\n", unknown(A, 1, 8));
    return 0;
}