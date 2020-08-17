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


void non_dominated_sort(INDIVIDUAL *pop, int pop_size)
{
    int i = 0; int j = 0, k = 0;
    int index = 0; /*临时索引号*/
    int current_rank = 0, unrank_num = pop_size; /*rank用于等级赋值，unrank_num用于判断是否停止循环*/
    int dominate_relation = 0;
    int *ni = NULL, **si = NULL, *Q = NULL;/*ni用于表示支配第i个solution的解的个数，si是一个集合，存放第i个元素支配的解,Q集合用于存放当前ni为0的solution*/
    int *dominate_num = NULL;   /*用于存储I支配的解的个数*/
    INDIVIDUAL *ind_tempA = NULL, *ind_tempB = NULL, temp;
    ni = (int *)malloc(sizeof(int) * pop_size);
    temp.variable = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
    temp.objective = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.objective_number);

    if (NULL == ni)
    {
        printf("in the non_dominated_sort, malloc ni Failed\n");
        goto FINISH;
    }
    memset(ni, 0, sizeof(int) * pop_size);

    si = (int **)malloc(sizeof(int *) * pop_size);
    if (NULL == si)
    {
        printf("in the non_dominated_sort, malloc si Failed\n");
        goto FINISH;
    }
    for (i = 0; i < pop_size; i++)
    {
        si[i] = (int *)malloc(sizeof(int) * pop_size);
        if (NULL == si[i])
        {
            printf("in the non_dominated_sort, malloc si Failed\n");
            goto FINISH;
        }
        memset(si[i], 0, sizeof(int) * pop_size);
    }

    Q = (int *)malloc(sizeof(int) * pop_size);
    if (NULL == Q)
    {
        printf("in the non_dominated_sort, malloc Q Failed\n");
        goto FINISH;
    }
    memset(Q, 0, sizeof(int) * pop_size);

    dominate_num = (int*)malloc(sizeof(int) * pop_size);
    if (NULL == dominate_num)
    {
        printf("in the non_dominated_sort, malloc dominate_numb Failed\n");
        goto FINISH;
    }
    memset(dominate_num, 0, sizeof(int) * pop_size);

    for (i = 0; i < pop_size; i++)
    {
        ind_tempA = pop + i;
        index = 0;
        for (j = 0; j < pop_size; j++)
        {
            if (i == j)
                continue;

            ind_tempB = pop + j;
            dominate_relation = check_dominance(ind_tempA, ind_tempB);
            if (DOMINATE == dominate_relation)
            {
                /*I支配J*/
                si[i][index++] = j;

            }
            else if(DOMINATED == dominate_relation)/*J支配I*/
            {

                ni[i]++;
            }
            else;
        }
        dominate_num[i] = index;
    }

    while(unrank_num)
    {
        index = 0;
        for (i = 0; i < pop_size; i++)
        {
            if (ni[i] == 0)
            {


                pop[i].rank = current_rank;
                Q[index++] = i;
                unrank_num--;
                ni[i] = -1;
            }
        }
        current_rank++;
        for (i = 0; i < index; i++)
        {
            for(j = 0; j < dominate_num[Q[i]]; j++)
            {
                ni[si[Q[i]][j]]--;
            }
        }
    }
    for(i = 0;i < pop_size - 1;i++)
    {
        for(j = i;j <pop_size;j++)
        {
            if(pop[i].rank > pop[j].rank)
            {
                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    temp.variable[n] = pop[i].variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    temp.objective[n] = pop[i].objective[n];
                }
                temp.rank = pop[i].rank;
                temp.fitness = pop[i].fitness;

                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    pop[i].variable[n] = pop[j].variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    pop[i].objective[n] = pop[j].objective[n];
                }
                pop[i].rank = pop[j].rank;
                pop[i].fitness = pop[j].fitness;


                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    pop[j].variable[n] = temp.variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    pop[j].objective[n] = temp.objective[n];
                }
                pop[j].rank = temp.rank;
                pop[j].fitness = temp.fitness;
            }
        }
    }
//    for(i = 0;i < g_algorithm_entity.algorithm_para.pop_size;i++)
//            printf("\n %d",pop_table[i].rank);

    FINISH:
    free(temp.variable);
    free(temp.objective);
    free(ni);
    for (i = 0; i < pop_size; i++)
    {
        free(si[i]);
    }
    free(si);
    free(Q);
    free(dominate_num);
    return;
}

void crowd_distance_assign(INDIVIDUAL *mix_pop, int index_rank, INDIVIDUAL *pop_sort)
{
    INDIVIDUAL temp;
    int current_pop_number = 0;
    int a = 0;
    int *sort;
    double *f_max,*f_min;
    f_max = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.objective_number);
    f_min = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.objective_number);
    sort = (int *)malloc(sizeof(int) * algorithm_entity.algorithmParameter.objective_number * algorithm_entity.algorithmParameter.population_size * 2);

    temp.variable = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
    temp.objective = (double *)malloc(sizeof(double) * algorithm_entity.algorithmParameter.objective_number);


    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size * 2;i++)
    {
        if(mix_pop[i].rank == index_rank)
        {
            for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
            {
                pop_sort[current_pop_number].variable[j] = mix_pop[i].variable[j];
            }
            for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
            {
                pop_sort[current_pop_number].objective[j] = mix_pop[i].objective[j];
            }
            pop_sort[current_pop_number].rank = mix_pop[i].rank;
            pop_sort[current_pop_number].fitness = mix_pop[i].fitness;
            current_pop_number++;
        }
    }

    for(int i = 0;i < current_pop_number;i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
        {
            sort[j * algorithm_entity.algorithmParameter.population_size * 2 + i] = i;
        }
        pop_sort[i].crowding_distance = 0;
    }


    for(int i = 0;i < current_pop_number - 1;i++)
    {
        for(int j = i + 1;j < current_pop_number;j++)
        {
            for(int k = 0;k < algorithm_entity.algorithmParameter.objective_number;k++)
            {
                if(pop_sort[sort[k * algorithm_entity.algorithmParameter.population_size * 2 + i]].objective[k] < pop_sort[sort[k * algorithm_entity.algorithmParameter.population_size * 2 + j]].objective[k]){
                    a = sort[k * algorithm_entity.algorithmParameter.population_size * 2 + j];
                    sort[k * algorithm_entity.algorithmParameter.population_size * 2 + i] = sort[k * algorithm_entity.algorithmParameter.population_size * 2 + j];
                    sort[k * algorithm_entity.algorithmParameter.population_size * 2 + j] = a;
                }
            }
        }
    }

    for(int i = 0;i < algorithm_entity.algorithmParameter.objective_number;i++)
    {
        pop_sort[sort[i * algorithm_entity.algorithmParameter.population_size * 2]].crowding_distance += INFINITY;
        pop_sort[sort[i * algorithm_entity.algorithmParameter.population_size * 2 + current_pop_number - 1]].crowding_distance += INFINITY;
        f_max[i] = pop_sort[sort[i * algorithm_entity.algorithmParameter.population_size * 2]].objective[i];
        f_min[i] = pop_sort[sort[i * algorithm_entity.algorithmParameter.population_size * 2 + current_pop_number - 1]].objective[i];
    }

    for(int i = 1;i < current_pop_number - 1;i++)
    {
        for(int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++)
        {
            pop_sort[sort[j * algorithm_entity.algorithmParameter.population_size * 2 + i]].crowding_distance += (pop_sort[sort[j * algorithm_entity.algorithmParameter.population_size * 2 + i] - 1].objective[j] - pop_sort[sort[j * algorithm_entity.algorithmParameter.population_size * 2 + i + 1]].objective[j]) / (f_max[j] - f_min[j]);
        }
    }


    for(int i = 0;i < current_pop_number - 1;i++)
    {
        for(int j = i + 1;j < current_pop_number;j++)
        {
            if(pop_sort[i].crowding_distance < pop_sort[j].crowding_distance)
            {
                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    temp.variable[n] = pop_sort[i].variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    temp.objective[n] = pop_sort[i].objective[n];
                }
                temp.rank = pop_sort[i].rank;
                temp.fitness = pop_sort[i].fitness;
                temp.crowding_distance = pop_sort[i].crowding_distance;

                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    pop_sort[i].variable[n] = pop_sort[j].variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    pop_sort[i].objective[n] = pop_sort[j].objective[n];
                }
                pop_sort[i].rank = pop_sort[j].rank;
                pop_sort[i].fitness = pop_sort[j].fitness;
                pop_sort[i].crowding_distance = pop_sort[j].crowding_distance;


                for(int n = 0;n < algorithm_entity.algorithmParameter.variable_number;n++)
                {
                    pop_sort[j].variable[n] = temp.variable[n];
                }
                for(int n = 0;n < algorithm_entity.algorithmParameter.objective_number;n++)
                {
                    pop_sort[j].objective[n] = temp.objective[n];
                }
                pop_sort[j].rank = temp.rank;
                pop_sort[j].fitness = temp.fitness;
                pop_sort[j].crowding_distance = temp.crowding_distance;
            }
        }
    }
    free(temp.variable);
    free(temp.objective);
    free(f_max);
    free(f_min);
    free(sort);
    return;
}


void select_population(INDIVIDUAL *parent_pop, INDIVIDUAL *mix_pop){
    int index_rank = 0, temp, parent_pop_current_number = 0;
    INDIVIDUAL *pop_sort;
    pop_sort = (INDIVIDUAL *)malloc(sizeof(INDIVIDUAL) * algorithm_entity.algorithmParameter.population_size * 2);
    allocate_memory_pop(pop_sort,algorithm_entity.algorithmParameter.population_size * 2);
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
    non_dominated_sort(mix_pop, 2 * algorithm_entity.algorithmParameter.population_size);
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
    //            cout << mix_pop[i].objective[j] << ",";
    //        else
    //            cout << mix_pop[i].objective[j]<<","<<mix_pop[i].rank<<endl;
    //    }
    //}
    while(1)
    {
        temp = 0;
        for(int i = 0;i < 2 * algorithm_entity.algorithmParameter.population_size;i++)
        {
            if(mix_pop[i].rank == index_rank)
            {
                temp++;
            }
        }
        if(parent_pop_current_number + temp <= algorithm_entity.algorithmParameter.population_size&&temp > 0)
        {
            for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++)
            {
                if(mix_pop[i].rank == index_rank)
                {
                    for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
                    {
                        parent_pop[parent_pop_current_number].variable[j] = mix_pop[i].variable[j];
                    }
                    for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
                    {
                        parent_pop[parent_pop_current_number].objective[j] = mix_pop[i].objective[j];
                    }
                    parent_pop[parent_pop_current_number].rank = mix_pop[i].rank;
                    parent_pop[parent_pop_current_number].fitness = mix_pop[i].fitness;
                    parent_pop_current_number++;
                }

            }
            index_rank++;
        }
        else
            break;
    }
    if(parent_pop_current_number == algorithm_entity.algorithmParameter.population_size) return;
    else
    {
        temp = algorithm_entity.algorithmParameter.population_size - parent_pop_current_number;
        crowd_distance_assign(mix_pop, index_rank, pop_sort);
        for(int i = 0;i < temp;i++)
        {
            for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
            {
                parent_pop[parent_pop_current_number].variable[j] = pop_sort[i].variable[j];
            }
            for(int j = 0;j < algorithm_entity.algorithmParameter.objective_number;j++)
            {
                parent_pop[parent_pop_current_number].objective[j] = pop_sort[i].objective[j];
            }
            parent_pop[parent_pop_current_number].rank = pop_sort[i].rank;
            parent_pop[parent_pop_current_number].fitness = pop_sort[i].fitness;
            parent_pop_current_number++;
        }
    }
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++)
    {
        parent_pop[i].fitness = 0;
    }
    destroy_memory_pop(pop_sort, algorithm_entity.algorithmParameter.population_size * 2);
    return;
}

void NSGA2(NSGA2_entity entity)
{

    entity.iteration_number = 0;
    evaluation(entity.parent_pop,entity.algorithmParameter.population_size);

    //cout<<"begin"<<endl;
    //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
    //        for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
    //            if (j != algorithm_entity.algorithmParameter.variable_number - 1)
    //               cout << entity.parent_pop[i].variable[j] << ",";
    //            else
    //                cout << entity.parent_pop[i].variable[j]<<",";
    //       }
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
        //           cout << entity.offspring_pop[i].objective[j]<<","<<entity.offspring_pop[i].rank<<endl;
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
        select_population(entity.parent_pop,entity.mix_pop);
        //cout<<"begin"<<endl;
        //for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++) {
        //    for (int j = 0; j < algorithm_entity.algorithmParameter.variable_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.variable_number - 1)
        //           cout << entity.parent_pop[i].variable[j] << ",";
        //        else
        //            cout << entity.parent_pop[i].variable[j]<<",";
        //   }
        //   for (int j = 0; j < algorithm_entity.algorithmParameter.objective_number;j++) {
        //        if (j != algorithm_entity.algorithmParameter.objective_number - 1)
        //            cout << entity.parent_pop[i].objective[j] << ",";
        //        else
        //            cout << entity.parent_pop[i].objective[j]<<","<<entity.parent_pop[i].rank<<endl;
        //    }
        //}
        //cout<<"begin"<<endl;



    }
    return;
}