#include "node.h"

// Allocates memory for a tree node
Node* allocateNode(Problem *problem) 
{
    Node *node = (Node*)malloc(sizeof(Node));
    
    // Initializing S set
    node->s = (int*)malloc(problem->n_constraints * sizeof(int));
    for(int i = 0; i < problem->n_constraints; i++) {
        node->s[i] = problem->constraints[i][problem->n_coefficients];
    }
    
    // Initializing J set
    node->j = (int*)malloc(problem->n_coefficients * sizeof(int));
    memset(node->j, 0, problem->n_coefficients * sizeof(int));

    // Initializing discardeds set
    node->discardeds = (int*)malloc(problem->n_coefficients * sizeof(int));
    memset(node->discardeds, 0, problem->n_coefficients * sizeof(int));

    // Other variables
    node->fathomed = 0;
    node->feasible = 0;
    node->z = 0;

    return node;
} /* allocateNode */

// Prints the informatio of a node
void printNode(Problem *problem, Node *node, int level)
{
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("====================\n");
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("Node:\n");
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("J: ");
    for(int k = 0; k < problem->n_coefficients; k++)
        printf("%d ", node->j[k]);
    printf("\n");
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("S: ");
    for(int k = 0; k < problem->n_constraints; k++)
        printf("%d ", node->s[k]);
    printf("\n");
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("Local z: %d\n", node->z);
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("Global Z: %d\n", problem->global_z);
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("Feasible: %d\n", node->feasible);
    for(int l = 0; l < level; l++)
        printf("\t");
    printf("====================\n");
} /* printNode */

// Frees memory allocated for a node
void freeNode(Node *node)
{
    SAFE_FREE(node->discardeds);
    SAFE_FREE(node->j);
    SAFE_FREE(node->s);
    SAFE_FREE(node);
} /* freeNode */