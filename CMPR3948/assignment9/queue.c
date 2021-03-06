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
/*    Assignment Number: 9                                              */
/*                                                                      */
/*    Topic: queue                                                      */
/*                                                                      */
/*    file name: queue.c                                                */ 
/*                                                                      */
/*    Date: 08/13/2017                                                  */
/*                                                                      */
/*    Objective: read Enque/Deque choice and data from input file       */
/*               perform Enque/Deque and print queue every time         */
/*                                                                      */
/*    Comments:  assume input file is in expected format                */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_DATA 20
#define MAX_INPUT_LEN 200
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct _queue {
    int data[MAX_DATA];
    int front, rear;
} queue_t;

void enqueue(queue_t *queue, int data); /* add integer to queue */
int dequeue(queue_t *queue);            /* get and remove integer from queue */
void print_queue(queue_t *queue);       /* print queue from front to rear */

/* global variable */
FILE *ofp;

/* add integer to queue */
void enqueue(queue_t *queue, int data)
{
    queue->rear++;
    if (queue->rear == MAX_DATA) {
        queue->rear = 0;
    }

    if (queue->front == queue->rear) {
        print_and_record("queue overflow\n");
        exit(1);
    }

    queue->data[queue->rear] = data;
}

/* get and remove integer from queue */
int dequeue(queue_t *queue)
{
    if (queue->front == queue->rear) {
        print_and_record("queue underflow\n");
        exit(1);
    }
    
    queue->front++;
    if (queue->front == MAX_DATA) {
        queue->front = 0;
    }

    return queue->data[queue->front];
}

/* print queue from front to rear */
void print_queue(queue_t *queue)
{
    int i;
    for (i = queue->front; i != queue->rear;) {
        i++;
        if (i == MAX_DATA) {
            i = 0;
        }
        print_and_record("%2d ", queue->data[i]);
    }
    print_and_record("\n");
}

int main (void)
{
    FILE *ifp;
    char choice_line[MAX_INPUT_LEN];
    char data_line[MAX_INPUT_LEN];
    char *choice, *data, *saveptr1, *saveptr2;

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* initialize queue */
    queue_t queue;
    queue.rear = -1;
    queue.front = -1;

    /* read choice and data line from file until EOF */
    while(fgets(choice_line, MAX_INPUT_LEN, ifp)
          && fgets(data_line, MAX_INPUT_LEN, ifp)) {
        choice = strtok_r(choice_line+strlen("Choice:"), " ", &saveptr1);
        data   = strtok_r(data_line+strlen("Data:"), " ", &saveptr2);
        /*
         * parse choice/data line 
         * perform corresponding operation
         */
        while (choice) {
            if (*choice == 'E') {
                enqueue(&queue, atoi(data));
                print_and_record("Enque %d -> Queue: ", atoi(data));
                print_queue(&queue);
                data = strtok_r(NULL, " ", &saveptr2);
            } else if (*choice == 'D') {
                dequeue(&queue);
                print_and_record("Deque    -> Queue: ");
                print_queue(&queue);
            }
            choice = strtok_r(NULL, " ", &saveptr1);
        }
    }

    /* close file */
    fclose(ifp);
    fclose(ofp);

    return 0;
}
