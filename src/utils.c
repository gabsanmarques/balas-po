#include "utils.h"

// Reads problem information from input file
Problem* readInput(const char *file_name) 
{
    FILE *file = fopen(file_name, "r");
    Problem *problem = NULL;
    int i, j;
    int n_coefficients, n_constraints;

    if(file == NULL)
    {
        printf("Erro ao ler o arquivo de entrada!\n");
        exit(1);
    }

    fscanf(file, "%d %d", &n_coefficients, &n_constraints);
    problem = allocateProblem(n_coefficients, n_constraints);

    for(i = 0; i < n_coefficients; i++) {
        fscanf(file, "%d", &problem->obj_function[i]);
    }

    for(i = 0; i < n_constraints; i++) {
        for(j = 0; j < n_coefficients + 1; j++) {
            fscanf(file, "%d", &problem->constraints[i][j]); 
        }
    }

    return problem;
} /* readInput */

/* Calculates the objective function value based at the J vector */
int calcObjValue(Problem *problem, int *j)
{
    int i;
    int sum = 0;

    for(i = 0; i < problem->n_coefficients; i++) {
        sum += (j[i] == 1 ? 1 : 0) * problem->obj_function[i];
    }

    return sum;
} /* calcObjValue */

/* Tests if the trivial solution is feasible */
void testTrivialSolution(Problem *problem, Node *node)
{
    for(int i = 0; i < problem->n_constraints; i++) {
        if(0 > problem->constraints[i][problem->n_coefficients])
            return;
    }
    
    problem->global_z = 0;
    problem->has_global_z = 1;
    node->feasible = 1;
    problem->result = (int*)malloc(sizeof(int) * problem->n_coefficients);
    memset(problem->result, 0, sizeof(int) * problem->n_coefficients);
} /* testTrivialSolution */