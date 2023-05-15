//========================================================================
/*
D. Vale, N. Paar 
 - created Feb 01 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#ifndef _TI_H
#define _TI_H

#include "operator.h"
#include "reading.h"


int warning_repeating_indices(operator_t *, int);
operator_t * transformation_of_indices(operator_t *, paramet_t, int, int *);


all_operator_t transformation_of_indices_if_needed(all_operator_t all_op, paramet_t par, int *transformed);

int test_konz();
void test_transformation();
#endif
