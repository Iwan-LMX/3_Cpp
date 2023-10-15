#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int main(int argc, char *argv[]) {
    if(argc !=2){
        printf("Usage: %s number\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if(n>2){
        unsigned long long int* arr = malloc(n * sizeof(unsigned long long int));
        assert(arr != NULL);
        arr[0] = 1;
        arr[1] = 1;
        for(int i=2; i<n; i++){
            arr[i] = arr[i-1] + arr[i-2];
        }
        printf("%llu\n", arr[n-1]);
        free(arr);
    }else
        printf("1\n");
    return 0;
}