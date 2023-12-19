#include "problem.h"

// Allocates memory for a problem structure
Problem* allocateProblem(int n_coefficients, int n_constraints)
{
    int i;

    Problem *problem = (Problem *)malloc(sizeof(Problem));
    problem->result = NULL;
    problem->obj_function = (int*)malloc(n_coefficients * sizeof(int));
    problem->constraints = (int**)malloc(n_constraints * sizeof(int*));
    for(i = 0; i < n_constraints; i++) {
        problem->constraints[i] = (int*)malloc((n_coefficients + 1) * sizeof(int));
    }
    problem->has_global_z = 0;
    problem->n_coefficients = n_coefficients;
    problem->n_constraints = n_constraints;

    return problem;
} /* allocateProblem */

// Frees memory allocated for a problem structure
void freeProblem(Problem *problem)
{
    int i;

    for(i = 0; i < problem->n_constraints; i++) {
        SAFE_FREE(problem->constraints[i]);
    }
    SAFE_FREE(problem->constraints);
    SAFE_FREE(problem->result);
    SAFE_FREE(problem->obj_function);
    SAFE_FREE(problem);
} /* freeProblem */

// Prints all informations of a problem
void printProblem(Problem *problem) 
{
    int i, j;

    printf("=====================\n");
    printf("Problem definition:\nObjective function:\n");

    // Printing objective function
    printf("\tmin ");
    for(i = 0; i < problem->n_coefficients; i++)
    {
        if(i == 0 || problem->obj_function[i] < 0)
            printf("%d(x%d) ", problem->obj_function[i], i+1);
        else
            printf("+ %d(x%d) ", problem->obj_function[i], i+1);  
    }

    // Printing constraints
    printf("\ns.a.\n");
    for(i = 0; i < problem->n_constraints; i++)
    {
        printf("\t");
        for(j = 0; j < problem->n_coefficients; j++)
        {
            if(j == 0 || problem->constraints[i][j] < 0)
                printf("%d(x%d) ", problem->constraints[i][j], j+1);
            else
                printf("+ %d(x%d) ", problem->constraints[i][j], j+1); 
        }
        printf("< %d\n", problem->constraints[i][problem->n_coefficients]);
    }
    printf("=====================\n");
} /* printProblem */