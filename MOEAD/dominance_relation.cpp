//
// Created by sinnable on 6/20/20.
//

#include "dominance_relation.h"

DOMINATE_RELATION check_dominance(INDIVIDUAL *ind1, INDIVIDUAL *ind2)
{
    int i;
    int flag1 = 0;
    int flag2 = 0;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        if (ind1->objective[i] < ind2->objective[i])
            flag1 ++;
        else
        {
            if (ind1->objective[i] > ind2->objective[i])
                flag2 ++;
        }
    }
    if (flag1 > 0 && flag2 == 0)
        return (DOMINATE);
    else
    {
        if (flag1 == 0 && flag2 > 0)
            return (DOMINATED);
        else
            return (NON_DOMINATED);
    }
}