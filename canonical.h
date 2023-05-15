//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 24 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================
#ifndef _CANONICAL_H
#define _CANONICAL_H

#include "operator.h"

short count_general_operators(operator_t *, int);

all_comb_of_operator_t prepair_combinations(all_operator_t);

void create_combinations_by_canonical_transformation(operator_t **, operator_t *, int, int);

#endif
