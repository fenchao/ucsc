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
/*    Assignment Number: 11                                             */
/*                                                                      */
/*    Topic: linked list                                                */
/*                                                                      */
/*    file name: linked_list.c                                          */ 
/*                                                                      */
/*    Date: 08/14/2017                                                  */
/*                                                                      */
/*    Objective: read number from input file and assemble linked list   */
/*               reverse linked list and delete as user wishes          */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct _node {
    int num;
    struct _node *next;
} node_t;

void insert(node_t **head_p, int num);     /* create node with num and insert to linked list */
void reverse(node_t **head_p);             /* reverse linked list */
int find_delete(node_t **head_p, int num); /* find and delete node with num*/
void print_list(node_t *head);             /* print linked list */
void free_list(node_t *head);              /* cleanup linked list */

/* global variable */
FILE *ofp;

/* create node with num and insert to linked list */
void insert(node_t **head_p, int num)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->num = num;
    p->next = *head_p;
    *head_p = p;
}

/* reverse linked list */
void reverse(node_t **head_p)
{
    node_t *cur, *rev = NULL;
    while (*head_p) {
        cur = *head_p;
        *head_p = (*head_p)->next;
        cur->next = rev;
        rev = cur;
    }
    *head_p = rev;
}

/* 
 * find node and delete
 * return FASLE if not found
 */
int find_delete(node_t **head_p, int num)
{
    node_t *prev = *head_p;
    node_t *cur;

    if (prev && prev->num == num) {
        *head_p = prev->next;
        free(prev);
        return TRUE;
    }

    while (prev) {
        cur = prev->next;
        if (cur && cur->num == num) {
            prev->next = cur->next;
            free(cur);
            return TRUE;
        }
        prev = cur;
    }
    return FALSE;
}

/* print linked list */
void print_list(node_t *head)
{
    while (head) {
        print_and_record("%d ", head->num);
        head = head->next;
    }
    print_and_record("\n");
}

/* cleanup linked list */
void free_list(node_t *head)
{
    node_t *p;

    while (head) {
        p = head;
        head = p->next;
        free(p);
    }
}

int main (void)
{
    FILE *ifp;
    node_t *head = NULL;
    int num;

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* read input and assemble linked list */
    print_and_record("Input:                   ");
    while (fscanf(ifp, "%d, ", &num) != EOF) {
        print_and_record("%d ", num);
        insert(&head, num);
    }
    print_and_record("\n");

    /* print original linked list */
    print_and_record("Original order:          ");
    print_list(head);

    /* reverse linked list */
    reverse(&head);

    /* print reversed linked list */
    print_and_record("Reversed order:          ");
    print_list(head);

    /* delete as user wishes */
    print_and_record("num to delete: ");
    while(scanf("%d", &num) != EOF) {
        fprintf(ofp, "%d\n", num);
        if (find_delete(&head, num)) {
            print_and_record("Delete %2d. List:         ", num);
        } else {
            print_and_record("Nothing to delete. List: ");
        }
        print_list(head);
        print_and_record("num to delete: ");
    }

Cleanup:
    free_list(head);
    head = NULL;
    fclose(ifp);
    fclose(ofp);

    return 0;
}
