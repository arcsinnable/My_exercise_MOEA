//
// Created by sinnable on 7/2/20.
//

#include "reproduct.h"

void reproduction(int male_index, int female_index, int offspring_index)
{
    int temp;
    float rand,rd;
    temp = entity.parent_male_population[male_index].gene + entity.parent_female_population[female_index].gene;
    switch(temp){
        case 0:
        {
            entity.offspring_male_population[offspring_index].gene = AA;
            entity.offspring_male_population[offspring_index].language_ability = strong;
            entity.offspring_male_population[offspring_index].sex = male;
            entity.offspring_male_population[offspring_index].period = none;
            entity.offspring_male_population[offspring_index].sign = 0;
            entity.offspring_female_population[offspring_index].gene = AA;
            entity.offspring_female_population[offspring_index].language_ability = strong;
            entity.offspring_female_population[offspring_index].sex = female;
            if((float)random()/(float)RAND_MAX <= 0.5)
                entity.offspring_female_population[offspring_index].period = luteal;
            else
                entity.offspring_female_population[offspring_index].period = ovulation;
            entity.offspring_female_population[offspring_index].sign = 0;
            break;
        }
        case 1:
        {
            if((float)random()/(float)RAND_MAX <= 0.5){
                entity.offspring_male_population[offspring_index].gene = AA;
            }
            else{
                entity.offspring_male_population[offspring_index].gene = Aa;

            }
            entity.offspring_male_population[offspring_index].language_ability = strong;
            entity.offspring_male_population[offspring_index].sex = male;
            entity.offspring_male_population[offspring_index].period = none;
            entity.offspring_male_population[offspring_index].sign = 0;
            if((float)random()/(float)RAND_MAX <= 0.5){
                entity.offspring_female_population[offspring_index].gene = AA;
            }
            else{
                entity.offspring_female_population[offspring_index].gene = Aa;

            }
            entity.offspring_female_population[offspring_index].language_ability = strong;
            entity.offspring_female_population[offspring_index].sex = female;
            if((float)random()/(float)RAND_MAX <= 0.5)
                entity.offspring_female_population[offspring_index].period = luteal;
            else
                entity.offspring_female_population[offspring_index].period = ovulation;
            entity.offspring_female_population[offspring_index].sign = 0;
            break;
        }
        case 2:
        {
            if(entity.parent_male_population[male_index].gene == Aa)
            {
                rand = (float)random()/(float)RAND_MAX;
                if(rand <= 0.25){
                    entity.offspring_male_population[offspring_index].gene = aa;
                    entity.offspring_male_population[offspring_index].language_ability = weak;
                }
                else if(rand <= 0.5){
                    entity.offspring_male_population[offspring_index].gene = AA;
                    entity.offspring_male_population[offspring_index].language_ability = strong;
                }
                else{
                    entity.offspring_male_population[offspring_index].gene = Aa;
                    entity.offspring_male_population[offspring_index].language_ability = strong;
                }
                entity.offspring_male_population[offspring_index].sex = male;
                entity.offspring_male_population[offspring_index].period = none;
                entity.offspring_male_population[offspring_index].sign = 0;
                rand = (float)random()/(float)RAND_MAX;
                if(rand <= 0.25){
                    entity.offspring_male_population[offspring_index].gene = aa;
                    entity.offspring_male_population[offspring_index].language_ability = weak;
                }
                else if(rand <= 0.5){
                    entity.offspring_male_population[offspring_index].gene = AA;
                    entity.offspring_male_population[offspring_index].language_ability = strong;
                }
                else{
                    entity.offspring_male_population[offspring_index].gene = Aa;
                    entity.offspring_male_population[offspring_index].language_ability = strong;
                }
                entity.offspring_female_population[offspring_index].sex = female;
                if((float)random()/(float)RAND_MAX <= 0.5)
                    entity.offspring_female_population[offspring_index].period = luteal;
                else
                    entity.offspring_female_population[offspring_index].period = ovulation;
                entity.offspring_female_population[offspring_index].sign = 0;
            }
            else
            {
                entity.offspring_male_population[offspring_index].gene = Aa;
                entity.offspring_male_population[offspring_index].language_ability = strong;
                entity.offspring_male_population[offspring_index].sex = male;
                entity.offspring_male_population[offspring_index].period = none;
                entity.offspring_male_population[offspring_index].sign = 0;
                entity.offspring_female_population[offspring_index].gene = Aa;
                entity.offspring_female_population[offspring_index].language_ability = strong;
                entity.offspring_female_population[offspring_index].sex = female;
                if((float)random()/(float)RAND_MAX <= 0.5)
                    entity.offspring_female_population[offspring_index].period = luteal;
                else
                    entity.offspring_female_population[offspring_index].period = ovulation;
                entity.offspring_female_population[offspring_index].sign = 0;
            }
            break;
        }
        case 3:
        {
            if((float)random()/(float)RAND_MAX <= 0.5){
                entity.offspring_male_population[offspring_index].gene = aa;
                entity.offspring_male_population[offspring_index].language_ability = weak;
            }
            else{
                entity.offspring_male_population[offspring_index].gene = Aa;
                entity.offspring_male_population[offspring_index].language_ability = strong;
            }
            entity.offspring_male_population[offspring_index].sex = male;
            entity.offspring_male_population[offspring_index].period = none;
            entity.offspring_male_population[offspring_index].sign = 0;
            if((float)random()/(float)RAND_MAX <= 0.5){
                entity.offspring_female_population[offspring_index].gene = aa;
                entity.offspring_female_population[offspring_index].language_ability = weak;
            }
            else{
                entity.offspring_female_population[offspring_index].gene = Aa;
                entity.offspring_female_population[offspring_index].language_ability = strong;
            }
            entity.offspring_female_population[offspring_index].sex = female;
            if((float)random()/(float)RAND_MAX <= 0.5)
                entity.offspring_female_population[offspring_index].period = luteal;
            else
                entity.offspring_female_population[offspring_index].period = ovulation;
            entity.offspring_female_population[offspring_index].sign = 0;
            break;
        }
        case 4:
        {
            entity.offspring_male_population[offspring_index].gene = aa;
            entity.offspring_male_population[offspring_index].language_ability = weak;
            entity.offspring_male_population[offspring_index].sex = male;
            entity.offspring_male_population[offspring_index].period = none;
            entity.offspring_male_population[offspring_index].sign = 0;
            entity.offspring_female_population[offspring_index].gene = aa;
            entity.offspring_female_population[offspring_index].language_ability = weak;
            entity.offspring_female_population[offspring_index].sex = female;
            if((float)random()/(float)RAND_MAX <= 0.5)
                entity.offspring_female_population[offspring_index].period = luteal;
            else
                entity.offspring_female_population[offspring_index].period = ovulation;
            entity.offspring_female_population[offspring_index].sign = 0;
            break;
        }
        default:
            break;
    }
    if(ovulation == entity.parent_female_population[female_index].period)
    {
        if(strong == entity.parent_male_population[male_index].language_ability)
        {
            entity.offspring_male_population[offspring_index].survive_rate = H;
            entity.offspring_female_population[offspring_index].survive_rate = H;
        }
        else
        {
            entity.offspring_male_population[offspring_index].survive_rate = L;
            entity.offspring_female_population[offspring_index].survive_rate = L;
        }
    }
    else
    {
        if(strong == entity.parent_male_population[male_index].language_ability)
        {
            entity.offspring_male_population[offspring_index].survive_rate = HH;
            entity.offspring_female_population[offspring_index].survive_rate = HH;
        }
        else
        {
            entity.offspring_male_population[offspring_index].survive_rate = LL;
            entity.offspring_female_population[offspring_index].survive_rate = LL;
        }
    }

    rand = (float)random()/(float)RAND_MAX;
    if(rand > 0.5)
    {
        rd = (float)random()/(float)RAND_MAX;
        if(rd <= 1.0/4.0)
            entity.offspring_male_population[offspring_index].gene = AA;
        else if(rd > 1.0/4.0 && rd <= 3.0/4.0)
            entity.offspring_male_population[offspring_index].gene = Aa;
        else
            entity.offspring_male_population[offspring_index].gene = aa;
        if(entity.offspring_male_population[offspring_index].gene == AA || entity.offspring_male_population[offspring_index].gene == Aa)
            entity.offspring_male_population[offspring_index].language_ability = strong;
        else
            entity.offspring_male_population[offspring_index].language_ability = weak;
    }
    rand = (float)random()/(float)RAND_MAX;
    if(rand > 0.5)
    //if(rand > 0.25 * (entity.offspring_female_population[offspring_index].survive_rate + 1))
    {
        rd = (float)random()/(float)RAND_MAX;
        if(rd <= 1.0/4.0)
            entity.offspring_female_population[offspring_index].gene = AA;
        else if(rd > 1.0/4.0 && rd <= 3.0/4.0)
            entity.offspring_female_population[offspring_index].gene = Aa;
        else
            entity.offspring_female_population[offspring_index].gene = aa;
        if(entity.offspring_female_population[offspring_index].gene == AA || entity.offspring_female_population[offspring_index].gene == Aa)
            entity.offspring_female_population[offspring_index].language_ability = strong;
        else
            entity.offspring_female_population[offspring_index].language_ability = weak;
    }
    return;
}