//
// Created by sinnable on 6/20/20.
//

#include "evaluation.h"
#include "test_problem.h"

void evaluation(INDIVIDUAL *pop, int pop_size)
{
    for(int i = 0; i < pop_size; i++)
    {
        evaluation_individual(pop,i);
    }
}
double cal_weighted_sum(INDIVIDUAL *pop, double *weight_vector, int obj_num)
{
    int  i = 0;
    double fitness = 0;
    for (i = 0; i < obj_num; i++)
    {
        fitness += pop->objective[i] * weight_vector[i];
    }

    pop->fitness = fitness;

    return fitness;
}

double cal_TCH(INDIVIDUAL *pop, double *weight_vector, int obj_num)
{
    int i = 0;
    double fitness = 0, diff = 0, maxFit = 0;

    maxFit = -1.0e+30;
    for (i = 0; i < obj_num; i++)
    {
        diff = fabs(pop->objective[i] - algorithm_entity.ideal_point.objective[i]);
        if (weight_vector[i] < EPS)
        {
            fitness = diff * 0.000001;
        }
        else
        {
            fitness = diff * weight_vector[i];
        }

        if (maxFit < fitness)
        {
            maxFit = fitness;
        }
    }

    fitness = maxFit;
    pop->fitness = fitness;
    return fitness;
}

extern double cal_ITCH (INDIVIDUAL *pop, double *weight_vector, int obj_num)
{
    int i = 0;
    double fitness = 0, diff = 0, maxFit = 0;

    maxFit = -1.0e+30;

    for (i = 0; i < obj_num; i++)
    {
        diff = fabs (pop->objective[i] - algorithm_entity.ideal_point.objective[i]);
        if (weight_vector[i] < EPS)
            fitness = diff / 0.000001;
        else
            fitness = diff / weight_vector[i];

        if (fitness > maxFit)
            maxFit = fitness;
    }

    fitness = maxFit;
    pop->fitness = fitness;

    return fitness;
}

void evaluation_individual(INDIVIDUAL *population, int index)
{
    INDIVIDUAL *pop = population + index;
    switch (algorithm_entity.test_problem)
    {
        case 0:
            zdt1(pop);
            break;
        case 1:
            zdt2(pop);
            break;
        case 2:
            zdt3(pop);
            break;
        case 3:
            zdt4(pop);
            break;
        case 4:
            zdt6(pop);
            break;
        case 5:
            sch(pop);
            break;
        case 6:
            kur(pop);
            break;
        case 7:
            dtlz1(pop);
            break;
        case 8:
            dtlz2(pop);
            break;
        case 9:
            dtlz3(pop);
            break;
        case 10:
            dtlz4(pop);
            break;
        case 11:
            dtlz5(pop);
            break;
        case 12:
            dtlz6(pop);
            break;
        case 13:
            dtlz7(pop);
            break;
        default:
            cout<<"UNKNOWN TEST PROBLEOM";
    }
}
double indicator(INDIVIDUAL pop1, INDIVIDUAL pop2)
{
    double r = algorithm_entity.variable_higher_bound[0]-algorithm_entity.variable_lower_bound[0];
    double epsilon = (pop1.objective[0] - pop2.objective[0])/r;
    for(int i = 1;i < algorithm_entity.algorithmParameter.objective_number;i++)
    {
        r = algorithm_entity.variable_higher_bound[i]-algorithm_entity.variable_lower_bound[i];
        if((pop1.objective[i] - pop2.objective[i])/r > epsilon)
            epsilon = (pop1.objective[i] - pop2.objective[i])/r;
    }
    return epsilon;
}