//
// Created by sinnable on 6/20/20.
//

#include "mutation.h"

void mutation_individual(INDIVIDUAL *offspring_pop,int index)
{
    int i;
    double rnd, delta1, delta2, mut_pow, delta_q;
    double y, yl, yu, val, a;
    INDIVIDUAL *ind = offspring_pop + index;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<>  dis(0.0,1.0);

    for (i = 0; i < algorithm_entity.algorithmParameter.variable_number; i++)
    {
        if ((double)random()/(double)RAND_MAX <= algorithm_entity.polynomial_parameter.p_mutation)
        {
            y = ind->variable[i];

            yl      = algorithm_entity.variable_lower_bound[i];
            yu      = algorithm_entity.variable_higher_bound[i];
            delta1  = (y - yl) / (yu - yl);
            delta2  = (yu - y) / (yu - yl);
            rnd     = dis(gen);
            mut_pow = 1.0 / (algorithm_entity.polynomial_parameter.eta_mutation + 1.0);
            if (rnd <= 0.5)
            {
                a     = 1.0 - delta1;
                val    = 2.0 * rnd + (1.0 - 2.0 * rnd) * (pow(a, (algorithm_entity.polynomial_parameter.eta_mutation + 1.0)));
                delta_q = pow(val, mut_pow) - 1.0;
            }
            else
            {
                a     = 1.0 - delta2;
                val    = 2.0 * (1.0 - rnd) + 2.0 * (rnd - 0.5) * (pow(a, (algorithm_entity.polynomial_parameter.eta_mutation + 1.0)));
                delta_q = 1.0 - (pow(val, mut_pow));
            }
            y = y + delta_q * (yu - yl);
            if (y < yl)
                y = yl;
            if (y > yu)
                y = yu;
            ind->variable[i] = y;

        }
    }

    return;
}

//void mutation(INDIVIDUAL *pop, int pop_size)
//{
//    for(int i = 0;i < pop_size;i++)
//    {
//        mutation_individual(&pop[i]);
//    }
//    return;
//}