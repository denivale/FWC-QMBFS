//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 24 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#ifndef _CONTRACTION_H
#define _CONTRACTION_H

#include "operator.h"
#include "point.h"
#include "line.h"
#include "draw.h"
#include "output.h"
#include "kronecker.h"



void find_indices_of_particular_type_of_operator(operator_t *op, short *stogod, short n, char t, short c, short *count);

int full_contract_one(operator_t *op, int n, short comb_order, short *nonzero_deltas, info_draw_t*);




int pair_test(operator_t *, int, short *, short *);
int contract_one_line(operator_t, operator_t, kronecker_t *);
int contract_lines(point_t *, point_t *, short *, directed_line_t *, operator_t *, int, kronecker_t *);

contraction_out_t contract_wick_lines(all_point_t T, all_directed_lines_t all_lines, all_operator_t all_op, int ord);
directed_line_t * create_beg_of_contraction_lines(int numlines, short * hc, short *pc, short coh);



#endif
