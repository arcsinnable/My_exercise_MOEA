//
// Created by sinnable on 6/20/20.
//

#include "crossover.h"

INDIVIDUAL* tournament_by_rank(INDIVIDUAL *pop1, INDIVIDUAL *pop2)
{
    if(pop1->rank < pop2->rank)
        return pop1;
    if(pop1->rank > pop2->rank)
        return pop2;

    if((double)random()/(double)RAND_MAX <0.5)return pop1;
    else return pop2;
}

INDIVIDUAL* inverse_tournament_by_rank(INDIVIDUAL *pop1, INDIVIDUAL *pop2)
{
    if(pop1->rank > pop2->rank)
        return pop1;
    if(pop1->rank < pop2->rank)
        return pop2;

    if((double)random()/(double)RAND_MAX <0.5)return pop1;
    else return pop2;
}

void sbx_crossover(INDIVIDUAL *parent1, INDIVIDUAL *parent2, INDIVIDUAL *offspring1,INDIVIDUAL *offspring2)
{
    int i;
    double rand = 0;
    double y1 = 0, y2 = 0, yl = 0, yu = 0;
    double c1 = 0, c2 = 0;
    double beta, alpha, betaq;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<>  dis(0.0,1.0);

    if ((double)random()/(double)RAND_MAX <= algorithm_entity.sbx_parameter.p_crossover)
    {

        for (i = 0; i < algorithm_entity.algorithmParameter.variable_number; i++)
        {
            if (fabs (parent1->variable[i]-parent2->variable[i]) > pow(10,-9))
            {
                if (parent1->variable[i] < parent2->variable[i])
                {
                    y1 = parent1->variable[i];
                    y2 = parent2->variable[i];
                }
                else{
                    y1 = parent2->variable[i];
                    y2 = parent1->variable[i];
                }
                yl    = algorithm_entity.variable_lower_bound[i];
                yu    = algorithm_entity.variable_higher_bound[i];
                rand  = dis(gen);
                beta  = 1.0 + (2.0 * (y1 - yl) / (y2 - y1));
                alpha = 2.0 - pow (beta, -(algorithm_entity.sbx_parameter.eta_crossover + 1.0));
                if (rand <= (1.0/alpha))
                {
                    betaq = pow ((rand * alpha), (1.0 / (algorithm_entity.sbx_parameter.eta_crossover + 1.0)));
                }
                else
                {
                    betaq = pow ((1.0 / (2.0 - rand * alpha)), (1.0 / (algorithm_entity.sbx_parameter.eta_crossover + 1.0)));
                }
                c1    = 0.5 * ((y1 + y2) - betaq * (y2 - y1));
                beta  = 1.0 + (2.0 * (yu - y2) / (y2 - y1));
                alpha = 2.0 - pow (beta, -(algorithm_entity.sbx_parameter.eta_crossover + 1.0));
                if (rand <= (1.0/alpha))
                {
                    betaq = pow ((rand * alpha), (1.0 / (algorithm_entity.sbx_parameter.eta_crossover + 1.0)));
                }
                else
                {
                   betaq = pow ((1.0 / (2.0 - rand * alpha)), (1.0 / (algorithm_entity.sbx_parameter.eta_crossover + 1.0)));
                }
                c2 = 0.5 * ((y1 + y2) + betaq * (y2 - y1));
                if (c1 < yl)
                    c1 = yl;
                if (c2 < yl)
                    c2 = yl;
                if (c1 > yu)
                    c1 = yu;
                if (c2 > yu)
                    c2 = yu;
                if ((double)random()/(double)RAND_MAX <= 0.5)
                {
                    offspring1->variable[i] = c2;
                    offspring2->variable[i] = c1;
                }
                else{
                    offspring1->variable[i] = c1;
                    offspring2->variable[i] = c2;
                }
            }
            else{
                    offspring1->variable[i] = parent1->variable[i];
                    offspring2->variable[i] = parent2->variable[i];
                }
            }
        }
    else
    {
        for (i = 0; i < algorithm_entity.algorithmParameter.variable_number; i++)
        {
            offspring1->variable[i] = parent1->variable[i];
            offspring2->variable[i] = parent2->variable[i];
        }
    }

    return;
}

void crossover(INDIVIDUAL *offspring_pop, INDIVIDUAL *parent_pop)
{
    int i, temp, rand;
    int *a1, *a2;
    INDIVIDUAL *parent1, *parent2;
    a1 = (int *) malloc (algorithm_entity.algorithmParameter.population_size * sizeof(int));
    a2 = (int *) malloc (algorithm_entity.algorithmParameter.population_size * sizeof(int));
    for (i = 0; i < algorithm_entity.algorithmParameter.population_size; i++)
        a1[i] = a2[i] = i;

    for (i = 0; i < algorithm_entity.algorithmParameter.population_size; i++)
    {
        rand     = i + random() % (algorithm_entity.algorithmParameter.population_size-i);
        temp     = a1[rand];
        a1[rand] = a1[i];
        a1[i]    = temp;
        rand     = i + random() % (algorithm_entity.algorithmParameter.population_size-i);
        temp     = a2[rand];
        a2[rand] = a2[i];
        a2[i]    = temp;
    }
    //for(i = 0;i<algorithm_entity.algorithmParameter.population_size;i++)
    //{
    //    cout<<a1[i]<<",";
    //}
    for (i = 0; i < algorithm_entity.algorithmParameter.population_size ; i += 4)
    {
        parent1 = tournament_by_rank(&parent_pop[a1[i]], &parent_pop[a1[i + 1]]);
        parent2 = tournament_by_rank(&parent_pop[a1[i + 2]], &parent_pop[a1[i + 3]]);
        sbx_crossover (parent1, parent2, offspring_pop + i, offspring_pop + i + 1);
        parent1 = tournament_by_rank(&parent_pop[a2[i]], &parent_pop[a2[i + 1]]);
        parent2 = tournament_by_rank(&parent_pop[a2[i + 2]], &parent_pop[a2[i + 3]]);
        sbx_crossover (parent1, parent2,offspring_pop + i + 2, offspring_pop + i + 3);

    }

    free(a1);
    free(a2);
    return;
}

void crossover_MOEAD(INDIVIDUAL *parent_pop, int parent_index, INDIVIDUAL *offspring_pop, NeighborType type)
{
    int i = 0;
    int rand = 0;
    int selected_id, *selected_flag = NULL;
    int parent_id[2] = {0}, choose_num = 0;
    INDIVIDUAL *parent = parent_pop + parent_index;
    INDIVIDUAL *offspring = offspring_pop + parent_index;



    selected_flag = (int *)malloc(algorithm_entity.algorithmParameter.population_size * sizeof(int));
    memset(selected_flag, 0, sizeof(int) * algorithm_entity.algorithmParameter.population_size);

    while(choose_num < 2)
    {
        if (NEIGHBOR == type)
        {
            rand = random()%algorithm_entity.algorithmParameter.neighbor_size;
            selected_id = algorithm_entity.algorithmParameter.neighbor_table[parent_index].neighbor[rand];
        }
        else
        {
            rand = random()%weight_num;
            selected_id = rand;
        }

        if (selected_flag[selected_id] == 0)
        {
            selected_flag[selected_id] = 1;
            parent_id[choose_num++] = selected_id;
        }
    }

    de_crossover(parent, parent_pop + parent_id[0],
                 parent_pop + parent_id[1], offspring);

    free(selected_flag);
    return;
}

void de_crossover (INDIVIDUAL *parent1, INDIVIDUAL *parent2, INDIVIDUAL *parent3, INDIVIDUAL *offspring)
{
    int i, r;
    double value, yl, yu;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);

    r = random() % algorithm_entity.algorithmParameter.variable_number;
    for (i = 0 ; i < algorithm_entity.algorithmParameter.variable_number;i ++)
    {
        yl = algorithm_entity.variable_lower_bound[i];
        yu = algorithm_entity.variable_higher_bound[i];
        if (dis(gen) < algorithm_entity.dePara.CR || i == r)
        {
            value = parent3->variable[i] + algorithm_entity.dePara.F * (parent1-> variable[i] - parent2->variable[i]);
            value = (value > yu) ? yu : (value < yl) ? yl : value;
        }
        else
        {
            value = parent3->variable[i];
        }
        offspring->variable[i] = value;
    }

    return;
}
