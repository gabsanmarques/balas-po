#ifndef NODE_H
#define NODE_H
#define SAFE_FREE(ptr) if (ptr != NULL) { free(ptr); ptr = NULL; }

#include "problem.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
    int *s;
    int *j;
    int z;
    int* discardeds;
    int fathomed;
    int feasible;
};

typedef struct node Node;

Node* allocateNode(Problem *problem);
void printNode(Problem *problem, Node *node, int level);
void freeNode(Node *node);

#endif