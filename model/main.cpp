#include "global.h"
#include "initialize.h"
#include "reproduct.h"

extern int mating_pool(int *male_index)
{
    if(neturl_strategy == entity.mating_strategy) {
        if ((float) random() / (float) RAND_MAX <= 0.5){
            entity.parent_male_population[male_index[1]].sign = 0;
            return male_index[0];
        }
        else{
            entity.parent_male_population[male_index[0]].sign = 0;
            return male_index[1];
        }
    }
    else if(select_strategy == entity.mating_strategy)
    {
        if(entity.parent_male_population[male_index[0]].language_ability > entity.parent_male_population[male_index[1]].language_ability)
        {
            entity.parent_male_population[male_index[1]].sign = 0;
            return male_index[0];
        }

        else if(entity.parent_male_population[male_index[0]].language_ability < entity.parent_male_population[male_index[1]].language_ability)
        {
            entity.parent_male_population[male_index[0]].sign = 0;
            return male_index[1];
        }

        else{
            if ((float) random() / (float) RAND_MAX <= 0.5){
                entity.parent_male_population[male_index[1]].sign = 0;
                return male_index[0];
            }
            else{
                entity.parent_male_population[male_index[0]].sign = 0;
                return male_index[1];
            }
        }
    }
    else{
        cout<<"There exists error when mating"<<endl;
        return 0;
    }
}


int main() {
    int female_index, male_index;
    int male_mating_index[2] = {-1,-1};
    int rand, count;
    int *A_num, *a_num, num1 = 0,num2 = 0;
    double ratio = 0;
    Male_mating_list *maleMatingList;
    entity.population_size = 2000;
    entity.index_run_begin = 0;
    entity.index_run_end = 10;
    entity.max_generation = 200;

    srand(time(NULL));
    for(int t = 0;t < entity.index_run_end;t++) {
        if (FAIL == initialize()) {
            cout << "There exists error when initializing" << endl;
            return 0;
        }
        A_num = (int *) malloc(sizeof(int) * entity.max_generation);
        a_num = (int *) malloc(sizeof(int) * entity.max_generation);
        for (int i = 0; i < entity.max_generation; i++) {
            A_num[i] = 0;
            a_num[i] = 0;
        }

        for (entity.generation_current = 0;
             entity.generation_current < entity.max_generation; entity.generation_current++) {
            for (int i = 0; i < entity.population_size; i++) {
                rand = random() % (entity.population_size - i);
                count = -1;
                for (int j = 0; j < entity.population_size; j++) {
                    if (entity.parent_female_population[j].sign == 0)
                        count++;
                    if (count == rand) {
                        female_index = j;
                        entity.parent_female_population[j].sign = 1;
                        break;
                    }
                }
                rand = random() % (entity.population_size - i);
                count = -1;
                for (int j = 0; j < entity.population_size; j++) {
                    if (entity.parent_male_population[j].sign == 0)
                        count++;
                    if (count == rand) {
                        male_mating_index[0] = j;
                        entity.parent_male_population[j].sign = 1;
                        break;
                    }
                }
                rand = random() % (entity.population_size - i);
                count = -1;
                for (int j = 0; j < entity.population_size; j++) {
                    if (entity.parent_male_population[j].sign == 0)
                        count++;
                    if (count == rand) {
                        male_mating_index[1] = j;
                        entity.parent_male_population[j].sign = 1;
                        break;
                    }
                }
                male_index = mating_pool(male_mating_index);
                reproduction(male_index, female_index, i);
            }
            for (int i = 0; i < entity.population_size; i++) {
                if (entity.offspring_male_population[i].gene == AA || entity.offspring_male_population[i].gene == Aa)
                    A_num[entity.generation_current] += 1;
                else a_num[entity.generation_current] += 1;

                if (entity.offspring_female_population[i].gene == AA ||
                    entity.offspring_female_population[i].gene == Aa)
                    A_num[entity.generation_current] += 1;
                else a_num[entity.generation_current] += 1;
            }

            for (int i = 0; i < entity.population_size; i++) {
                entity.parent_male_population[i].gene = entity.offspring_male_population[i].gene;
                entity.parent_male_population[i].survive_rate = entity.offspring_male_population[i].survive_rate;
                entity.parent_male_population[i].language_ability = entity.offspring_male_population[i].language_ability;
                entity.parent_male_population[i].period = entity.offspring_male_population[i].period;
                entity.parent_male_population[i].sign = entity.offspring_male_population[i].sign;

                entity.parent_female_population[i].gene = entity.offspring_female_population[i].gene;
                entity.parent_female_population[i].survive_rate = entity.offspring_female_population[i].survive_rate;
                entity.parent_female_population[i].language_ability = entity.offspring_male_population[i].language_ability;
                entity.parent_female_population[i].period = entity.offspring_female_population[i].period;
                entity.parent_female_population[i].sign = entity.offspring_female_population[i].sign;
            }
        }
        for (int i = 0; i < entity.max_generation; i++) {
            cout << A_num[i] << "," << a_num[i] << endl;
            ratio += (float) A_num[i] / (float) a_num[i];
        }
        cout << t << ":  " << ratio / entity.max_generation << endl;
        free(A_num);
        free(a_num);
        free(entity.parent_male_population);
        free(entity.parent_female_population);
        free(entity.offspring_male_population);
        free(entity.offspring_female_population);
    }
    return 0;
}
