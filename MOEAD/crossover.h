//
// Created by sinnable on 6/20/20.
//

#ifndef UNTITLED_CROSSOVER_H
#define UNTITLED_CROSSOVER_H
#include "global.h"

extern INDIVIDUAL* tournament_by_rank(INDIVIDUAL *pop1, INDIVIDUAL *pop2);
INDIVIDUAL* inverse_tournament_by_rank(INDIVIDUAL *pop1, INDIVIDUAL *pop2);
extern void crossover(INDIVIDUAL *offspring_pop, INDIVIDUAL *parent_pop);
extern void sbx_crossover(INDIVIDUAL *parent1, INDIVIDUAL *parent2, INDIVIDUAL *offspring1,INDIVIDUAL *offspring2);
extern void crossover_MOEAD(INDIVIDUAL *parent_pop_table, int parent_index, INDIVIDUAL *offspring, NeighborType type);
extern void de_crossover (INDIVIDUAL *parent1, INDIVIDUAL *parent2, INDIVIDUAL *parent3, INDIVIDUAL *offspring);

#endif //UNTITLED_CROSSOVER_H
