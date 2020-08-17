//
// Created by sinnable on 6/20/20.
//

# include "metaheuritics.h"
# include "initialize.h"
# include "population.h"
# include "evaluation.h"
# include "print.h"
# include "crossover.h"
# include "mutation.h"
# include "dominance_relation.h"
# include "memory.h"
# include "utility.h"

static int partition_by_distance(Distance_info *distanceInfo, int left, int right)
{
    double temp_fit = distanceInfo[left].value;
    int temp_index = distanceInfo[left].idx;
    while(left < right)
    {
        while ((left < right) && (distanceInfo[right].value >= temp_fit))right--;
        if (left < right)
        {
            distanceInfo[left].idx = distanceInfo[right].idx;
            distanceInfo[left].value = distanceInfo[right].value;
            left++;
        }
        while ((left < right) && (distanceInfo[left].value < temp_fit))left++;
        if (left < right)
        {
            distanceInfo[right].idx = distanceInfo[left].idx;
            distanceInfo[right].value = distanceInfo[left].value;
            right--;
        }
    }
    distanceInfo[left].value = temp_fit;
    distanceInfo[left].idx = temp_index;
    return left;
}

static void distance_quick_sort(Distance_info *distanceInfo, int left, int right)
{
    int pos = 0;

    if (left < right)
    {
        pos = partition_by_distance(distanceInfo, left, right);
        distance_quick_sort(distanceInfo, pos + 1, right);
        distance_quick_sort(distanceInfo, left, pos - 1);
    }
    return;
}

static void MOEAD_initial()
{
    int i = 0, j = 0, k = 0;
    double difference = 0, distance_temp = 0, Euc_distance = 0;
    Distance_info sort_list[MAX_SIZE];


    lambda = initialize_uniform_point (algorithm_entity.algorithmParameter.population_size, &weight_num);

    algorithm_entity.algorithmParameter.neighbor_table = (MOEAD_NEIGHBOR*)malloc(sizeof(MOEAD_NEIGHBOR) * weight_num);
    if(NULL == algorithm_entity.algorithmParameter.neighbor_table)
    {
        printf("In the state of initiate parameter malloc G_MOEAD_weighted Fail\n");
        return;
    }

    for (i = 0; i < weight_num; i++)
    {
        for (j = 0; j < weight_num; j++)
        {
            distance_temp = 0;
            for (k = 0; k < algorithm_entity.algorithmParameter.objective_number; k++)
            {
                difference = fabs(lambda[i][k] -  lambda[j][k]);
                distance_temp += (double)pow(difference,2);
            }

            Euc_distance = sqrt((double)distance_temp);
            sort_list[j].value = Euc_distance;
            sort_list[j].idx = j;
        }

        distance_quick_sort(sort_list, 0, weight_num - 1);

        algorithm_entity.algorithmParameter.neighbor_table[i].neighbor = (int *)malloc(sizeof(int) * algorithm_entity.algorithmParameter.neighbor_size);
        if(NULL == algorithm_entity.algorithmParameter.neighbor_table[i].neighbor)
        {
            printf("In the state of initiate parameter malloc weight neighbor Fail\n");
            return ;
        }

        for (j = 0; j < algorithm_entity.algorithmParameter.neighbor_size; j++)
        {
            algorithm_entity.algorithmParameter.neighbor_table[i].neighbor[j] = sort_list[j].idx;
        }
    }
    return;
}

static void initialize_idealpoint(INDIVIDUAL *pop_table, int pop_num, REFERENCE_POINT *ideal_point)
{
    int i = 0, j = 0;
    INDIVIDUAL *ind = NULL;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        ideal_point->objective[i] = INFINITY;
    for (i = 0 ;i < pop_num; i++)
    {
        ind = pop_table + i;
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number; j++)
        {
            if (ind->objective[j] < ideal_point->objective[j])
                ideal_point->objective[j] = ind->objective[j];
        }
    }
    return;
}

void MOEAD(MOEAD_entity entity)
{
    NeighborType type;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    initialize_real_code();
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {
            algorithm_entity.parent_pop[i].variable[j] = 0;
        }
    }
    MOEAD_initial();
    cout<<"shit"<<endl;
    initialize_pop_real(algorithm_entity.parent_pop, weight_num);
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
    entity.iteration_number = 0;
    evaluation(entity.parent_pop,entity.algorithmParameter.population_size);
    initialize_idealpoint (algorithm_entity.parent_pop, weight_num, &algorithm_entity.ideal_point);

    for (int i = 0; i < weight_num; i++)
    {
        cal_moead_fitness(algorithm_entity.parent_pop + i, lambda[i], algorithm_entity.algorithmParameter.function_type);
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
    //            cout << entity.parent_pop[i].objective[j] << ",";
    //        else
    //            cout << entity.parent_pop[i].objective[j]<<","<<entity.parent_pop[i].rank<<endl;
    //    }
    //}
    while(entity.iteration_number < entity.algorithmParameter.max_evaluation) {
        entity.iteration_number++;
        for (int i = 0; i < weight_num; i++) {
            if (dis(gen) < algorithm_entity.algorithmParameter.neighborhood_selection_probability) {
                type = NEIGHBOR;
            } else {
                type = GLOBAL_PARENT;
            }

            crossover_MOEAD(algorithm_entity.parent_pop, i, algorithm_entity.offspring_pop, type);
            mutation_individual(algorithm_entity.offspring_pop, i);
            evaluation_individual(algorithm_entity.offspring_pop, i);

            // update ideal point
            update_ideal_point_by_ind(algorithm_entity.offspring_pop, i);

            // update subproblem
            update_subproblem(algorithm_entity.offspring_pop, i, type);



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
    }

    for (int i = 0; i < weight_num; i++)
        free (lambda[i]);
    free (lambda);
    return;
}