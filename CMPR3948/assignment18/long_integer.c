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
/*    Assignment Number: 18                                             */
/*                                                                      */
/*    Topic: queue                                                      */
/*                                                                      */
/*    file name: long_integer.c                                         */ 
/*                                                                      */
/*    Date: 08/27/2017                                                  */
/*                                                                      */
/*    Objective: read two long integers, add them and write to output   */
/*                                                                      */
/*    Comments:  0. assume inputs are valid positive integers           */
/*               1. we maintain input lists while adding; hence, we keep*/
/*               adding after short input is NULL                       */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 5
#define OVERFLOW_NUM 100000
#define BUFFER_LEN MAX_DIGITS+1
#define MAX_INPUT_LEN 200
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct node {
    int          val;
    struct node *next;
} node_t;

node_t *str2list(char *str);                  /* convert valid number string to integer node */
node_t *add_list(node_t *int1, node_t *int2); /* calculate sum of two integer nodes */
void print_list(node_t *node);                /* recursive printing from rear node */
void free_list(node_t *node);                 /* clean list */

/* global variable */
FILE *ofp;

/* convert valid number string to integer node */
node_t *str2list(char *str)
{
    int offset;
    char buffer[BUFFER_LEN];
    node_t *head, *node;

    if (str == NULL) {
        return NULL;
    }

    /* first node */
    offset = strlen(str) % MAX_DIGITS;
    if (offset) {
        strncpy(buffer, str, offset);
        buffer[offset] = '\0';
        head = (node_t *) malloc(sizeof(node_t));
        head->val = atoi(buffer);
        head->next = NULL;
    } else {
        head = NULL;
    }

    /* remaining nodes */
    str += offset;
    while(isdigit(*str)) {
        strncpy(buffer, str, MAX_DIGITS);
        buffer[MAX_DIGITS] = '\0';
        node = (node_t *) malloc(sizeof(node_t));
        node->val = atoi(buffer);
        node->next = head;
        head = node;
        str += MAX_DIGITS;
    }

    return head;
}

/*
 * calculate addtion for two nodes 
 * return malloced list containing sum
 * inputs are not mutated
 */
node_t *add_list(node_t *int1, node_t *int2)
{
    int val1, val2, sum, carry = 0;
    node_t *head, *node;
    if (int1 == NULL && int2 == NULL) {
        return NULL;
    }

    head = (node_t *) malloc(sizeof(node_t));
    node = head; // dummy head
    while (int1 || int2 || carry) {
        node->next = (node_t *) malloc(sizeof(node_t));
        node = node->next;

        if (int1) {
            val1 = int1->val;
            int1 = int1->next;
        } else {
            val1 = 0;
        }

        if (int2) {
            val2 = int2->val;
            int2 = int2->next;
        } else {
            val2 = 0;
        }

        sum = val1 + val2 + carry;
        if (sum >= OVERFLOW_NUM) {
            sum %= OVERFLOW_NUM;
            carry = 1;
        } else {
            carry = 0;
        }

        node->val = sum;
    }
    node->next = NULL;

    /* remove dummy head */
    node = head;
    head = node->next;
    free(node);

    return head;
}

/* recursive printing from rear node */
void print_list(node_t *node)
{
    int val, digits = MAX_DIGITS;

    if (node == NULL) {
        return;
    }

    print_list(node->next);

    /* print leading zeros */
    if (node->next != NULL) {
        print_and_record(" ");
        val = node->val;
        do {
            digits--;
            val /= 10;
        } while(val);
        while (digits--) {
            print_and_record("0");
        }
    }

    print_and_record("%d", node->val);
}

/* clean list */
void free_list(node_t *node)
{
    node_t *tmp_node;
    
    while(node) {
        tmp_node = node;
        node = node->next;
        free(tmp_node);
    }
}

int main (void)
{
    FILE *ifp;

    node_t *int1, *int2, *sum;
    char str1[MAX_INPUT_LEN], str2[MAX_INPUT_LEN];

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* read input */
    fgets(str1, MAX_INPUT_LEN, ifp);
    fgets(str2, MAX_INPUT_LEN, ifp);

    /* remove EOF or \n */
    str1[strlen(str1)-1] = '\0';
    str2[strlen(str2)-1] = '\0';

    /* form linear linked list */
    int1 = str2list(str1);
    int2 = str2list(str2);
    print_and_record("Form linear linked list\nList 1: ");
    print_list(int1);
    print_and_record("\nList 2: ");
    print_list(int2);
    print_and_record("\n");

    /* add linked list */
    sum = add_list(int1, int2);
    print_and_record("Add two integers\nSum:    ");
    print_list(sum);
    print_and_record("\n");

Cleanup:
    /* free memory*/
    free_list(int1);
    free_list(int2);
    free_list(sum);

    /* close file */
    fclose(ifp);
    fclose(ofp);

    return 0;
}
