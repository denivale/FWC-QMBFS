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

#include "canonical.h"
#include "combinatorics.h"
#include "contraction.h"
#include "shalloc.h"

short count_general_operators(operator_t *, int);
static short * create_change_field(operator_t *, int, int);
static void png(short);
static void error_message(char *);
static void fill_all_combinations_of_operators(operator_t **, operator_t *, short*,  short**, int, int);

static void error_message(char *s){
fprintf (stderr, "%s\n", s);
exit(1);
}


short count_general_operators(operator_t *op, int n){
register short i, count;
count = 0;
for (i = 0; i < n; i++){
	if (op[i].t == 'a') count++;
	}
return count;
}



short count_general_in_all_operators(all_operator_t all){
return count_general_operators(all.op, all.n);
}

static short * create_change_field(operator_t *op, int n, int ngo){
register short i, j = 0;
short * temp;
temp = _1Ds(ngo); //ngp - number of general operators
for (i = 0; i < n; i++){
        if (op[i].t == 'a') temp[j++] = op[i].c;
	if (j > ngo) error_message("j > ngp!");
        }
return temp;
}



cf_t create_and_fill_change_field(all_operator_t all){
cf_t temp;
short counter;

counter = count_general_operators(all.op, all.n);

if (counter == 0) temp.cf = NULL;
else
	temp.cf = create_change_field(all.op, all.n, (int)counter);

temp.n = counter;

return temp;
}


static void png(short count){
printf ("Transformation needed for %d operators\n", count);
return;
}


void free_cf(cf_t *temp){

free(temp->cf);

temp->n = 0;
return;
}


static void print_all_combinations(short **comb_field, int ngo, int comb){
register short i, j;
printf ("Printing combinations...\n");
for (j = 0; j < comb; j++){
        for (i = 0; i < ngo; i++){
                printf ("%4.1d", comb_field[i][j]);
                }
        printf ("\n");
        }
printf ("... done!!!\n");
return;
}




static void fill_all_combinations_of_operators(operator_t **temp, operator_t *op, short *change, short** comb_field, int nmax, int comb){

register short i, j, count;
register char c;

for (i = 0; i < nmax; i++){
        for (j = 0; j < comb; j++)
                temp[j][i] = copy_operator(op[i]);
        if (op[i].t == 'a') {
                for (j = 0; j < comb; j++){
                        if (change[count] == 1) {
                                c = temp[j][i].c = comb_field[count][j];
                                if (c == 1) temp[j][i].t = 'c';
                                else temp[j][i].t = 'h';
                                }
                        else
                                {
                                c = temp[j][i].c = comb_field[count][j];
                                if (c == -1) temp[j][i].t = 'c';
                                else temp[j][i].t = 'h';
                                }
                        }
		count++;
                }

	}

for (i = 0; i < comb; i++)
        print_operator_series(temp[i], nmax);

return;
}


all_comb_of_operator_t prepair_combinations(all_operator_t all_op){
all_comb_of_operator_t temp;
cf_t cf;
cf2_t comb_field;
int i, j, cn;
char t;
short c, count;

cf = create_and_fill_change_field(all_op);

cn = (int)pow(2, cf.n);

printf ("Creating empty array of all combinations....\n");
temp = create_all_comb_of_empty_operators(cn, all_op.n);
printf ("... created!\n");

printf ("Creating and filling all possible alternations of creation and annihilation operators!...\n");
comb_field = create_and_fill_alternation_of_pm_one(cf);
printf ("... created!\n");

count = 0;

for (i = 0; i < all_op.n; i++){
        for (j = 0; j < cn; j++)
                copy_operator2(&temp.all[j].op[i], all_op.op[i]);
        
	if (all_op.op[i].t == 'a') {
                for (j = 0; j < cn; j++){
			c = comb_field.cf[count][j];
                        
			if (cf.cf[count] == 1) {
				if (c == 1) t = 'c';
				else t = 'h';
                                }
                        else
                                {
                                if (c == -1) t = 'c';
                                else t = 'h';
                                }
			
			fill_operator(&temp.all[j].op[i], t, c, all_op.op[i].ind);
                        }
                count++;
                }
        }

print_all_comb_of_operator(temp);

free_cf2(&comb_field);

free_cf(&cf);

printf (".... created all combinations which correspond to canonical transformation of operators!\n");

return temp;
}

