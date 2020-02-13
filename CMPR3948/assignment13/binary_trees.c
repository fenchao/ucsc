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
/*    Assignment Number: 13                                             */
/*                                                                      */
/*    Topic: queue                                                      */
/*                                                                      */
/*    file name: binary_trees.c                                         */ 
/*                                                                      */
/*    Date: 08/23/2017                                                  */
/*                                                                      */
/*    Objective: read input and create a binary tree                    */
/*               perform in/pre/post order traversal in both            */
/*               recursive & non-recursive method                       */
/*               delete as user wish                                    */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 200
#define FALSE 0
#define TRUE  1
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define print_and_record(...) \
{                             \
    printf(__VA_ARGS__);      \
    fprintf(ofp, __VA_ARGS__); \
}

typedef struct _node {
    int val;
    struct _node *left, *right;
} node_t;

typedef struct {
    node_t *node[MAX_STACK];
    int top;
} mystack_t;

void push(node_t *node);                  /* push node to stack */
node_t *pop();                            /* pop node from stack */
node_t * create_tree (int val);           /* init a binary tree node */
void insert_tree (node_t *root, int val); /* insert node to binary tree */
void intrav(node_t *root);                /* recursive inorder traversal */
void pretrav(node_t *root);               /* recursive preorder traversal */
void posttrav(node_t *root);              /* recursive postorder traversal */
void intrav_stack(node_t *root);          /* non-recursive inorder traversal */
void pretrav_stack(node_t *root);         /* non-recursive preorder traversal */
void posttrav_stack(node_t *root);        /* non-recursive postorder traversal */
int max_tree(node_t *root);               /* find max of binary tree */
int min_tree(node_t *root);               /* find min of binary tree */
int delete_tree(node_t *root, int val);   /* delete node from binary tree */
void free_tree(node_t *root);             /* free a binary tree */

/* global variable */
FILE *ofp;
mystack_t stack;

/* push node to stack */
void push(node_t *node)
{
    if (stack.top == MAX_STACK - 1) {
        print_and_record("stack overflow\n");
        exit(1);
    }

    stack.node[++stack.top] = node;
}

/* pop node from stack */
node_t *pop()
{
    if (stack.top == -1) {
        print_and_record("stack underflow\n");
        exit(1);
    }

    return (stack.node[stack.top--]);
}

/* init a binary tree node */
node_t * create_tree (int val)
{
    node_t *node = (node_t *) malloc (sizeof(node_t));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* insert node to binary tree */
void insert_tree (node_t *root, int val)
{
    node_t *node = root;
    while (node) {
        if (val == node->val) {
            print_and_record("Dup %d\n", val);
            return;
        }
        if (val < node->val) {
            if (node->left) {
                node = node->left;
            } else {
                node->left = create_tree(val);
                return;
            }
        } else {
            if (node->right) {
                node = node->right;
            } else {
                node->right = create_tree(val);
                return;
            }
        }
    }
}

/* recursive inorder traversal */
void intrav(node_t *root)
{
    if (root) {
        intrav(root->left);
        print_and_record("%d ", root->val);
        intrav(root->right);
    }
}

/* recursive preorder traversal */
void pretrav(node_t *root)
{
    if (root) {
        print_and_record("%d ", root->val);
        pretrav(root->left);
        pretrav(root->right);
    }
}

/* recursive postorder traversal */
void posttrav(node_t *root)
{
    if (root) {
        posttrav(root->right);
        posttrav(root->left);
        print_and_record("%d ", root->val);
    }
}

/* non-recursive inorder traversal */
void intrav_stack(node_t *root)
{
    node_t *node = root;
    stack.top = -1;
    do {
        if (node) {
            push(node);
            node = node->left;
        } else {
            node = pop();
            print_and_record("%d ", node->val);
            node = node->right;
        }
    } while (stack.top != -1 || node != NULL);
}

/* non-recursive preorder traversal */
void pretrav_stack(node_t *root)
{
    node_t *node = root;
    stack.top = -1;
    do {
        if (node) {
            print_and_record("%d ", node->val);
            push(node);
            node = node->left;
        } else {
            node = pop();
            node = node->right;
        }
    } while (stack.top != -1 || node != NULL);
}

/* non-recursive postorder traversal */
void posttrav_stack(node_t *root)
{
    node_t *node = root;
    stack.top = -1;
    do {
        while (node) {
            if (node->left)
                push(node->left);
            push(node);

            node = node->right;
        }

        node = pop();
        if (node->left && stack.node[stack.top] == node->left) {
            pop();
            push(node);
            node = node->left;
        } else {
            print_and_record("%d ", node->val);
            node = NULL;
        }
    } while (stack.top != -1);
}

/* find max of binary tree */
int max_tree(node_t *root)
{
    if (!root)
        return -1;
    while (root->right) {
        root = root->right;
    }
    return root->val;
}

/* find min of binary tree */
int min_tree(node_t *root)
{
    if (!root)
        return -1;
    while (root->left) {
        root = root->left;
    }
    return root->val;
}

/* delete node from binary tree */
int delete_tree(node_t *root, int val)
{
    int replace_val;
    node_t *node = root, *tmp_node;
    while(node) {
        if (val < node->val) {
            if (node->left && val == node->left->val) {
                /* delete left node of node */
                if (node->left->right) {
                    replace_val = min_tree(node->left->right);
                    delete_tree(node->left, replace_val);
                    node->left->val = replace_val;
                } else {
                    tmp_node = node->left;
                    node->left = tmp_node->left;
                    free(tmp_node);
                }
                return TRUE;
            } else {
                node = node->left;
            }
        } else if (val > node->val) {
            if (node->right && val == node->right->val) {
                /* delete right node of node */
                if (node->right->left) {
                    replace_val = max_tree(node->right->left);
                    delete_tree(node->right, replace_val);
                    node->right->val = replace_val;
                } else {
                    tmp_node = node->right;
                    node->right = tmp_node->right;
                    free(tmp_node);
                }
                return TRUE;
            } else {
                node = node->right;
            }
        } else {
            if (node->left == NULL && node->right == NULL) {
                print_and_record("root freed - val %d", val);
                free(node);
                return TRUE;
            } else if (node->left) {
                replace_val = max_tree(node->left);
                delete_tree(node, replace_val);
                node->val = replace_val;
                return TRUE;
            } else {
                replace_val = min_tree(node->right);
                delete_tree(node, replace_val);
                node->val = replace_val;
                return TRUE;;
            }
        }
    }

    return FALSE;
}

/* free a binary tree */
void free_tree(node_t *root)
{
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main (void)
{
    FILE *ifp;
    int val;
    node_t *root;

    /* open file */
    ifp = fopen(INPUT_FILE, "r");
    ofp = fopen(OUTPUT_FILE, "w");

    /* read input */
    fscanf(ifp, "%d, ", &val);
    root = create_tree(val);
    while (fscanf(ifp, "%d, ", &val) != EOF) {
        insert_tree(root, val);
    }

    /* inorder traversal */
    print_and_record("Inorder recursive:       ");
    intrav(root);
    print_and_record("\n");

    /* inorder traversal non-recursive */
    print_and_record("Inorder non-recursive:   ");
    intrav_stack(root);
    print_and_record("\n");

    /* preorder traversal */
    print_and_record("Preorder recursive:      ");
    pretrav(root);
    print_and_record("\n");

    /* preorder traversal non-recursive */
    print_and_record("Preorder non-recursive:  ");
    pretrav_stack(root);
    print_and_record("\n");

    /* postorder traversal */
    print_and_record("Postorder recursive:     ");
    posttrav(root);
    print_and_record("\n");

    /* postorder traversal non-recursive */
    print_and_record("Postorder non-recursive: ");
    posttrav_stack(root);
    print_and_record("\n");

    /* prompt user to delete */
    print_and_record("Num to delete: ");
    while(scanf("%d", &val) != EOF) {
        fprintf(ofp, "%d\n", val);

        if(delete_tree(root, val)) {
            print_and_record("Val %d found!\nInorder non-recursive:   ", val);
            intrav_stack(root);
            print_and_record("\n");
        } else {
            print_and_record("Val %d NOT found!\n", val);
        }

        print_and_record("Num to delete: ");
    }

Cleanup:
    free_tree(root);
    /* close file */
    fclose(ifp);
    fclose(ofp);

    return 0;
}
