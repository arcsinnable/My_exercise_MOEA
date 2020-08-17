//
// Created by sinnable on 6/20/20.
//

#ifndef UNTITLED_METAHEURITICS_H
#define UNTITLED_METAHEURITICS_H
#include "global.h"
#include "metaheuritics.h"

extern void mix_population(INDIVIDUAL *mix_pop, INDIVIDUAL *parent_pop, INDIVIDUAL *offspring_pop, int pop_size);
extern void copy_pop(INDIVIDUAL *mix_pop, INDIVIDUAL *pop_select);
extern double fitness_evaluation(INDIVIDUAL *pop_select, int popsize);
extern void select_population(INDIVIDUAL *parent_pop, INDIVIDUAL *mix_pop);
extern void MOEAD(MOEAD_entity algorithm_entity);
extern int select_worst(INDIVIDUAL *pop_select, int popsize, int *flag);
extern void fitness_change(INDIVIDUAL *pop_select, int index, double MAX, int popsize, int *flag);


#endif //UNTITLED_METAHEURITICS_H
