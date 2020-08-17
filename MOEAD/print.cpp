//
// Created by sinnable on 6/20/20.
//

#include "print.h"

void print_progress(MOEAD_entity entity)
{
    cout<< "|The  " << entity.run_index_current << "  run  |  " << (double)entity.iteration_number / (double)entity.algorithmParameter.max_evaluation * 100 <<"% |"<<endl;
    fflush(stdout);
    return;
}
