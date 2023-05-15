//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 24 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#include "operator.h"
#include "calc_wick.h"
#include "combinatorics.h"
#include "canonical.h"
#include "contraction.h"
#include "draw.h"
#include "latex.h"
#include "full_contraction.h"
#include "line.h"
#include "kronecker.h"

//========================================================================
/*
 Calculates all possible combinations of complete Wicks
 contraction, and depending on the option writes the result to standard
 input, tex document or provides graphical interpretation.
 Input arguments:
    prep - prepared input with options (prep_t)
    count - number of general operators
 Exit:
    0 - successfully executed
    0< - executed unsuccessfully 
*/
//========================================================================
int calculate_all_comb_of_wick_contraction(prep_t prep, short count){
all_comb_of_operator_t all_comb;
all_operator_t temp_op, all_op;
int i, j, tc;
short nonzero, exist;
all_comb_of_contractions_out_t contractions;
all_contractions_out_t one;
contraction_out_t out;
all_kronecker_t delta;
all_directed_lines_t dlines;
all_point_t T, I;
drawing_data_t drawing_data;
info_draw_t info;
latex_info_t lat;
int calc, faza;
int nzc, nzp, nzd;
int none;
info = prep.draw;
lat = prep.lat;

all_op = prep.in.all_op;

tc = (int)pow(2, count);

if (tc > 1)
	simplew = 0;
else simplew = 1;

printf ("Calculating of possible combinations if exist...\n");
contractions = create_all_empty_combinations_of_contractions(tc);

all_comb = prepair_combinations(all_op);


printf ("All combinations are ready!\n");

if (lat.prepair == 1){
	latex_prepair_operators(&latex_data_init, all_op.op, all_op.n);
	}

nzc = 0; 
nzp = 0;
nzd = 0;

none = 0;
for (i = 0; i < tc; i++){
        printf("============%.1d COMBINATION =============\n", i);
	temp_op	 = all_comb.all[i];
	printf ("Canonical transformation of the form:\n");
        //print_all_operator(temp_op);

	contractions.comb[i] = fwcoc(temp_op, i);

	one = contractions.comb[i];
	
	exist = one.live;

	print_all_operator(temp_op);

	if (exist != 0){
		none++;
		nzc++;
		nzp += one.nc;
		printf ("one.nc = %d\n", one.nc);
		for (j = 0; j < one.nc; j++){
			out = one.all[j];
			faza = out.fac;
			delta = out.deltas;
			if (faza == -1) printf ("(-1)");
			print_all_kronecker_deltas(delta);
			if (j+1 != one.nc) printf ("+");
			}
		}
	else
	printf (" = 0 \n");
	}

if (none == 0)// ukoliko ne preživljava ni za jednu kanonsku transformaciju
	printf (" = 0 (vanishing)!\n");

nzd = nzp*all_op.n/2;

if (lat.prepair == 1){
	if (nzc != 0)
		latex_initialize_arrays_and_counters(nzc, nzp, nzd);
	else 
		lat_zero = 1;
	}

//latex i vizualni output
for (i = 0; i < tc; i++){

	temp_op  = all_comb.all[i];

	one = contractions.comb[i];

        exist = one.live;

        if (exist != 0){
		T = one.T;
		if (lat.prepair == 1 && tc > 1)
                	latex_prepair_operators(&latex_data_c[lat_c++], temp_op.op, all_op.n);
		
		for (j = 0; j < one.nc; j++){
			out = one.all[j];
			I = out.I;
			delta = out.deltas;
			dlines = out.dlines;

			if (lat.prepair == 1){
                		latex_prepair_contractions(&latex_data_p[lat_p++], dlines.line, temp_op.op, i, out.ord, all_op.n);
				latex_prepair_kronecker(&latex_delta[lat_d++], delta.delta, delta.n, out.fac);
				}

			if (info.prepair == 1){
				info.c = i;
				info.p = j;
				fill_drawing_data(&drawing_data, all_op.n, I.n, T.point, dlines.line, I.point);
				draw_sa_file(info, drawing_data);
				free_drawing_data(&drawing_data);
				}

			}
		}
	}    



printf ("lat.prepair = %d\n", lat.prepair);
printf ("lat.create = %d\n", lat.create);
printf ("lat.show = %d\n", lat.show);

if (lat.prepair == 1)
	latex_print(&lat);

if (lat.create == 1 || lat.create == 2)
	create_pdf_from_latex_file(&lat);

if (lat.prepair != 0)
	latex_kill();

free_all_comb_of_contractions_out(&contractions);

free_all_comb_of_operator(&all_comb);

return 0;
}

