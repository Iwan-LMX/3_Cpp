#include<stdio.h>
#include<string.h>
#include<stdbool.h>
bool isHeterogram(char A[], int len){
    int letter[27];
    memset(letter, 0, sizeof(letter));
    for(int i=0; i<len; i++){
        letter[A[i] - 'a']++;
        if(letter[A[i] - 'a']++ >= 2) return false;
    }
    return true;
}
int main(){
    char word[32];
    memset(word, 0, sizeof(word));
    printf("Enter a string: ");
    scanf("%s", word);
    if(isHeterogram(word, strlen(word))){
        printf("yes\n");
    }else{
        printf("no\n");
    }
    return 0;
}