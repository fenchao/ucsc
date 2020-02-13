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
/*    Assignment Number: 8                                              */
/*                                                                      */
/*    Topic: stack                                                      */
/*                                                                      */
/*    file name: stack.c                                                */ 
/*                                                                      */
/*    Date: 07/31/2017                                                  */
/*                                                                      */
/*    Objective: read expression from input file, evaluate validity of  */
/*               scopes                                                 */
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

typedef struct node {
    char sym;
    struct node *next;
} node_t;

void push(node_t **top_p, char sym); /* push symbol to stack */
char pop(node_t **top_p);            /* pop symbol from stack */
void free_list(node_t **top_p);      /* free whole linked list */
void print_stack(node_t *top);       /* print whole stack reversely - expression order */
int parse(node_t **top_p, char sym); /* parse symbol using stack operation */

/* global variable */
FILE *ofp;

/* push symbol to stack */
void push(node_t **top_p, char sym)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->sym = sym;
    p->next = *top_p;
    *top_p = p;
}

/* pop symbol from stack */
char pop(node_t **top_p)
{
    char sym;
    node_t *p = *top_p;

    if (p) {
        sym = p->sym;
        *top_p = p->next;
        free(p);
    } else {
        print_and_record("Empty Stack!\n");
        exit(1);
    }

    return sym;
}

/* free whole linked list */
void free_list(node_t **top_p)
{
    node_t *p;

    while (*top_p) {
        p = *top_p;
        *top_p = p->next;
        free(p);
    }
}

/* print whole stack reversely */
void print_stack(node_t *top)
{
    if (!top) {
        return;
    }
    print_stack(top->next);
    print_and_record("%c", top->sym);
}

/* 
 * parse symbol using stack operation
 * return FALSE immediately if expression is invalid
 */
int parse(node_t **top_p, char sym)
{
    char t_sym;

    switch(sym) {
        /* begin scope */
        case '{':
        case '[':
        case '(':
            push(top_p, sym);
            print_and_record("%c Push  Stack ", sym);
            print_stack(*top_p);
            print_and_record("\n");
            return TRUE;
        /* end scope */
        case '}':
        case ']':
        case ')':
            // empty stack
            if (*top_p == NULL) {
                print_and_record("%c Pop   Empty Stack\n", sym);
                return FALSE;
            }
            break;
        default: // ignore
            print_and_record("%c Ignore\n", sym);
            return TRUE;
    }

    /* check corresponding begin & end scope */        
    print_and_record("%c Pop   Stack ", sym);
    print_stack(*top_p);
    t_sym = pop(top_p);
    if ((t_sym == '{' && sym == '}')
        || (t_sym == '[' && sym == ']')
        || (t_sym == '(' && sym == ')')) {
        print_and_record(" & %c match\n", sym);
        return TRUE;
    }

    print_and_record(" & %c NOT match\n", sym);
    return FALSE;
}

int main (void)
{
    char sym;
    FILE *ifp;
    node_t *top = NULL;

    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /*
     * for invalid expression,
     * we won't read whole file or 
     * not all elements on stack are poped
     */
    do {
        sym = fgetc(ifp);
    } while(sym != EOF && parse(&top, sym));

    if (sym != EOF || top) {
        print_and_record("Invalid Expression!\n");
    } else {
        print_and_record("Valid Expression!\n");
    }

Cleanup:
    free_list(&top);
    fclose(ifp);
    fclose(ofp);

    return 0;
}
