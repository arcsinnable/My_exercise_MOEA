//
// Created by sinnable on 6/19/20.
//

#include "population.h"

void initialize_pop_real(INDIVIDUAL *pop, int popsize)
{
    double rand;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(algorithm_entity.variable_lower_bound[0],algorithm_entity.variable_higher_bound[0]);

    for(int i = 0;i < popsize;i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {

            rand = dis(gen);
            pop[i].variable[j] = rand;
        }
        pop[i].rank = 0;
    }
    return;
}