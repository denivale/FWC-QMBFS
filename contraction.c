#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "latex.h"
#include "contraction.h"
#include "shalloc.h"
#include "operator.h"
#include "point.h"
#include "line.h"
#include "combinatorics.h"
#include "kronecker.h"
#include "output.h"
//#include "result.h"


static void error_message(char *);
static void pair_test_print(short [], short []);


static void error_message(char *s){
fprintf (stderr, "Error!!!!\n%s\n", s);
exit(2);
}


//static void pair_test_print(short [], short []);
//static int pair_test(operator_t *, int, short *, short *);

static void pair_test_print(short particles[], short holes[]){
printf ("particles:\tcreation - %3.1d, anihilation - %3.1d\n", particles[1], particles[0]);
printf ("holes\tcreation - %3.1d, anihilation - %3.1d\n", holes[1], holes[0]);
return;
}


//Checking number of creation and annihilation operators for particular realization.
int pair_test(operator_t *op, int n, short *pn, short *hn){
register short i;
short holes[2] = {0,0}, particles[2] = {0,0};
short h, p;

if (n % 2 == 1) return 0;

for (i = 0; i < n; i++){
        if (op[i].t == 'h') {
                if (op[i].c == 1) holes[1]++;
                else holes[0]++;
                }
        else if (op[i].t == 'c'){
                if (op[i].c == 1) particles[1]++;
                else particles[0]++;
                }
	h = -holes[1] + holes[0];
	p = -particles[1] + particles[0];
	if (h < 0 || p < 0) return 0;
        }

if (particles[0] != particles[1] || holes[0] != holes[1])
        return 0;

*pn = particles[0];
*hn = holes[0];

return 1;
}


int contract_one_line(operator_t op1, operator_t op2, kronecker_t *temp){

if (op1.t == op2.t){
        if (op1.c == -1 && op2.c == 1 && op1.pos < op2.pos){
                copy_indeks(temp->ind1, op1.ind);
                copy_indeks(temp->ind2, op2.ind);
                }
        else return 0;
        if (op1.t == 'c') temp->fermi = 1;
        else if (op1.t == 'h') temp->fermi = -1;
	else if (op1.t == 'a') temp->fermi = 0; 
        else return 0;
	temp->rez = 1;
        }
else return 0;

return 1;
}


int contract_lines(point_t * T, point_t *I, short *inter, directed_line_t *line, operator_t *op, int n, kronecker_t * delta){
register short i;
short rez, phase = 1; 

for (i = 0; i < n; i++){
        rez = contract_one_line(op[line[i].beg], op[line[i].end], &delta[i]);
        if (rez == 0) return 0;
        }

*inter = calculate_intersections(T, I, line, op, 2*n);

phase = (short)pow(-1, *inter);

return phase;
}



contraction_out_t contract_wick_lines(all_point_t T, all_directed_lines_t all_lines, all_operator_t all_op, int ord){
contraction_out_t temp;
register short i;
short rez, phase = 1, inter;

temp.deltas = create_empty_all_kronecker(all_lines.n);

for (i = 0; i < all_lines.n; i++){
	rez = contract_one_line(all_op.op[all_lines.line[i].beg], all_op.op[all_lines.line[i].end], &temp.deltas.delta[i]);
	if (rez == 0){
		temp.I.n = 0;
		temp.ord = ord;
		temp.I.point = NULL;
		temp.dlines.n = 0;
		temp.dlines.line = NULL;
		
		kronecker_all_free(&temp.deltas);
			
		temp.fac = 0;
		
		return temp;
		}
	}


all_point_t I;
I = create_array_of_empty_points(all_op.n*all_op.n);

if (all_lines.n > 1)
	inter = calculate_intersections(T.point, I.point, all_lines.line, all_op.op, all_op.n);
else 
	inter = 0;


phase = (short)pow(-1, inter);

temp.fac = phase;
temp.ord = ord;

temp.dlines = create_all_empty_directed_lines(all_lines.n);


for (i = 0; i < all_lines.n; i++){
	complete_copy_dline(&temp.dlines.line[i], all_lines.line[i]);
	}

if (inter == 0){
	temp.I.point = NULL;
	temp.I.n = inter;
	}
else {
	temp.I.n = inter;
	temp.I = create_array_of_empty_points(inter);
	for (i = 0; i < temp.I.n; i++){
		complete_copy_point(&temp.I.point[i], I.point[i]);
		}
	}

free_all_points(&I);

return temp;
}


static void find_position_of_all_creation_operators(operator_t *op, int n, short *hc, short *pc){
register short i, coh = 0, cop = 0;
for (i = 0; i < n; i++){
	if (op[i].c == 1){
                if (op[i].t == 'h')
                        hc[coh++] = (short)op[i].pos;
                else if (op[i].t == 'c')
                        pc[cop++] = (short)op[i].pos;
		}
	}
return;
}



directed_line_t * create_beg_of_contraction_lines(int numlines, short * hc, short *pc, short coh){
register int i;
directed_line_t *line;
line = (directed_line_t*) malloc(sizeof(directed_line_t)*numlines);

for (i = 0; i < numlines; i++){
	line[i].num = i;
	if (i < coh){
		line[i].beg = hc[i];
		line[i].t = 'h';
		}
	else {
		line[i].beg = pc[i-coh];
		line[i].t = 'c';
		}
	}

return line;
}


void copy_kronecker_field(kronecker_t * dest, kronecker_t * source, int n){
register int i;
//kronecker_t * dest;

for (i = 0; i < n; i++){
        copy_indeks(dest[i].ind1, source[i].ind1);
        copy_indeks(dest[i].ind2, source[i].ind2);
        dest[i].pos1 = source[i].pos1;
        dest[i].pos2 = source[i].pos2;
//      dest[i].perm = source[i].perm;
//      dest[i].comb = source[i].comb;
        dest[i].rez = source[i].rez;
        dest[i].fermi = source[i].fermi;
        }

return;
}


void test_kronecker(){
kronecker_t * delta, *delta_new;
int i, n = 2;
delta = create_field_kronecker(n);
delta_new = create_field_kronecker(n);


printf (">>>> Testing Kronecker symbols\n");
fill_kronecker(&delta[0], "l1", "l2", 1,2,1,1);
fill_kronecker(&delta[1], "i1", "i2", 1,2,1,1);
copy_kronecker_field(delta_new, delta, n);
for (i = 0; i < n; i++)
	print_kronecker_standard(delta_new[i]);

printf ("printing array:\n");

print_kroencker1D_standard(delta, 1, 2);
printf ("<<<< End of testing Kronecker symbols!\n");

return;
}


void find_indices_of_particular_type_of_operator(operator_t *op, short *stogod, short n, char t, short c, short *count){
register short i, co = 0;
for (i = 0; i < n; i++){
	if (op[i].c == c && op[i].t == t) stogod[co++] = op[i].pos;
	}
*count = co;
return;
}

