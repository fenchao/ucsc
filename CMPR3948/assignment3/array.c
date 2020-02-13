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
/*    Assignment Number: 3                                              */
/*                                                                      */
/*    Topic: Arrays                                                     */
/*                                                                      */
/*    file name: array.c                                                */ 
/*                                                                      */
/*    Date: 07/08/2017                                                  */
/*                                                                      */
/*    Objective: print array in original/reversed order                 */
/*               prompt user to give num and find indices               */
/*                                                                      */
/*    Comments: We will return first occurance of index if there is a   */
/*              duplicate                                               */
/*              index/indice starts from 0                              */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_LEN 100
#define MAX_INPUT_LEN 1000
#define QUIT_NUM -999

int main ()
{
    int arr[MAX_ARRAY_LEN];
    int len = 0;
    int index, num;
    char input[MAX_INPUT_LEN];
    char *token;

    /* scan array input */
    printf("enter your integer array\n");
    fgets(input, MAX_INPUT_LEN, stdin);

    /* read input to array */
    token = strtok(input, ", ");
    while (token != NULL)
    {
        arr[len] = atoi(token);
        len++;
        token = strtok(NULL, ", ");
    }

    /* print in original order */
    printf("\noriginal order:\n");
    for (index = 0; index < len; index++)
    {
        printf("%d", arr[index]);
        if (index + 1 < len) {
            printf(", ");
        } else {
            printf("\n");
        }
    }

    /* print in reversed order */
    printf("\nreversed order:\n");
    for (index = len-1; index >= 0; index--)
    {
        printf("%d", arr[index]);
        if (index != 0) {
            printf(", ");
        } else {
            printf("\n");
        }
    }

    /* identiy the indices */
    do {
        printf("\nenter a number to find index (%d to quit)\n", QUIT_NUM);
        scanf("%d", &num);
        if(num == QUIT_NUM) {
            break;
        }
        for (index = 0; index < len; index++)
        {
            if (arr[index] == num) {
                printf("arr[%d] = %d\n", index, num);
                break;
            }
            if (index == len-1) {
                printf("num %d not in array\n", num);
            }
        }
    } while(num != QUIT_NUM);

    return 0;
}
