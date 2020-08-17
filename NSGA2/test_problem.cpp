//
// Created by sinnable on 6/19/20.
//

#include "test_problem.h"
#include "global.h"

void zdt1(INDIVIDUAL *individual)
{
    double f1,f2,g,h;
    double temp = 0;

    f1 = individual->variable[0];

    for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
    {
        temp += individual->variable[i];
    }
    g = 1 + 9 * temp / (algorithm_entity.algorithmParameter.variable_number - 1);
    h = 1 - sqrt(f1 / g);
    f2 = g * h;
    individual->objective[0]=f1;
    individual->objective[1]=f2;
    return;
}
void zdt2(INDIVIDUAL *individual)
{
    double f1,f2,g,h;
    double temp = 0;

    f1 = individual->variable[0];

    for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
    {
        temp += individual->variable[i];
    }
    g = 1 + 9 * temp / (algorithm_entity.algorithmParameter.variable_number - 1);
    h = 1 - pow(f1 / g,2);
    f2 = g * h;
    individual->objective[0]=f1;
    individual->objective[1]=f2;
    return;
}

void zdt3(INDIVIDUAL *individual)
{
    double f1,f2,g,h;
    double temp = 0;

    f1 = individual->variable[0];

    for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
    {
        temp += individual->variable[i];
    }
    g = 1 + 9 * temp / (algorithm_entity.algorithmParameter.variable_number - 1);
    h = 1 - sqrt(f1 / g) - f1 / g * sin(10 * PI * f1);
    f2 = g * h;
    individual->objective[0]=f1;
    individual->objective[1]=f2;
    return;
}

void zdt4(INDIVIDUAL *individual)
{
    double f1,f2,g,h;
    double temp = 0;

    f1 = individual->variable[0];

    for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
    {
        temp += pow(individual->variable[i],2) - 10 * cos(4 * PI * individual->variable[i]);
    }
    g = 1 + 10 * (algorithm_entity.algorithmParameter.variable_number - 1) + temp;
    h = 1 - sqrt(f1 / g);
    f2 = g * h;
    individual->objective[0]=f1;
    individual->objective[1]=f2;
    return;
}

void zdt6(INDIVIDUAL *individual)
{
    double f1,f2,g,h;
    double temp = 0;

    f1 = 1 - exp(-4 * individual->variable[0]) * pow(sin(6 * PI * individual->variable[0]),6);

    for(int i = 1;i < algorithm_entity.algorithmParameter.variable_number;i++)
    {
        temp += individual->variable[i];
    }
    g = 1 + 9 * pow(temp / (algorithm_entity.algorithmParameter.variable_number - 1),0.25);
    h = 1 - pow(f1 / g,2);
    f2 = g * h;
    individual->objective[0]=f1;
    individual->objective[1]=f2;
    return;
}
void sch(INDIVIDUAL *individual)
{
    individual->objective[0] = pow(individual->variable[0],2);
    individual->objective[1] = pow(individual->variable[0] - 2.0,2);
    return;
}

extern void kur(INDIVIDUAL *individual)
{
    double f1 = 0, f2 = 0;
    for(int i = 0;i < 2;i++)
    {
        f1 += -10 * exp(-0.2 * sqrt(pow(individual->variable[i],2) + pow(individual->variable[i+1],2)));
    }
    for(int i = 0;i < 3;i++)
    {
        f2 += pow(fabs(individual->variable[i]),0.8) + 5 * sin(pow(individual->variable[i],3));
    }
    individual->objective[0] = f1;
    individual->objective[1] = f2;
    return;
}

void dtlz2(INDIVIDUAL *individual)
{
    int i, j, k;
    int aux;
    double gx;


    gx = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += pow((individual->variable[i] - 0.5), 2.0);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        individual->objective[i] = 1.0 + gx;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            individual->objective[i] *= cos(PI * 0.5 * individual->variable[j]);
        if (i != 0)
        {
            aux     = algorithm_entity.algorithmParameter.objective_number - (i + 1);
            individual->objective[i] *= sin(PI * 0.5 * individual->variable[aux]);
        }
    }
    return;
}

void dtlz6(INDIVIDUAL *individual)
{
    int i, j, k;
    int aux;
    double gx, temp;
    double *theta;

    theta = (double *) malloc (algorithm_entity.algorithmParameter.variable_number * sizeof(double));

    gx = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += pow(individual->variable[i], 0.1);
    temp     = PI / (4.0 * (1.0 + gx));
    theta[0] = individual->variable[0] * PI / 2.0;
    for (i = 1; i < (algorithm_entity.algorithmParameter.objective_number - 1); i++)
        theta[i] = temp * (1.0 + 2.0 * gx * individual->variable[i]);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        individual->objective[i] = 1.0 + gx;


    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            individual->objective[i] *= cos(theta[j]);
        if (i != 0)
        {
            aux     = algorithm_entity.algorithmParameter.objective_number - (i + 1);
            individual->objective[i] *= sin(theta[aux]);
        }
    }
    free(theta);
    return;
}