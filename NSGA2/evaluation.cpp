//
// Created by sinnable on 6/20/20.
//

#include "evaluation.h"
#include "test_problem.h"

void evaluation(INDIVIDUAL *pop, int pop_size)
{
    for(int i = 0; i < pop_size; i++)
    {
        evaluation_individual(&pop[i]);
    }
}

void evaluation_individual(INDIVIDUAL *pop)
{

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
            dtlz2(pop);
            break;
        case 8:
            dtlz6(pop);
            break;
        default:
            cout<<"UNKNOWN TEST PROBLEOM";
    }
}