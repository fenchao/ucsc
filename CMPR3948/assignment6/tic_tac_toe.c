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
/*    Assignment Number: 6                                              */
/*                                                                      */
/*    Topic: functions                                                  */
/*                                                                      */
/*    file name: tic_tac_toe.c                                          */ 
/*                                                                      */
/*    Date: 07/15/2017                                                  */
/*                                                                      */
/*    Objective: two players play tic-tac-toe                           */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

#define BOARD_SIZE 4 // max dimension of row and column
#define PLAYER1 1 // player1 move
#define PLAYER2 2 // player2 move
#define FALSE 0
#define TRUE 1
#define OUTPUT_FILE "record.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(fp, __VA_ARGS__); \
}

void init_game();  /* initiate game */
void print_board(); /* print current board*/
int check_move(int row, int col); /* check if a move is valid */
int play_turn(); /* play one turn */
int game_over(); /* check if one player has won or game is draw */

/* global variable */
int board[BOARD_SIZE][BOARD_SIZE];
FILE *fp;

/* initiate game */
void init_game()
{
    int row, col;

    /* empty the board */
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = 0; 
        }
    }

    /* print welcome message & initial board */
    print_and_record("Welcome to play tic-tac-toe!!!\n");
    print_board();
}

/* print current board */
void print_board()
{
    int row, col;
    print_and_record("-----------------\n");
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            switch (board[row][col]) {
                case PLAYER1:
                    print_and_record("| X ");
                    break;
                case PLAYER2:
                    print_and_record("| O ");
                    break;
                default:
                    print_and_record("|   ");
                    break;
            }
        }
        print_and_record("|\n-----------------\n");
    }
}

/* check if a move is valid */
int check_move(int row, int col)
{
    if (row < 0 || row >= BOARD_SIZE
        || col < 0 || col >= BOARD_SIZE
        || board[row][col]) {
        return FALSE;
    }
    return TRUE;
}

/* play one turn */
int play_turn()
{
    static int turn = PLAYER1;
    int row, col;

    /* get user input */
    print_and_record("Player%d move (row, col): ", turn);
    scanf("%d, %d", &row, &col);
    fprintf(fp, "%d, %d\n", row, col); /* record user input */

    /* check & set move */
    if (!check_move(row, col)) {
        print_and_record("Invalid move!\n");
        return FALSE;
    } else {
        board[row][col] = turn;
    }

    /* change turn */
    turn = PLAYER1+PLAYER2-turn;
    return TRUE;
}

/* check if game is over */
int game_over()
{
    int row, col, win;

    /* check row */
    for (row = 0; row < BOARD_SIZE; row++) {
        /* no point to check further if empty */
        if (!board[row][0]) {
            continue;
        }
        win = TRUE;
        for (col = 1; col < BOARD_SIZE; col++) { 
            if (board[row][0] != board[row][col]) {
                /* mark row not win if we see a different move */
                win = FALSE;
                break;
            }
        }
        if (win) {
           /* whole row is same */
            print_and_record("Congratulations! Player%d WIN!!!\n", board[row][0]);
            return TRUE;
        }
    }

    /* check col */
    for (col = 0; col < BOARD_SIZE; col++) {
        /* no point to check further if empty */
        if (!board[0][col]) {
            continue;
        }
        win = TRUE;
        for (row = 1; row < BOARD_SIZE; row++) { 
            if (board[0][col] != board[row][col]) {
                /* mark col not win if we see a different move */
                win = FALSE;
                break;
            }
        }
        if (win) {
            /* whole column is same */
            print_and_record("Congratulations! Player%d WIN!!!\n", board[0][col]);
            return TRUE;
        }
    }

    /* check diagonal 1 */
    if (board[0][0]) {
        win = TRUE;
        for (row = 0, col = 0; row < BOARD_SIZE; row++, col++) {
            if (board[0][0] != board[row][col]) {
                /* mark diagonal 1 not win */
                win = FALSE;
                break;
            }
        }
        if (win) {
            print_and_record("Congratulations! Player%d WIN!!!\n", board[0][0]);
            return TRUE;
        }
    }

    /* check diagonal 2 */
    if (board[0][BOARD_SIZE-1]) {
        win = TRUE;
        for (row = 0, col = BOARD_SIZE-1; row < BOARD_SIZE; row++, col--) {
            if (board[0][BOARD_SIZE-1] != board[row][col]) {
                /* mark diagonal 2 not win */
                win = FALSE;
                break;
            }
        }
        if (win) {
            print_and_record("Congratulations! Player%d WIN!!!\n", board[0][BOARD_SIZE-1]);
            return TRUE;
        }
    }

    /* check if there is space so game is not over */
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (!board[row][col]) {
                /* find empty cell */
                return FALSE;
            }
        }
    }

    /* board is full and no one wins */
    print_and_record("OMG!! Game is a tie!\n");
    return TRUE;
}

int main (void)
{
    fp = fopen(OUTPUT_FILE, "a");

    /* initiate the game */
    init_game();

    do {
        /* play one turn */
        if (play_turn()) {
            /* print board only if move is valid */
            print_board();
        }
    } while(!game_over()); /* keep play if game not over */

    fclose(fp);

    return 0;
}
