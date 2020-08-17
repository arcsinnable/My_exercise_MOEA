//
// Created by sinnable on 6/19/20.
//
#include "global.h"
#include "initialize.h"
#include "memory.h"
#include "population.h"


extern int set_bound()
{
    if(ZDT4 == algorithm_entity.test_problem)
    {
        algorithm_entity.variable_lower_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        algorithm_entity.variable_higher_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);

        algorithm_entity.variable_lower_bound[0] = 0.0;
        algorithm_entity.variable_higher_bound[0] = 1.0;
        for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
        {
            algorithm_entity.variable_lower_bound[i] = -5.0;
            algorithm_entity.variable_higher_bound[i] = 5.0;
        }
    }
    else if(SCH == algorithm_entity.test_problem)
    {
        algorithm_entity.variable_lower_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        algorithm_entity.variable_higher_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);

        algorithm_entity.variable_lower_bound[0] = -10.0;
        algorithm_entity.variable_higher_bound[0] = 10.0;
    }
    else if(KUR == algorithm_entity.test_problem)
    {
        algorithm_entity.variable_lower_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        algorithm_entity.variable_higher_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        for(int i = 0;i < 3;i++)
        {
            algorithm_entity.variable_lower_bound[i] = -5.0;
            algorithm_entity.variable_higher_bound[i] = 5.0;
        }
    }
    else{
        algorithm_entity.variable_lower_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
        algorithm_entity.variable_higher_bound = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);

        for(int i = 0;i < algorithm_entity.algorithmParameter.variable_number;i++)
        {
            algorithm_entity.variable_lower_bound[i] = 0.0;
            algorithm_entity.variable_higher_bound[i] = 1.0;
        }
    }
    if(NULL == algorithm_entity.variable_lower_bound||NULL == algorithm_entity.variable_lower_bound) return FAIL;
    return SUCCESS;
}

extern int initialize_real_code()
{
    algorithm_entity.algorithmParameter.variable_number = 3;
    algorithm_entity.algorithmParameter.objective_number = 2;
    algorithm_entity.algorithmParameter.max_evaluation = 2000;
    algorithm_entity.algorithmParameter.population_size = 100;
    algorithm_entity.test_problem = KUR;
    algorithm_entity.algorithmParameter.output_interval = 1000;
    algorithm_entity.run_index_begin = 0;
    algorithm_entity.run_index_end = 9;
    algorithm_entity.sbx_parameter.eta_crossover = 20;
    algorithm_entity.sbx_parameter.p_crossover = 0.9;
    algorithm_entity.polynomial_parameter.eta_mutation = 20;
    algorithm_entity.polynomial_parameter.p_mutation = 1.0 / (double)algorithm_entity.algorithmParameter.variable_number;
    algorithm_entity.parent_pop = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size);
    algorithm_entity.offspring_pop = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size);
    algorithm_entity.mix_pop = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size * 2);
    algorithm_entity.elt_pop = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size);
    free(algorithm_entity.variable_higher_bound);
    free(algorithm_entity.variable_lower_bound);
    allocate_memory_pop(algorithm_entity.parent_pop,algorithm_entity.algorithmParameter.population_size);
    allocate_memory_pop(algorithm_entity.offspring_pop,algorithm_entity.algorithmParameter.population_size);
    allocate_memory_pop(algorithm_entity.mix_pop,algorithm_entity.algorithmParameter.population_size * 2);
    allocate_memory_pop(algorithm_entity.elt_pop,algorithm_entity.algorithmParameter.population_size);
    set_bound();
    initialize_pop_real(algorithm_entity.parent_pop, algorithm_entity.algorithmParameter.population_size);


    if(FAIL == set_bound())return FAIL;
    return SUCCESS;
}