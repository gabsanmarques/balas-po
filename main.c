#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "problem.h"
#include "node.h"
#include "utils.h"
#include "balas.h"

int main(int argc, char const *argv[])
{
    const char *input_file = argc > 1 ? argv[1] : "./inputs/input.txt";
    Problem *problem = readInput(input_file);
    Node *root = allocateNode(problem);

    printProblem(problem);
    testTrivialSolution(problem, root);
    balas(problem, root, 0);

    printf("===================\n");
    if(problem->result == NULL)
        printf("No feasible solution found!");
    else {
        printf("Solution: ");
        for(int k = 0; k < problem->n_coefficients; k++)
            printf("%d ", (problem->result[k] == 1 ? 1 : 0));
        printf("\nSolution value: %d", problem->global_z);
    }
    printf("\n===================\n");


    freeProblem(problem);
    
    return 0;
}