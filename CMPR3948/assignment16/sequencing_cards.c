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
/*    Assignment Number: 16                                             */
/*                                                                      */
/*    Topic: queue                                                      */
/*                                                                      */
/*    file name: sequencing_cards.c                                     */ 
/*                                                                      */
/*    Date: 08/23/2017                                                  */
/*                                                                      */
/*    Objective: read required card sequence,                           */
/*               shuffle the card in the way                            */
/*               that we can open it like magic                         */
/*                                                                      */
/*    Comments:  0. We created two lists called stack & list            */
/*                  They can pop/push to top/bottom                     */
/*               1. "10" is the only 2-char char, we defined str2char   */
/*                  & char2str to handle this special case              */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LEN 3
#define MAX_INPUT_LEN 200
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct _node {
    char sym;
    struct _node *next;
} node_t;

typedef struct _list {
    node_t *top;
    node_t *bottom;
} list_t;

void insert_bottom(list_t *list, char sym); /* insert at bottom */
void insert_top(list_t *list, char sym);    /* insert at top */
char pop_top(list_t *list);                 /* get and remove from top */
char pop_bottom(list_t *list);              /* get and remove bottom */
void print_list(list_t *list);              /* print list from top to bottom */
void destroy_list(list_t *list);            /* recycle list */
char str2char(char *str);                   /* convert string to char to store in list */
char *char2str(char ch);                    /* convert char back to string to print */

/* global variable */
FILE *ofp;
char buffer[MAX_BUFFER_LEN]; /* buffer to convert char to string */

/* add to bottom list */
void insert_bottom(list_t *list, char sym)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->sym = sym;
    p->next = NULL;

    if (list->bottom) {
        list->bottom->next = p;
    } else {
        list->top = p;
    }

    list->bottom = p;
}

/* add to top of list */
void insert_top(list_t *list, char sym)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->sym = sym;
    p->next = list->top;

    if (list->bottom == NULL) {
        list->bottom = p;
    }

    list->top = p;
}

/* get and pop from top */
char pop_top(list_t *list)
{
    char sym;
    node_t *p = list->top;

    if (p == NULL) {
        print_and_record("Empty Queue!\n");
        exit(1);
    }

    if(p == list->bottom) {
        list->bottom = NULL;
    }

    sym = p->sym;
    list->top = p->next;
    free(p);
    return sym;
}

/* get and pop from bottom */
char pop_bottom(list_t *list)
{
    char sym;
    node_t *p = list->top;

    if (p == NULL) {
        print_and_record("Empty Queue!\n");
        exit(1);
    }

    if(p == list->bottom) {
        sym = list->bottom->sym;
        free(list->bottom);
        list->top = NULL;
        list->bottom = NULL;
        return sym;
    }

    while (p->next != list->bottom) {
        p = p->next;
    }
    sym = list->bottom->sym;
    free(list->bottom);
    p->next = NULL;
    list->bottom = p;

    return sym;
}

/* print list from top to bottom */
void print_list(list_t *list)
{
    node_t *p = list->top;
    while (p) {
        print_and_record("%s ", char2str(p->sym));
        p = p->next;
    }
    print_and_record("\n");
}

/* destroy and mark list freed */
void destroy_list(list_t *list)
{
    node_t *p = list->top;
    while(p) {
        list->top = p->next;
        free(p);
        p = list->top;
    }
    list->top = NULL;
    list->bottom = NULL;
}

/* convert string to char */
char str2char(char *str) {
    if (str[0] == '1' && str[1] == '0') {
        return '0'; /* store "10" as '0' */
    }
    return *str;
}

/* convert char to string */
char *char2str(char ch) {
    if (ch == '0') {
        sprintf(buffer, "10");
    } else {
        sprintf(buffer, "%c", ch);
    }
    return buffer;
}

int main (void)
{
    FILE *ifp;
    char *sym_str, sym_char;
    char input[MAX_INPUT_LEN];
    list_t list, stack;
    int round = 0;

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* initialize list & stack */
    list.top = NULL;
    list.bottom = NULL;
    stack.top = NULL;
    stack.bottom = NULL;
    
    /* read required sequence */
    while (fgets(input, MAX_INPUT_LEN, ifp)) {

        /* store input to stack */
        print_and_record("Round %d\n\nRead input:\n", round);
        sym_str = strtok(input, ", ");
        while(sym_str) {
            sym_char = str2char(sym_str);
            insert_top(&stack, sym_char);
            print_and_record("%s ", char2str(sym_char));
            sym_str = strtok(NULL, ", ");
        }
        print_and_record("\nTemporary store input to stack:\n")
        print_list(&stack);
        print_and_record("\n");
    
        /* shuffle */
        print_and_record("Shuffle:\n");
        while(stack.top) {
            /* read from stack */
            sym_char = pop_top(&stack);

            /* shuffle: open -> top */
            print_and_record("Read %2s               ", char2str(sym_char));
            insert_top(&list, sym_char);
            print_and_record("Deck: ");
            print_list(&list);

            /* shuffle: bottom -> top */
            sym_char = pop_bottom(&list);
            print_and_record("Move %2s (bottom->top) ", char2str(sym_char));
            insert_top(&list, sym_char);
            print_and_record("Deck: ");
            print_list(&list);
        }
        print_and_record("\nShuffled Deck: ");
        print_list(&list);
        print_and_record("\n");

        /* shuffle done recycle stack */
        destroy_list(&stack);

        /* open deck */
        print_and_record("Open:\n");
        while(list.top) {
            /* open deck: top->bottom */
            sym_char = pop_top(&list);
            print_and_record("Move %2s (top->bottom) ", char2str(sym_char));
            insert_bottom(&list, sym_char);
            print_and_record("Deck: ");
            print_list(&list);

            /* open deck: top->open */
            sym_char = pop_top(&list);
            print_and_record("Open %2s               ", char2str(sym_char));
            print_and_record("Deck: ");
            print_list(&list);

            /* store opened cards */
            insert_bottom(&stack, sym_char);
        }
        print_and_record("\nOpened Deck: ");
        print_list(&stack);
        print_and_record("\n");

        /* recycle stack and list */
        destroy_list(&list);
        destroy_list(&stack);

        round++;
    }

    /* close file */
    fclose(ifp);
    fclose(ofp);

    return 0;
}
