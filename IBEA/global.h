//
// Created by sinnable on 6/18/20.
//

#ifndef UNTITLED_GLOBAL_H
#define UNTITLED_GLOBAL_H
# include <iostream>
# include <time.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <random>
using namespace std;

# define PI acos(-1)
# define FAIL 0
# define SUCCESS 1

typedef struct
{
    int rank;
    double *variable;
    double *objective;
    double fitness;
    double crowding_distance;
}INDIVIDUAL;

typedef enum
{
    ZDT1,
    ZDT2,
    ZDT3,
    ZDT4,
    ZDT6,
    SCH,
    KUR,
    DTLZ1,
    DTLZ2,
    DTLZ3,
    DTLZ4,
    DTLZ5,
    DTLZ6,
    DTLZ7
}TESTPROBLEM;

typedef enum
{
    polynomial
}MUTATIONTYPE;

typedef struct
{
    double p_mutation;
    double eta_mutation;
}POLYNOMIALPARAMETER;

typedef enum
{
    SBX
}CROSSOVERTYPE;

typedef struct
{
    double p_crossover;
    double eta_crossover;
}SBXPARAMETER;

typedef struct
{
    int population_size;
    int variable_number;
    int objective_number;
    int max_evaluation;
    int output_interval;
    MUTATIONTYPE mutation_type;
    CROSSOVERTYPE crossover_type;
}ALGORITHM_PARAMETER;

typedef struct
{
    int iteration_number;
    int run_index_begin;
    int run_index_current;
    int run_index_end;

    INDIVIDUAL *parent_pop;
    INDIVIDUAL *offspring_pop;
    INDIVIDUAL *mix_pop;
    INDIVIDUAL *elt_pop;

    double *variable_lower_bound;
    double *variable_higher_bound;

    double fitness_scaling_factor;
    ALGORITHM_PARAMETER algorithmParameter;
    TESTPROBLEM test_problem;
    SBXPARAMETER sbx_parameter;
    POLYNOMIALPARAMETER polynomial_parameter;
}IBEA_entity;

extern IBEA_entity algorithm_entity;
extern double Diversity_metric;
#endif //UNTITLED_GLOBAL_H
