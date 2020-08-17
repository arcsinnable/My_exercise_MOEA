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
# define MAX_SIZE 1000
# define EPS 1.0e-7
typedef struct
{
    int rank;
    double *variable;
    double *objective;
    double fitness;
    double crowding_distance;
}INDIVIDUAL;

typedef struct {
    double value;
    int idx;
}Distance_info;

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

typedef struct {
    int idx;
    int *neighbor;
}MOEAD_NEIGHBOR;

typedef enum {
    NEIGHBOR,
    GLOBAL_PARENT
}NeighborType;

typedef enum {
    WS,
    N_WS,
    TCH,
    N_TCH,
    ITCH,
    N_ITCH,
    PBI,
    N_PBI
}MoeadFunction;

typedef struct
{
    int population_size;
    int neighbor_size;
    int variable_number;
    int objective_number;
    int max_evaluation;
    int output_interval;
    MoeadFunction function_type;
    double neighborhood_selection_probability;
    int maximumNumberOfReplacedSolutions;
    MOEAD_NEIGHBOR *neighbor_table;
    MUTATIONTYPE mutation_type;
    CROSSOVERTYPE crossover_type;
}ALGORITHM_PARAMETER;

typedef struct
{
    double *variable;
    double *objective;
}REFERENCE_POINT;

typedef struct{
    double CR;
    double F;
    double K;
}DE_PARA;

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

    REFERENCE_POINT ideal_point;

    double *variable_lower_bound;
    double *variable_higher_bound;


    DE_PARA  dePara;
    ALGORITHM_PARAMETER algorithmParameter;
    TESTPROBLEM test_problem;
    SBXPARAMETER sbx_parameter;
    POLYNOMIALPARAMETER polynomial_parameter;
}MOEAD_entity;


extern MOEAD_entity algorithm_entity;
extern double Diversity_metric;
extern double **lambda;
extern int weight_num;

#endif //UNTITLED_GLOBAL_H
