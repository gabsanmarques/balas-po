#ifndef BALAS_H
#define BALAS_H

#include "balas.h"
#include "node.h"
#include "problem.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void calcS(Problem *problem, Node *node);
void balas(Problem *problem, Node *node, int level);

#endif