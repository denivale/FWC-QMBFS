#ifndef _CANONICAL_H
#define _CANONICAL_H

#include "operator.h"

short count_general_operators(operator_t *, int);

all_comb_of_operator_t prepair_combinations(all_operator_t all_op);

void create_combinations_by_canonical_transformation(operator_t **, operator_t *, int, int);

#endif
