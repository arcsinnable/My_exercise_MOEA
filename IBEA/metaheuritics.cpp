//
// Created by sinnable on 6/20/20.
//

# include "metaheuritics.h"
# include "evaluation.h"
# include "print.h"
# include "crossover.h"
# include "mutation.h"
# include "dominance_relation.h"
# include "memory.h"

void mix_population(INDIVIDUAL *mix_pop, INDIVIDUAL *parent_pop, INDIVIDUAL *offspring_pop, int pop_size)
{
    for (int i = 0; i < pop_size; i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {
            mix_pop[i].variable[j] = parent_pop[i].variable[j];
        }
        for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
        {
            mix_pop[i].objective[j] = parent_pop[i].objective[j];
        }
        mix_pop[i].rank = parent_pop[i].rank;
        mix_pop[i].fitness = parent_pop[i].fitness;
    }
    for (int i = 0; i < pop_size; i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {
            mix_pop[i + pop_size].variable[j] = offspring_pop[i].variable[j];
        }
        for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
        {
            mix_pop[i + pop_size].objective[j] = offspring_pop[i].objective[j];
        }
        mix_pop[i + pop_size].rank = offspring_pop[i].rank;
        mix_pop[i + pop_size].fitness = offspring_pop[i].fitness;
    }
    return;
}

void copy_pop(INDIVIDUAL *mix_pop, INDIVIDUAL *pop_select)
{
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++) {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {
            pop_select[i].variable[j] = mix_pop[i].variable[j];
        }
        for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
        {
            pop_select[i].objective[j] = mix_pop[i].objective[j];
        }
    }
    return;
}
double fitness_evaluation(INDIVIDUAL *pop_select, int popsize)
{
    double temp = 0, count = 0;
    for(int i = 0; i < popsize;i++)
    {
        pop_select[i].fitness = 0;
        for(int j = 0;j < popsize;j++)
        {
            if(j == i)
                continue;
            if(temp < fabs(indicator(pop_select[j],pop_select[i])))
                temp = fabs(indicator(pop_select[j],pop_select[i]));
        }
    }
    for(int i = 0; i < popsize;i++)
    {
        for(int j = 0;j < popsize;j++)
        {
            if(j == i)
                continue;
            count = exp(-1 * indicator(pop_select[j],pop_select[i])/temp/algorithm_entity.fitness_scaling_factor);
            pop_select[i].fitness -= exp((-indicator(pop_select[j],pop_select[i])/temp)/algorithm_entity.fitness_scaling_factor);
        }
    }
    return temp;
}
int select_worst(INDIVIDUAL *pop_select, int popsize, int *flag)
{
    double worst_fitness = pop_select[0].fitness;
    int worst_index, i;
    for(i = 0;i < popsize && flag[i] == 1;i++);
    worst_index = i;
    for(i = i + 1;i < popsize;i++)
    {
        if(flag[i]==0)
        {
            if(pop_select[i].fitness < worst_fitness)
            {
                worst_index = i;
                worst_fitness = pop_select[i].fitness;
            }
        }
    }
    return worst_index;
}

void fitness_change(INDIVIDUAL *pop_select, int index, double MAX, int popsize, int *flag)
{
    for(int i = 0;i < popsize;i++)
    {
        if(flag[i]==0)
        {
            if(i != index)
                pop_select[i].fitness += exp(-1 * indicator(pop_select[index],pop_select[i])/MAX/algorithm_entity.fitness_scaling_factor);
        }
    }
    flag[index] = 1;
    return;
}


void select_population(INDIVIDUAL *parent_pop, INDIVIDUAL *mix_pop){
    int index_rank = 0, temp = 0, count = algorithm_entity.algorithmParameter.population_size;
    double MAX;
    int *flag;
    INDIVIDUAL *pop_select;
    pop_select = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size * 2);
    flag =(int *)malloc(sizeof(int) * algorithm_entity.algorithmParameter.population_size * 2);
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++)
    {
        flag[i] = 0;
    }
    allocate_memory_pop(pop_select,algorithm_entity.algorithmParameter.population_size * 2);
    //cout<<"begin"<<endl;
    //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++) {
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
    //            cout << mix_pop[i].variable[j] << ",";
    //        else
    //            cout << mix_pop[i].variable[j]<<",";
    //    }
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
    //            cout << mix_pop[i].objective[j] << ",";
    //        else
    //            cout << mix_pop[i].objective[j]<<","<<mix_pop[i].rank<<endl;
    //    }
    //}
    copy_pop(mix_pop, pop_select);
    MAX = fitness_evaluation(pop_select,algorithm_entity.algorithmParameter.population_size * 2);
    //cout<<"begin"<<endl;
    //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++) {
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
    //           cout << mix_pop[i].variable[j] << ",";
    //        else
    //           cout << mix_pop[i].variable[j]<<",";
    //    }
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
    //       if (j != algorithm_entity.algorithmParameter.objective_number - 1)
    //            cout << mix_pop[i].objective[j] << ",";
    //        else
    //            cout << mix_pop[i].objective[j]<<","<<mix_pop[i].rank<<endl;
    //    }
    //}
    while(count)
    {
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //            cout << mix_pop[i].variable[j] << ",";
        //        else
        //           cout << mix_pop[i].variable[j]<<",";
        //    }
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //       if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << pop_select[i].objective[j] << ",";
        //        else
        //            cout << pop_select[i].objective[j]<<", "<<pop_select[i].fitness<<endl;
        //    }
        //}
        temp = select_worst(pop_select,algorithm_entity.algorithmParameter.population_size * 2, flag);

        fitness_change(pop_select,temp, MAX, algorithm_entity.algorithmParameter.population_size * 2, flag);

        count--;

    }
    //cout<<"begin"<<endl;
    //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
    //           cout << entity.parent_pop[i].variable[j] << ",";
    //        else
    //            cout << entity.parent_pop[i].variable[j]<<",";
    //   }
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
    //            cout << pop_select[i].objective[j] << ",";
    //        else
    //            cout << pop_select[i].objective[j]<<","<<pop_select[i].fitness<<endl;
    //    }
    //}
    count = 0;
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        while(flag[count]==1)
            count++;
        for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number; j++) {
            parent_pop[i].variable[j] = pop_select[count].variable[j];
        }
        for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number; j++) {
            parent_pop[i].objective[j] = pop_select[count].objective[j];
        }
        count++;
    }
    free(flag);
    destroy_memory_pop(pop_select, algorithm_entity.algorithmParameter.population_size * 2);

    return;
}

void IBEA(IBEA_entity entity)
{

    entity.iteration_number = 0;
    evaluation(entity.parent_pop,entity.algorithmParameter.population_size);

    //cout<<"begin"<<endl;
    //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //           cout << entity.parent_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.parent_pop[i].variable[j]<<",";
        //   }
    //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
    //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
    //            cout << entity.parent_pop[i].objective[j] << ",";
    //        else
    //            cout << entity.parent_pop[i].objective[j]<<","<<entity.parent_pop[i].rank<<endl;
    //    }
    //}
    while(entity.iteration_number < entity.algorithmParameter.max_evaluation)
    {
        entity.iteration_number++;
        //print_progress(entity);
        crossover(entity.offspring_pop, entity.parent_pop);
        //evaluation(entity.offspring_pop, entity.algorithmParameter.population_size);
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //            cout << entity.offspring_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.offspring_pop[i].variable[j]<<",";
        //    }
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << entity.offspring_pop[i].objective[j] << ",";
        //        else
        //            cout << entity.offspring_pop[i].objective[j]<<","<<entity.offspring_pop[i].rank<<endl;
        //    }
        //}
        mutation(entity.offspring_pop, entity.algorithmParameter.population_size);

        evaluation(entity.offspring_pop, entity.algorithmParameter.population_size);
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //            cout << entity.offspring_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.offspring_pop[i].variable[j]<<",";
        //    }
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << entity.offspring_pop[i].objective[j] << ",";
        //        else
        //           cout << entity.offspring_pop[i].objective[j]<<","<<entity.offspring_pop[i].rank<<endl;
        //    }
        //}

        mix_population(entity.mix_pop, entity.parent_pop, entity.offspring_pop, entity.algorithmParameter.population_size);
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //            cout << entity.offspring_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.offspring_pop[i].variable[j]<<",";
        //    }
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << entity.mix_pop[i].objective[j] << ",";
        //        else
        //            cout << entity.mix_pop[i].objective[j]<<endl;
        //    }
        //}
        select_population(entity.parent_pop,entity.mix_pop);
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //           cout << entity.parent_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.parent_pop[i].variable[j]<<",";
        //   }
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << entity.parent_pop[i].objective[j] << ",";
        //        else
        //            cout << entity.parent_pop[i].objective[j]<<","<<entity.parent_pop[i].fitness<<endl;
        //    }
        //}
        //cout<<"begin"<<endl;



    }
    return;
}