#include "global.h"
#include "initialize.h"
#include "metaheuritics.h"
#include "memory.h"
#include "diversity_metric.h"
#include "test_problem.h"
//configuration
//algorithm_name:NSGA2
//test_problem:DTLZ1
//problem_param:
//number_variable:10
//number_objective:3
//popSize:300
//eliteSize:300
//max_evaluation:120000
//runtime_output:1
//output_interval:1000
//run_index_begin:1
//run_index_end:1
//analyse:FUN


int main()
{

    for(algorithm_entity.run_index_current = algorithm_entity.run_index_begin;algorithm_entity.run_index_current <= algorithm_entity.run_index_end;algorithm_entity.run_index_current++) {
        initialize_real_code();
        cout<<algorithm_entity.algorithmParameter.variable_number<<endl;
        cout<<algorithm_entity.algorithmParameter.objective_number<<endl;
        cout<<algorithm_entity.algorithmParameter.max_evaluation<<endl;
        cout<<algorithm_entity.algorithmParameter.population_size<<endl;
        cout<<algorithm_entity.test_problem<<endl;
        cout<<algorithm_entity.algorithmParameter.output_interval<<endl;
        cout<<algorithm_entity.run_index_begin<<endl;
        cout<<algorithm_entity.run_index_end<<endl;
        cout<<algorithm_entity.sbx_parameter.eta_crossover<<endl;
        cout<<algorithm_entity.sbx_parameter.p_crossover<<endl;
        cout<<algorithm_entity.polynomial_parameter.eta_mutation<<endl;

        IBEA(algorithm_entity);
        cout << "the "<<algorithm_entity.run_index_current <<" output is as follows" << endl;
        for (int i = 0; i < algorithm_entity.algorithmParameter.population_size; i++) {
            for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number; j++) {
                if (j != algorithm_entity.algorithmParameter.objective_number - 1)
                    cout << algorithm_entity.parent_pop[i].objective[j] << ", ";
                else
                    cout << algorithm_entity.parent_pop[i].objective[j] << endl;
            }

        }

        destroy_memory_pop(algorithm_entity.parent_pop, algorithm_entity.algorithmParameter.population_size);
        destroy_memory_pop(algorithm_entity.offspring_pop, algorithm_entity.algorithmParameter.population_size);
        destroy_memory_pop(algorithm_entity.mix_pop, algorithm_entity.algorithmParameter.population_size * 2);
        destroy_memory_pop(algorithm_entity.elt_pop, algorithm_entity.algorithmParameter.population_size);
    }
    free(algorithm_entity.variable_lower_bound);
    free(algorithm_entity.variable_higher_bound);
    return 0;
}
