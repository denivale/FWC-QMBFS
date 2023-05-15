/*
 D. Vale, N. Paar 
 - created Feb 1 2019
 - last modification May 15 2023 (D. Vale)
*/


#include <stdio.h>
#include <stdlib.h>

#include "preparation.h"
#include "calculation.h"
#include "calc_wick.h"
#include "operator.h"
#include "canonical.h"


int calculation(prep_t prep, option_t option){
short count;
all_operator_t all_op;

all_op = prep.in.all_op;

count = count_general_operators(all_op.op, all_op.n);

printf ("Number of general operators: %d\n", count);

calculate_all_comb_of_wick_contraction(prep, count);

free_all_operator(&all_op);

return 1;
}



void start_procedure(option_t option){
prep_t prep;

prep = preparation(option);

calculation(prep, option);

return;
}
