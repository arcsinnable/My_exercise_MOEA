//
// Created by sinnable on 6/20/20.
//

#ifndef UNTITLED_DOMINANCE_RELATION_H
#define UNTITLED_DOMINANCE_RELATION_H
#include "global.h"
typedef enum{
    DOMINATE,
    DOMINATED,
    NON_DOMINATED
}DOMINATE_RELATION;

extern DOMINATE_RELATION check_dominance(INDIVIDUAL *ind1, INDIVIDUAL *ind2);


#endif //UNTITLED_DOMINANCE_RELATION_H
