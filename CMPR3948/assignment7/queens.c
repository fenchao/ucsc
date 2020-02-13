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
/*    Assignment Number: 7                                              */
/*                                                                      */
/*    Topic: backtracking                                               */
/*                                                                      */
/*    file name: queens.c                                               */ 
/*                                                                      */
/*    Date: 07/30/2017                                                  */
/*                                                                      */
/*    Objective: given queen in 1st row, place 8 queens not attacking   */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

#define BOARD_SIZE 8 // max dimension of row and column
#define DIAGONAL_SIZE (2*BOARD_SIZE-1) // number of diagonals
#define OFFSET (BOARD_SIZE-1) // offset for down_diag
#define FALSE 0
#define TRUE 1
#define OUTPUT_FILE "8queens.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(fp, __VA_ARGS__); \
}

void init_board();  /* initiate column and diagonals */
void print_board(); /* print 8 queen board*/
int  user_col();    /* get valid column for 1st row */
int  check_queen(int row, int col); /* check if row-col is valid to place queen */
void set_queen(int row, int col);   /* set queen recursively */

/* global variable */
FILE *fp;
int sol_num;
int queen_col[BOARD_SIZE];
int up_diag[DIAGONAL_SIZE];
int down_diag[DIAGONAL_SIZE];

/* initiate column and diagonals */
void init_board()
{
    int i;

    sol_num = 0;

    for (i = 0; i < BOARD_SIZE; i++) {
        queen_col[i] = -1;
    }
    for (i = 0; i < DIAGONAL_SIZE; i++) {
        up_diag[i] = FALSE;
        down_diag[i] = FALSE;
    }
}

/* print 8 queen board */
void print_board()
{
    int row, col;

    print_and_record("---------------------------------\n");
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (queen_col[row] == col) {
                if (row == 0) {
                    print_and_record("| U ");
                } else {
                    print_and_record("| Q ");
                }
            } else {
                print_and_record("|   ");
            }
        }
        print_and_record("|\n---------------------------------\n");
    }
}

/* check if row-col is valid to place queen */
int check_queen(int row, int col)
{
    int i = 0;

    /* safe check - check board range */
    if (row < 0 || row >= BOARD_SIZE
        || col < 0 || col >= BOARD_SIZE) {
        return FALSE;
    }

    /* check diagonal */
    if (up_diag[col+row]
        || down_diag[row-col+OFFSET]) {
        return FALSE;
    }

    /* check columns for all previous rows */
    for (i = 0; i < row; i++) {
        if (queen_col[i] == col) {
            return FALSE;
        }
    }

    /* all checks pass */
    return TRUE;
}

/* get valid column for 1st row */
int user_col()
{
    int col;

    /* user prompt */
    print_and_record("\nFor 1st row, which column to place queen: ");
    scanf("%d", &col);
    fprintf(fp, "%d\n", col); /* record user input */

    /* return valid column */
    if (check_queen(0, col)) {
        return col;
    } else {
        print_and_record("Invalid column!\n");
        return user_col();
    }
}

/* set queen recursively */
void set_queen(int row, int col)
{
    /* positive termination - all rows have queen */
    if (row == BOARD_SIZE) {
        if(!sol_num) { // only print 1st solution
            print_board();
        }
        sol_num++;
        return;
    }
    /* negative termination - no column can place queen */
    if (col == BOARD_SIZE) {
        return;
    }

    /* if we can place queen here */
    if (check_queen(row, col)) {
        /* set queen */
        queen_col[row] = col;
        up_diag[row+col] = TRUE;
        down_diag[row-col+OFFSET] = TRUE;

        /* let's set next row recursively */
        set_queen(row+1, 0);

        /* 
         * No matter positive/negative termination,
         * we are not interested in this row-col anymore.
         */

        /* reset queen - backtracking */
        queen_col[row] = -1;
        up_diag[row+col] = FALSE;
        down_diag[row-col+OFFSET] = FALSE;
    }

    /* 
     * No matter if positive/negative termination,
     * or col is invalid at this row,
     * we are now interested in next col of this row.
     */

    /* 1st row is user defined*/
    if (row != 0) {
        set_queen(row, col+1);
    }
}

int main (void)
{
    int col;

    fp = fopen(OUTPUT_FILE, "a");

    /* initiate columns and diagonals */
    init_board();

    /* get valid column for 1st row */
    col = user_col();

    /* set queen recursively */
    set_queen(0, col);

    /* print result */
    print_and_record("%d total solutions."
                     " Solutions can be mirrored.\n", sol_num);

    fclose(fp);

    return 0;
}
