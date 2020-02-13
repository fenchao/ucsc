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
/*    Assignment Number: 10                                             */
/*                                                                      */
/*    Topic: recursion                                                  */
/*                                                                      */
/*    file name: hanoi.c                                                */ 
/*                                                                      */
/*    Date: 08/20/2017                                                  */
/*                                                                      */
/*    Objective: prompt user to define number of disks                  */
/*               play haoni with recursion method                       */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

void hanoi(int n, char from, char aux, char to); /* hanoi recursion helper */

/* global variable */
FILE *ofp;
int disk; /* disk to be final on peg C */

/* hanoi recursion helper */
void hanoi(int n, char from, char aux, char to) {
    if (n == 1) {
        if (disk == n) {
            print_and_record("Final ");
            disk--;
        }
        print_and_record("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n-1, from, to, aux);
    if (disk == n) {
        print_and_record("Final ");
        disk--;
    }
    print_and_record("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n-1, aux, from, to);
}

int main (void)
{
    int num;

    ofp = fopen(OUTPUT_FILE, "a");

    /* set game with num of disks */
    print_and_record("\nhow many disks to play hanoi: ");
    scanf("%d", &num);
    fprintf(ofp, "%d\n", num);

    /* recursion call */
    disk = num;
    hanoi(num, 'A', 'B', 'C');

    fclose(ofp);

    return 0;
}
