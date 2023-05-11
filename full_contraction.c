#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "shalloc.h"
#include "operator.h"
#include "point.h"
#include "line.h"
#include "kronecker.h"
#include "output.h"
#include "contraction.h"
#include "full_contraction.h"

//===========================================================================================================
// Function fwcoc(all_operator_t all_op, int ord):
// Description:
// The function of computing the complete Wick contraction of fermionic creation and annihilation operators that
// appear in many-particle theories. The procedure itself consists of 3 parts:
// Part 1:
// i) Testing the prerequisites of non-vanishing full Wick contractions,
// ii) We count particle and annihilation pairs if the preconditions are met,
// iii) We allocate the necessary memory
// Part 2:
// i) The beginning of the contraction lines is always the same, so we look for appearances exclusively
//    annihilation particle and annihilation operators.
// ii) We create incomplete directed lines where we define only their beginning - annihilation points
//     operator.
// iii) We create a geometric interpretation. We join the set of points on the vertices, i.e., 
//      equidistant points on the unit circle (equivalent interpreation vertices of regular n-polygone)
//      set of operators (equivalent geometric interpretation - n equidistant points on the circle).
//      It is the same for every possible contraction, but not for every combination of canonical transformations.
// iv) We create an empty set of Kronecker delta symbols.
// v) We are looking for the ordinal number of occurrences of the annihilation and particle creation operators.
// vi) We calculate the total number of permutations of the annihilation and particle creation operators.
// vii) We calculate all permutation realizations.
// Part 3:
// Given that annihilation and particle are independent operators, the number of contracting 
// possibilities will be given in multiplication of the number of permutations of the annihilation 
// creation operator and the number of permutations of the particle creation operator. For 
// every arrangemenet of quantum mechanical operators we calculate the permutation:
// i) ends of directed lines,
// ii) the corresponding Wick contraction of a particular realization of Wick's lines,
// iii) we store only non-vanishing contractions in the form of Kronecker delta and heavyside 
//      theta function and corresponding phase.
// Input arguments:
//  all_op - arrangement of quantum mechanical operators after canonical transformation if done
//  (hint all_operator_t)
//  ord - red. no.
// Exit:
//  All nonvanished contractions saved in data form all_contractions_out_t.
//===========================================================================================================
all_contractions_out_t fwcoc(all_operator_t all_op, int ord){
all_contractions_out_t temp;
short pair_p, pair_h;

temp.ord = ord;
// 1. dio:

//printf ("Pair test\n");
if (pair_test(all_op.op, all_op.n, &pair_p, &pair_h) == 0){
	zero_lab:
		temp.all = NULL;
		temp.nc = 0;
		temp.live = 0;
		temp.ord = ord;
		return temp;
	}

short num_lines;
short *hc, *ha, *pc, *pa;

num_lines = all_op.n/2;

if (pair_h != 0){
        hc = _1Ds(pair_h);
        ha = _1Ds(pair_h);
        }
else {
        printf ("pair_h = 0\n");
        hc = _1Ds(1);
        ha = _1Ds(1);
        }


if (pair_p != 0){
        pc = _1Ds(pair_p);
        pa = _1Ds(pair_p);
        }
else {
        printf ("pair_p = 0\n");
        pc = _1Ds(1);
        pa = _1Ds(1);
        }


// 2. dio:
directed_line_t *dline;
short coh, cop;
short i;
printf ("Searching indices of annihilation hole and particle operators (if exist) ...\n");

find_indices_of_particular_type_of_operator(all_op.op, ha, (short)all_op.n, 'h', -1, &coh);
find_indices_of_particular_type_of_operator(all_op.op, pa, (short)all_op.n, 'c', -1, &cop);

for (i = 0; i < coh; i++)
	printf ("ha[%d] = %d\n", i, ha[i]);

for (i = 0; i < cop; i++)
	printf ("pa[%d] = %d\n", i, pa[i]);

all_directed_lines_t all_dline;

all_dline.n = num_lines;
all_dline.line = create_beg_of_contraction_lines(num_lines, ha, pa, coh);


short ** perm_h, **perm_c;
int fh, fc;
short h, p;
int counter, rez;

temp.T = create_all_operator_points(all_op);

printf ("pair_h = %d\tpair_p = %d\n", pair_h, pair_p);

fh = factoriel(pair_h);
fc = factoriel(pair_p);

printf ("fh = %d\n", fh);
printf ("fc = %d\n", fc);


coh = 0; cop = 0;
find_indices_of_particular_type_of_operator(all_op.op, hc, (short)all_op.n, 'h', 1, &coh);
find_indices_of_particular_type_of_operator(all_op.op, pc, (short)all_op.n, 'c', 1, &cop);

reset_counter();

perm_h = _2Ds(fh, pair_h+1);
get_all_permutations(hc, 0, pair_h-1, pair_h, perm_h);
printf("Permutations of ending hole operators: \n");
for (h = 0; h < fh; h++){
        for (coh = 0; coh < pair_h; coh++)
                printf ("%4.1d", perm_h[h][coh]);
        printf ("\n");
        }
printf ("==========================\n");


reset_counter();

perm_c = _2Ds(fc, pair_p+1);
get_all_permutations(pc, 0, pair_p-1, pair_p, perm_c);
printf("Permutations of ending particle operators: \n");
for (p = 0; p < fc; p++){
        for (cop = 0; cop < pair_p; cop++)
                printf ("%4.1d", perm_c[p][cop]);
        printf ("\n");
        }
printf ("==========================\n");

// 3. dio
contraction_out_t res_contraction;
int cperm;
short calc;

printf ("Prepair intersections...\n");

print_operator_series(all_op.op, all_op.n);

printf (" = \n");

for (calc = 0; calc <= 1; calc++){
	counter = 0;
	cperm = 0;
	for (h = 0; h < fh; h++){
        	for (coh = 0; coh < pair_h; coh++){
                	all_dline.line[coh].end = perm_h[h][coh];
                	}
        	for (p = 0; p < fc; p++){
                	for (cop = 0; cop < pair_p; cop++){
                        	all_dline.line[pair_h+cop].end = perm_c[p][cop];
                        	}
                	printf ("h = %d, p = %d\n", h, p);
                	if (calc == 1)
				for (i = 0; i < num_lines; i++) 
					print_dline(all_op.op, all_dline.line[i]);

			res_contraction = contract_wick_lines(temp.T, all_dline, all_op, cperm);
			rez = res_contraction.fac;
			if (rez != 0){
				if (calc == 1){
					
					temp.all[counter] = create_empty_contraction_result(num_lines, res_contraction.I.n);

					printf ("Calculating intersection points: %d\n", temp.all[counter].I.n);
					printf ("Number of lines : %d\n", temp.all[counter].dlines.n);
					printf ("Number of delta Kronecker symbols : %d\n", temp.all[counter].deltas.n);
					
					copy_contraction_out(&temp.all[counter], res_contraction);
					}	
				counter++;
				}
			free_contraction_out(&res_contraction);
			cperm++;
			}
		}
	if (calc == 0){
		printf ("counter = %d\n", counter);
		temp.nc = counter;
		temp.ord = ord;
		if (counter > 0){
			temp.all = create_array_of_empty_contractions(counter);
			temp.live = 1;
			}
		else {
			temp.live = 0;
			temp.all = NULL;
			break;
			}
		}
	}

printf ("Permutations of contractions are calculated!\n");

printf ("Nonvanishing permutations of Wick's lines %d/total number of permutations %d\n", counter, fh*fc);;

free(pa);
free(pc);
free(ha);
free(hc);
E2Ds(perm_h);
E2Ds(perm_c);
	
return temp;
}
