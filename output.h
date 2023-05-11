#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "point.h"
#include "kronecker.h"
#include "line.h"


typedef struct{
all_point_t I;
all_kronecker_t deltas;
all_directed_lines_t dlines;
int fac;
int ord;//permutacije
} contraction_out_t;

typedef struct{
contraction_out_t *all;
all_point_t T;
int nc;// broj kontrakcija//ukupan broj permutacija
int live;//0,1
int ord;//kombinacije
} all_contractions_out_t;

typedef struct{
all_contractions_out_t *comb;
int nc;
} all_comb_of_contractions_out_t;

contraction_out_t create_empty_contraction_result(int num_lines, int num_point);
contraction_out_t * create_array_of_empty_contractions(int n);
all_comb_of_contractions_out_t create_all_empty_combinations_of_contractions(int nc);

void set_contraction_out(contraction_out_t *dest, contraction_out_t source);

void copy_contraction_out(contraction_out_t *temp, contraction_out_t source);


//oslobađanje memorije
void free_contraction_out(contraction_out_t *temp);
void free_all_contractions_out(all_contractions_out_t *temp);
void free_all_comb_of_contractions_out(all_comb_of_contractions_out_t *temp);

#endif
