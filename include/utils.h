#ifndef UTILS_H
#define UTILS_H

#include "problem.h"
#include "node.h"
#include <stdio.h>

Problem* readInput(const char *file_name);
int calcObjValue(Problem *problem, int *j);
void testTrivialSolution(Problem *problem, Node *node);

#endif