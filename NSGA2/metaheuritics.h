//
// Created by sinnable on 6/20/20.
//

#ifndef UNTITLED_METAHEURITICS_H
#define UNTITLED_METAHEURITICS_H
#include "global.h"
#include "metaheuritics.h"

extern void mix_population(INDIVIDUAL *mix_pop, INDIVIDUAL *parent_pop, INDIVIDUAL *offspring_pop, int pop_size);
extern void non_dominated_sort(INDIVIDUAL *pop, int pop_size);
extern void crowd_distance_assign(INDIVIDUAL *mix_pop, int index_rank, INDIVIDUAL *pop_sort);
extern void select_population(INDIVIDUAL *parent_pop, INDIVIDUAL *mix_pop);
extern void NSGA2(NSGA2_entity algorithm_entity);


#endif //UNTITLED_METAHEURITICS_H
