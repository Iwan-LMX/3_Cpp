/**
 * Each function f1-f8 copies a `src` string to a dynamically
 * allocated `dst` string and prints it to stdout.
 * 
 * While the code can compile, each function contains a common
 * memory mistake that results in either a run-time error or
 * "undefined behaviour".
 * 
 * First identify each mistake, then correct it.  Fixing the 
 * code will require adding, modifying, moving, or removing 
 * one line of code from each of the 8 functions.
 * 
 * Once corrected, the code should compile without warnings,
 * run without error, and not leak any memory.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void 
f1(void) {
    char *src = "f1";
    char *dst = malloc(strlen(src)+1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

void 
f2(void) {
    char *src = "f2";
    char *dst = malloc(strlen(src));
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst); 
}

void 
f3(void) {
    char *src = "f3";
    char *dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    printf("%s\n", dst);
    free(dst);
}

void 
f4(void) {
    char *src = "f4";
    char *dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
}

void 
f5(void) {
    char *src = "f5";
    char *dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    free(dst);
    printf("%s\n", dst);
}

static void 
myprintf(char *string) {
    printf("%s\n", string);
    free(string);
}

void 
f6(void) {
    char *src = "f6";
    char *dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    myprintf(dst);
    free(dst);
}

void 
f7(void) {
    char *src = "f7";
    char *dst = malloc(strlen(src) + 1);
    assert(dst != NULL);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(src);
    free(dst);
}

void 
f8(void) {
    char *src = "f8";
    char *dst = malloc(strlen(src) + 1);
    strcpy(dst, src);
    printf("%s\n", dst);
    free(dst);
}

int 
main(void) {
    f1();
    f2();
    f3();
    f4();
    f5();
    f6();
    f7();
    f8();

    return 0;
}