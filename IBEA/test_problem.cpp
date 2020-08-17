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

void kur(INDIVIDUAL *individual)
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

void dtlz1(INDIVIDUAL* ind)
{
    int i = 0, j = 0, k = 0, temp = 0;
    double g = 0;

    double *xreal, *obj;

    obj   = ind->objective;
    xreal = ind->variable;

    g = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        g += pow((xreal[i] - 0.5), 2.0) - cos(20.0 * PI * (xreal[i] - 0.5));
    g = 100.0 * (k + g);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        obj[i] = (1.0 + g) * 0.5;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            obj[i] *= xreal[j];
        if (i != 0)
        {
            temp = algorithm_entity.algorithmParameter.objective_number- (i + 1);
            obj[i] *= 1 - xreal[temp];
        }
    }
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
void dtlz3(INDIVIDUAL* ind)
{
    int i, j, k;
    int aux;
    double gx;
    double *xreal, *obj;

    obj   = ind->objective;
    xreal = ind->variable;

    gx = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += pow((xreal[i] - 0.5), 2.0) - cos(20.0 * PI * (xreal[i] - 0.5));
    gx = 100.0 * (k + gx);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        obj[i] = 1.0 + gx;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            obj[i] *= cos(PI * 0.5 * xreal[j]);
        if (i != 0)
        {
            aux     = algorithm_entity.algorithmParameter.objective_number - (i + 1);
            obj[i] *= sin(PI * 0.5 * xreal[aux]);
        }
    }
}


void dtlz4(INDIVIDUAL* ind)
{
    int i, j, k;
    int aux;
    double gx, alpha;
    double *xreal, *obj;

    obj   = ind->objective;
    xreal = ind->variable;

    gx    = 0.0;
    alpha = 100.0;
    k     = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += pow((xreal[i] - 0.5), 2.0);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        obj[i] = 1.0 + gx;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            obj[i] *= cos(PI * 0.5 * pow(xreal[j], alpha));
        if (i != 0)
        {
            aux     = algorithm_entity.algorithmParameter.objective_number - (i + 1);
            obj[i] *= sin(PI * 0.5 * pow(xreal[aux], alpha));
        }
    }
}


void dtlz5(INDIVIDUAL* ind)
{
    int i, j, k;
    int aux;
    double temp, gx;
    double *xreal, *obj, *theta;

    obj   = ind->objective;
    xreal = ind->variable;
    theta = (double *) malloc (algorithm_entity.algorithmParameter.variable_number * sizeof(double));

    gx = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += pow((xreal[i] - 0.5), 2.0);

    temp     = PI / (4.0 * (1.0 + gx));
    theta[0] = xreal[0] * PI / 2.0;
    for (i = 1; i < (algorithm_entity.algorithmParameter.objective_number - 1); i++)
        theta[i] = temp * (1.0 + 2.0 * gx * xreal[i]);

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        obj[i] = 1.0 + gx;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number - (i + 1); j++)
            obj[i] *= cos(theta[j]);
        if (i != 0)
        {
            aux     = algorithm_entity.algorithmParameter.objective_number - (i + 1);
            obj[i] *= sin(theta[aux]);
        }
    }
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
void dtlz7(INDIVIDUAL * ind)
{
    int i, j, k;
    int aux;
    double h, gx;
    double *xreal, *obj;

    obj   = ind->objective;
    xreal = ind->variable;

    gx = 0.0;
    k  = algorithm_entity.algorithmParameter.variable_number - algorithm_entity.algorithmParameter.objective_number + 1;
    for(i = algorithm_entity.algorithmParameter.variable_number - k; i < algorithm_entity.algorithmParameter.variable_number; i++)
        gx += xreal[i];
    gx = 1.0 + (9.0 * gx) / k;

    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
        obj[i] = xreal[i];

    h = 0.0;
    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number - 1; i++)
        h += (obj[i] / (1.0 + gx)) * (1.0 + sin (3.0 * PI * obj[i]));
    h = algorithm_entity.algorithmParameter.objective_number - h;

    obj[algorithm_entity.algorithmParameter.objective_number - 1] = (1 + gx) * h;
}

