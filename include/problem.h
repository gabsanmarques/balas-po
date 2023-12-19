#ifndef PROBLEM_H
#define PROBLEM_H
#define SAFE_FREE(ptr) if (ptr) { free(ptr); ptr = NULL; }

#include <stdlib.h>
#include <stdio.h>

struct problem {
    int n_coefficients;
    int n_constraints;
    int *obj_function;
    int **constraints;
    int global_z;
    int has_global_z;
    int *result;
};

typedef struct problem Problem;

Problem* allocateProblem(int n_coefficients, int n_constraints);
void freeProblem(Problem *problem);
void printProblem(Problem *problem);

#endif