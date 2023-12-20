#include "balas.h"

// Calculates the S set for the node
void calcS(Problem *problem, Node *node)
{
    for(int i = 0; i < problem->n_constraints; i++) {
        for(int r = 0; r < problem->n_coefficients; r++) {
            node->s[i] -= (node->j[r] == 1 ? 1 : 0) * problem->constraints[i][r];
        }
    }
} /* calcS */

// Runs the Balas algorithm starting at the root node
void balas(Problem *problem, Node *node, int level)
{
    int i, r;
    int discarded;
    int sum;
    int selected_branching = -1;
    int greatest_v = INT_MIN;
    
    node->z = calcObjValue(problem, node->j);
    if(node->feasible) {
        if(!problem->has_global_z) {
            problem->has_global_z = 1;
            problem->global_z = node->z;
            problem->result = node->j;
        } else if(node->z < problem->global_z) {
            problem->global_z = node->z;
            memcpy(problem->result, node->j, sizeof(int) * problem->n_coefficients);
        }
    }

    // Calculating S set for the new node
    calcS(problem, node);

    printNode(problem, node, level);

    /* ==========================================================
        TEST 1: For any free variable x_r, if a_ir >= 0 for all i
        corresponding to S^t_i < 0, then x_r cannot improve the
        infeasibility of the problem and must be discarded as
        non promising.
       ========================================================== */ 
    for(r = 0; r < problem->n_coefficients; r++) {
        // Fixed variables are not tested
        if(node->j[r] != 0)
            continue;

        discarded = 0;

        // If a_ir >= 0 for all constraints where S^t_i < 0
        // then discards x_r.
        for(i = 0; i < problem->n_constraints; i++) {
            if(node->s[i] < 0) {
                if(problem->constraints[i][r] >= 0) {
                    discarded = 1;
                } else {
                    discarded = 0;
                    break;
                }
            }
        }

        node->discardeds[r] = discarded;
    } /* TEST 1 */

    /* ==========================================================
        TEST 2: For any free variable xr, if cr + z^t >= z' then
        xr cannot lead to an improved solution and hence must be
        discarded.
       ========================================================== */ 
    if(problem->has_global_z) {
        for(r = 0; r < problem->n_coefficients; r++) {
            if(node->j[r] != 0)
                continue;
            if(!node->discardeds[r] && problem->obj_function[r] + node->z >= problem->global_z)
                node->discardeds[r] = 1;
        }
    } /* TEST 2 */

    /* ==========================================================
        TEST 3: Consider the ith constraint ai1x1 + ... ainxn +
        Si = bi, for wich S^t_i < 0. Let Nt define the set of
        free variables not discarded by test 1 and 2. None of the
        free variable in Nt are promising if for at least one
        S^t_i < 0, the following condition is satisfied: the sum
        for j in Nt of min{0, a_ij} > S^t_i. This actually says
        that the set Nt cannot lead to a feasible solution and
        hence must be discarded alltogether. In this case, Jt is
        said to be fathomed.
       ========================================================== */ 
    for(i = 0; i < problem->n_constraints; i++) {
        sum = 0;
        if(node->s[i] < 0) {
            for(r = 0; r < problem->n_coefficients; r++) {
                if(node->j[r] != 0)
                    continue;
                if(node->discardeds[r] != 1)
                    sum += problem->constraints[i][r] < 0 ? problem->constraints[i][r] : 0;
            }
        }
        if(sum > node->s[i]) {
            node->fathomed = 1;
            for(int l = 0; l < level; l++)
                printf("\t");
            printf("Infeasible solution: %d > %d at constraint %d!\n", sum, node->s[i], i+1);
            return;
        }
    }

    /* =============================================================
        TEST 4: If Nt is not empty, the branching variable is
        selected as the one corresponding to
            v^t_k = max{v^t_j}, for j in Nt,
            where v^t_i = sum for i = 1 to m of min{0, S^t_i - a_ij}
        If v^t_k = 0, xk = 1 together with Jt yields an improved
        feasible solution. In this case, J_t+1, which is defined by
        Jt with {k} augmented on the right, is fathomed.
       ============================================================= */ 
    for(r = 0; r < problem->n_coefficients; r++) {   
        if(node->discardeds[r] == 1 || node->j[r] != 0) {
            continue;
        }
        sum = 0;

        for(i = 0; i < problem->n_constraints; i++)
            sum += node->s[i] - problem->constraints[i][r] < 0 ? node->s[i] - problem->constraints[i][r] : 0;

        if(sum > greatest_v) {
            greatest_v = sum;
            selected_branching = r;
        }
    }

    // If none variable is selected for branching, return
    if(selected_branching == -1) {
        for(int l = 0; l < level; l++)
            printf("\t");
        printf("No variable selected for branching!\n");
        return;
    }

    for(int l = 0; l < level; l++)
        printf("\t");
    printf("Selected variable for branching: x%d\n", selected_branching + 1);

    // Generates left node fixing branching variable to 1
    Node* left = allocateNode(problem);
    memcpy(left->j, node->j, problem->n_coefficients * sizeof(int));
    left->j[selected_branching] = 1;
    if(greatest_v == 0)
        left->feasible = 1;

    // Generates right node fixing branching variable to 0
    Node* right = allocateNode(problem);
    memcpy(right->j, node->j, problem->n_coefficients * sizeof(int));
    right->j[selected_branching] = -1;

    balas(problem, left, level + 1);
    balas(problem, right, level + 1);

    freeNode(node);
} /* balas */