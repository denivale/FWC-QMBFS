#ifndef _CONTRACTION_H
#define _CONTRACTION_H

#include "operator.h"
#include "point.h"
#include "line.h"
#include "draw.h"
#include "output.h"
#include "kronecker.h"

/*
typedef struct{
char ind1[INDEX_SIZE];
char ind2[INDEX_SIZE];
short pos1;//-1 -> pozicija me ne zanima
short pos2;
//short perm = -1;//informacija o permutaciji (bitno za crtanje)
//short comb = -1;//informacija o kombinaciji -1 -> ne zanima me
short rez;//0,1 Pretpostavimo i nulu kao mogucnost
short fermi;//-1 ispod, 1 iznad Fermijevog, 0 sve mogucnosti (za neki generalni operator iako me trenutno to ne interesira. Ipak ostavljam kao jednu od mogucnosti)
} kronecker_t;

typedef struct{
int rez;
} predfac_t;

typedef struct{
kronecker_t *delta;
int n;
predfac_t predfac;
} all_kronecker_t;

typedef struct{
kronecker_t **delta;
short comb;
} kronecker_c_t; //kombinacije
*/

void find_indices_of_particular_type_of_operator(operator_t *op, short *stogod, short n, char t, short c, short *count);

int full_contract_one(operator_t *op, int n, short comb_order, short *nonzero_deltas, info_draw_t*);

//stvaranje polja Kroneckerovih simbola
//kronecker_t * create_field_kronecker(int);
//kronecker_t ** create_2D_field_kronecker(int, int);

//kopiranje polja Kroneckerovih simbola
//kronecker_t * copy_kronecker_field(kronecker_t *, int);
//void copy_kronecker_field(kronecker_t *, kronecker_t *, int);


//fill kronecker
//void fill_kronecker(kronecker_t *, char *, char *, short, short, short, short);

//print kronecker
//void print_kronecker_standard(kronecker_t);
//void print_kroencker1D_standard(kronecker_t *, short, int);


//Testiranje broja parova operatora i kontrakcije
int pair_test(operator_t *, int, short *, short *);
int contract_one_line(operator_t, operator_t, kronecker_t *);
int contract_lines(point_t *, point_t *, short *, directed_line_t *, operator_t *, int, kronecker_t *);

contraction_out_t contract_wick_lines(all_point_t T, all_directed_lines_t all_lines, all_operator_t all_op, int ord);
directed_line_t * create_beg_of_contraction_lines(int numlines, short * hc, short *pc, short coh);
//brisanje polja Kroneckerovih simbola
//void kronecker_free(kronecker_t *);
//void kronecker_2D_free(kronecker_t **);


//testovi
//void test_kronecker();
#endif
