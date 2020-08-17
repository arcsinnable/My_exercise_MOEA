//
// Created by sinnable on 6/20/20.
//

#ifndef UNTITLED_EVALUATION_H
#define UNTITLED_EVALUATION_H
#include "global.h"
#include "evaluation.h"

extern void evaluation(INDIVIDUAL *pop, int pop_size);
extern void evaluation_individual(INDIVIDUAL *population, int index);
extern double indicator(INDIVIDUAL pop1, INDIVIDUAL pop2);
extern double cal_weighted_sum(INDIVIDUAL *pop, double *weight_vector, int obj_num);
extern double cal_TCH(INDIVIDUAL *pop, double *weight_vector, int obj_num);
extern double cal_ITCH (INDIVIDUAL *pop, double *weight_vector, int obj_num);


#endif //UNTITLED_EVALUATION_H
