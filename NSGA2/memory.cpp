//
// Created by sinnable on 6/19/20.
//

#include "memory.h"

extern int allocate_memory_pop(INDIVIDUAL *pop, int pop_size)
{


    for(int i = 0; i < pop_size; i++)
    {
        pop[i].variable = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        if(NULL == pop[i].variable)return FAIL;


        pop[i].objective = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.objective_number);
        if(NULL == pop[i].objective)return FAIL;
    }
    return SUCCESS;
}
extern int destroy_memory_pop(INDIVIDUAL *pop, int pop_size)
{
    for(int i = 0;i < pop_size;i++)
    {
        if(NULL != pop[i].variable)
        {
            free(pop[i].variable);
            pop[i].variable = NULL;

        }
        if(NULL != pop[i].objective)
        {
            free(pop[i].objective);
            pop[i].objective = NULL;
        }
    }
    free(pop);
    pop = NULL;
    return SUCCESS;
}
