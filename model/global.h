//
// Created by sinnable on 6/25/20.
//

#ifndef MODEL_GLOBAL_H
#define MODEL_GLOBAL_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef enum
{
    male,
    female
}Sex;

typedef enum
{
    AA,
    Aa,
    aa
}Gene;

typedef enum
{
    strong,
    weak
}Language_Ability;

typedef enum
{
    none,
    luteal,
    ovulation
}Period;

typedef enum
{
    LL,
    L,
    H,
    HH
}Survive_Rate;

typedef enum
{
    neturl_strategy,
    select_strategy
}Mating_Strategy;

typedef enum
{
    FAIL,
    SUCCESS
}Status;

typedef struct
{
    Sex sex;
    Gene gene;
    Language_Ability language_ability;
    Period period;
    Survive_Rate survive_rate;
    int sign;
}Individual;

typedef struct Male_mating_list{
    int index;
    Male_mating_list *next;
}Male_mating_list;

typedef struct
{
    Individual *parent_male_population;
    Individual *parent_female_population;
    Individual *offspring_male_population;
    Individual *offspring_female_population;

    Mating_Strategy mating_strategy;

    int generation_current;
    int max_generation;
    int population_size;
    int index_run_begin;
    int index_run_end;
    int index_run_current;

    double *A_gene_rate;
    double *a_gene_rate;

}Model_entity;


extern Model_entity entity;


#endif //MODEL_GLOBAL_H
