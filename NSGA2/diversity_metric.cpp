//
// Created by sinnable on 6/21/20.
//

#include "diversity_metric.h"

double diversity_metric(INDIVIDUAL *pop, int pop_size)
{
    int *sort;
    INDIVIDUAL  temp;
    double dl, du, *d, d_mean, a;
    sort = (int *)malloc(sizeof(int) * pop_size);
    d =(double *)malloc((sizeof(double) * (pop_size - 1)));
    for(int i = 0;i < pop_size;i++)
    {
        sort[i] = i;
    }
    for(int i = 0;i < pop_size - 1;i++)
    {
        for(int j = i + 1; pop_size;j++)
        {
            if(pop[i].objective[1] > pop[i].objective[j])
            {
                temp = pop[i];
                pop[i] = pop[j];
                pop[j] = temp;
            }
        }
    }
    dl = sqrt(pow(pop[0].objective[0] - 0.0, 2) + pow(pop[0].objective[1] - 1.0, 2));
    du = sqrt(pow(pop[pop_size - 1].objective[0] - 1.0, 2) + pow(pop[0].objective[1] - 1.0, 2));
    d_mean = 0;
    for(int i = 0;i < pop_size - 1;i++)
    {
        d[i] = sqrt(pow(pop[i].objective[0] - pop[i+1].objective[0], 2) + pow(pop[i].objective[1] - pop[i+1].objective[1],2));
        d_mean += d[i]/(pop_size - 1);
    }
    a = 0;
    for(int i = 0;i < pop_size - 1;i++)
    {
        a+= fabs(d[i] - d_mean);
    }
    free(d);
    free(sort);
    return (dl + du + a)/(dl + du + (pop_size - 1) * d_mean);
}