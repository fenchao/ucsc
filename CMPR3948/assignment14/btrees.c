/************************************************************************/
/****************                  prologue               ***************/ 
/*                                                                      */
/*              University of California Extension, Santa Cruz          */
/*                                                                      */
/*                          Advanced C Programming                      */
/*                                                                      */
/*                    Instructor: Rajainder A. Yeldandi                 */
/*                                                                      */
/*    Author: Fenchao Du                                                */
/*                                                                      */
/*    Assignment Number: 14                                             */
/*                                                                      */
/*    Topic: btree                                                      */
/*                                                                      */
/*    file name: btrees.c                                               */ 
/*                                                                      */
/*    Date: 08/30/2017                                                  */
/*                                                                      */
/*    Objective: read input and create a binary tree                    */
/*               perform in/pre/post order traversal in both            */
/*               recursive & non-recursive method                       */
/*               delete as user wish                                    */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD 5
#define FALSE 0
#define TRUE  1
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct _btree {
    int num;
    struct _btree * child[MAX_CHILD];
    int key[MAX_CHILD - 1];
    struct _btree * parent;
    int index;
} btree_t;

/* global varibles */
FILE *ofp;

int main (void)
{
    FILE *ifp;
    int val;

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* read input */
    while (fscanf(ifp, "%d, ", &val) != EOF) {
        printf("%d\n",val);
    }

Cleanup:
    /* close file */
    fclose(ifp);
    fclose(ofp);

    return 0;
}
