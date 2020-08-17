//
// Created by sinnable on 8/9/20.
//

# include "utility.h"
# include "random.h"

static int combination (int n, int k)
{
    int i;

    if (n < k)
        return -1;
    double ans = 1;
    for (i = k + 1; i <= n; i++)
    {
        ans = ans * i;
        ans = ans / (double) (i - k);
    }

    return (int) ans;
}
static void set_weight (double *weight, double unit, double sum, int dim, int *column, double **lambda)
{
    int i;

    if (dim == algorithm_entity.algorithmParameter.objective_number)
    {
        for ( i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
            weight[i] = 0;
    }

    if (dim == 1)
    {
        weight[0] = unit - sum;
        for ( i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
            lambda[*column][i] = weight[i];
        *column = *column + 1;
        return;
    }
    for (i = 0; i <= unit - sum; i++)
    {
        weight[dim - 1] = i;
        set_weight (weight, unit, sum + i, dim - 1, column, lambda);
    }

    return;
}
double **initialize_uniform_point (int  num, int *number_weight)
{
    int i, j;

    int layer_size;
    int column = 0;

    double *Vec;
    double **lambda = NULL;

    int gaps = 1;
    for(int i = 0;i < algorithm_entity.algorithmParameter.population_size;i++)
    {
        for(int j = 0;j < algorithm_entity.algorithmParameter.variable_number;j++)
        {
            algorithm_entity.parent_pop[i].variable[j] = 0;
        }
    }
    *number_weight = 0;
    while(1)
    {
        layer_size  = combination(algorithm_entity.algorithmParameter.objective_number + gaps - 1, gaps);
        //printf("[%d]%d\n",gaps,layer_size);

        if(layer_size > num) break;
        *number_weight = layer_size;
        gaps = gaps + 1;

    }

    gaps = gaps - 1;
    lambda = (double **) malloc ((*number_weight) * sizeof(double *));
    for (i = 0; i < *number_weight; i++)
    {
        lambda[i] = (double *) malloc(algorithm_entity.algorithmParameter.objective_number  * sizeof(double));
    }

    Vec = (double *) malloc (algorithm_entity.algorithmParameter.objective_number  * sizeof(double));
    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number ; i++)
        Vec[i] = 0;
    set_weight(Vec, gaps, 0, algorithm_entity.algorithmParameter.objective_number, &column, lambda);

    for (i = 0; i < *number_weight; i++)
        for (j = 0; j < algorithm_entity.algorithmParameter.objective_number; j++) {
            lambda[i][j] = lambda[i][j] / gaps;
        }


    free (Vec);

    return lambda;
}
double cal_moead_fitness(INDIVIDUAL *ind, double *weight, MoeadFunction function_type)
{
    switch (function_type)
    {
        case WS:
            cal_weighted_sum(ind, weight, algorithm_entity.algorithmParameter.objective_number);
            break;

        case TCH:
            cal_TCH(ind, weight, algorithm_entity.algorithmParameter.objective_number);
            break;
        case ITCH:
            cal_ITCH(ind, weight, algorithm_entity.algorithmParameter.objective_number);
        default:
            break;
    }
}
void update_ideal_point_by_ind(INDIVIDUAL *pop, int index)
{
    int i = 0;
    INDIVIDUAL *ind=pop+index;
    for (i = 0; i < algorithm_entity.algorithmParameter.objective_number; i++)
    {
        if (ind->objective[i] < algorithm_entity.ideal_point.objective[i])
        {
            algorithm_entity.ideal_point.objective[i] = ind->objective[i];
        }
    }
    return;
}
int update_subproblem(INDIVIDUAL *offspring, int pop_index, NeighborType type)
{
    int i = 0;
    int index = 0, replace_num = 0, size = 0;
    int *perm = NULL;
    double temp = 0, old_fit = 0;

    if (NEIGHBOR == type)
        size = algorithm_entity.algorithmParameter.neighbor_size;
    else
        size = algorithm_entity.algorithmParameter.population_size;

    perm = (int *)malloc(sizeof(int) * size);
    random_permutation(perm, size);

    for (i = 0; i < size; i++)
    {
        if (replace_num >= algorithm_entity.algorithmParameter.maximumNumberOfReplacedSolutions)
        {
            break;
        }
        if (NEIGHBOR == type)
            index = algorithm_entity.algorithmParameter.neighbor_table[pop_index].neighbor[perm[i]];
        else
            index = perm[i];
        temp = cal_moead_fitness(offspring, lambda[index], algorithm_entity.algorithmParameter.function_type);
        old_fit = cal_moead_fitness(algorithm_entity.parent_pop + index, lambda[index], algorithm_entity.algorithmParameter.function_type);
        if (temp < old_fit)
        {
            memcpy(algorithm_entity.parent_pop[index].variable,offspring->variable,sizeof(double) * algorithm_entity.algorithmParameter.variable_number);
            memcpy(algorithm_entity.parent_pop[index].objective, offspring->objective,sizeof(double) * algorithm_entity.algorithmParameter.objective_number);
            algorithm_entity.parent_pop[index].fitness = temp;
            replace_num++;
        }
    }

    free(perm);

    return SUCCESS;
}