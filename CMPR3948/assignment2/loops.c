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
/*    Assignment Number: 2                                              */
/*                                                                      */
/*    Topic: Loops                                                      */
/*                                                                      */
/*    file name: loops.c                                                */ 
/*                                                                      */
/*    Date: 07/09/2017                                                  */
/*                                                                      */
/*    Objective: read scores from user input                            */
/*               find mean, min, max and print at the end               */
/*                                                                      */
/*    Comments: max input length is 1000 and in one line                */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1000

int main ()
{
    int min, max, sum = 0, num = 0;
    char input[MAX_INPUT_LEN];
    char *token;

    /* scan all scores */
    printf("enter your scores from different exams:\n");
    fgets(input, MAX_INPUT_LEN, stdin);
    printf("You entered: ");

    /* initialize min, max */
    token = strtok(input, ", ");
    min = atoi(token);
    max = atoi(token);

    /* collect and compute stats */
    while (token != NULL)
    {
        printf("%d ", atoi(token));
        min = atoi(token) < min ? atoi(token) : min;
        max = atoi(token) > max ? atoi(token) : max;
        sum += atoi(token);
        num++;
        token = strtok(NULL, ", ");
    }

    /* print analysis */
    printf("\nMin: %d, Max: %d, Average: %d\n", min, max, sum/num);

    return 0;
}
