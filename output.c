#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "kronecker.h"
#include "point.h"
#include "output.h"

static void error_message(char *);


static void error_message(char *s){
fprintf (stderr, "Error!!!!\n%s\n", s);
exit(2);
}

//Fale dlinije!!!!
contraction_out_t create_empty_contraction_result(int num_lines, int num_point){
contraction_out_t temp;

temp.deltas = create_empty_all_kronecker(num_lines);

//printf ("broj tocaka u create_contraction = %d\n", num_point);

temp.I = create_array_of_empty_points(num_point);

//printf ("broj tocaka u create_contraction, podatak I.n = %d\n",temp.I.n); 

temp.dlines = create_all_empty_directed_lines(num_lines);

temp.fac = 0;

temp.ord = -1;

return temp;
}


contraction_out_t * create_array_of_empty_contractions(int n){
contraction_out_t * temp;

if (n <= 0) 
	error_message("Total number of contraciton is less or equal to 0!\n");
temp = (contraction_out_t*)malloc(sizeof(contraction_out_t)*n);

return temp;
}


void copy_contraction_out(contraction_out_t *temp, contraction_out_t source){

//printf ("Kopiram tocke, dim1 = %d, dim2 = %d\n", temp->I.n, source.I.n);
copy_all_points(&temp->I, source.I);

copy_all_kronecker_deltas(&temp->deltas, source.deltas);

copy_all_dlines(&temp->dlines, source.dlines);

temp->fac = source.fac;

temp->ord = source.ord;


return;
}

//set_contraction
void set_contraction_out(contraction_out_t *dest, contraction_out_t source){

dest->fac = source.fac;
dest->ord = source.ord;

dest->I = create_array_of_empty_points(source.I.n);

copy_all_points(&dest->I, source.I);



return;
}


void free_contraction_out(contraction_out_t *temp){

if (temp->fac == 0) return;

free_all_directed_lines(&temp->dlines);

free_all_points(&temp->I);

kronecker_all_free(&temp->deltas);

temp->fac = 0;
temp->ord = -1;

return;
}


void free_all_contractions_out(all_contractions_out_t *temp){
int i;

if (temp->live == 0){
	temp->nc = 0;
	temp->live = 0;
	temp->ord = -1;
	return;
	}

for (i = 0; i < temp->nc; i++){
	printf ("Cleaning permutation: %d/%d\n", i, temp->nc);
	free_contraction_out(&temp->all[i]);

	}

if (temp->nc > 0) free(temp->all);
//sleep(1);

if (temp->T.n > 0) free_all_points(&temp->T);

temp->nc = 0;
temp->live = 0;
temp->ord = -1;
return;
}

all_comb_of_contractions_out_t create_all_empty_combinations_of_contractions(int nc){
all_comb_of_contractions_out_t temp;

if (nc <= 0)
	error_message("Dimension of combinations is less than 1!\n");

temp.comb = (all_contractions_out_t*)malloc(sizeof(all_contractions_out_t)*nc);

temp.nc = nc;

return temp;
}


void free_all_comb_of_contractions_out(all_comb_of_contractions_out_t *temp){
int i;
printf ("Cleaning memory for all combinations....\n");
for (i = 0; i < temp->nc; i++){
	printf ("cleaning memory for canonical transformation : %d/%d\n", i, temp->nc);
	free_all_contractions_out(&temp->comb[i]);

	}

if (temp->nc > 0) free(temp->comb);

temp->nc = 0;
printf (".... done!\n");
return;
}
