//
// Created by sinnable on 7/2/20.
//

#include "initialize.h"
Status initialize()
{
    float rand = 0;
    entity.parent_female_population = (Individual *)malloc(sizeof(Individual) * entity.population_size);
    if(NULL == entity.parent_female_population)
        return FAIL;
    entity.parent_male_population = (Individual *)malloc(sizeof(Individual) * entity.population_size);
    if(NULL == entity.parent_male_population)
        return FAIL;
    entity.offspring_female_population = (Individual *)malloc(sizeof(Individual) *entity.population_size);
    if(NULL == entity.offspring_female_population)
        return FAIL;
    entity.offspring_male_population = (Individual *)malloc(sizeof(Individual) * entity.population_size);
    if(NULL == entity.offspring_male_population)
        return FAIL;
    entity.mating_strategy = select_strategy;     //fill with neturl_strategy or select_strategy

    for(int i = 0;i < entity.population_size;i++)
    {
        entity.parent_male_population[i].sex = male;
        entity.parent_female_population[i].sex = female;

        entity.parent_female_population[i].sign = 0;
        entity.parent_male_population[i].sign = 0;


        rand = (float)random()/(float)RAND_MAX;
        if(rand <= 1.0/4.0)
            entity.parent_male_population[i].gene = AA;
        else if(rand > 1.0/4.0 && rand <= 3.0/4.0)
            entity.parent_male_population[i].gene = Aa;
        else
            entity.parent_male_population[i].gene = aa;
        rand = (float)random()/(float)RAND_MAX;
        if(rand <= 1.0/4.0)
            entity.parent_female_population[i].gene = AA;
        else if(rand > 1.0/4.0 && rand <= 3.0/4.0)
            entity.parent_female_population[i].gene = Aa;
        else
            entity.parent_female_population[i].gene = aa;


        entity.parent_male_population[i].period = none;
        rand = (float)random()/(float)RAND_MAX;
        if(rand <= 0.5)
            entity.parent_female_population[i].period = luteal;
        else
            entity.parent_female_population[i].period = ovulation;


        if(entity.parent_male_population[i].gene == AA || entity.parent_male_population[i].gene == Aa)
            entity.parent_male_population[i].language_ability = strong;
        else
            entity.parent_male_population[i].language_ability = weak;
        if(entity.parent_female_population[i].gene == AA || entity.parent_female_population[i].gene == Aa)
            entity.parent_female_population[i].language_ability = strong;
        else
            entity.parent_female_population[i].language_ability = weak;
    }
    return SUCCESS;
}