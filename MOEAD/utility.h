//
// Created by sinnable on 8/9/20.
//

#ifndef UNTITLED_UTILITY_H
#define UNTITLED_UTILITY_H

# include "global.h"
# include "evaluation.h"
extern double **initialize_uniform_point (int  num, int *number_weight);
extern double cal_moead_fitness(INDIVIDUAL *ind, double *weight, MoeadFunction function_type);
extern void update_ideal_point_by_ind(INDIVIDUAL *pop, int index);
extern int update_subproblem(INDIVIDUAL *offspring, int pop_index, NeighborType type);

#endif //UNTITLED_UTILITY_H
