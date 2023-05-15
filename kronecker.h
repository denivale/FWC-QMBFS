//========================================================================
/*
D. Vale, N. Paar 
 - created Feb 01 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================



#ifndef _KRONECKER_H
#define _KRONECKER_H

#include "operator.h"
typedef struct{
char ind1[INDEX_SIZE];
char ind2[INDEX_SIZE];
short pos1;
short pos2;
short rez;
short fermi;
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
} kronecker_c_t; 



kronecker_t * create_field_kronecker(int);
kronecker_t ** create_2D_field_kronecker(int, int);
all_kronecker_t create_empty_all_kronecker(int n);


void copy_kronecker_field(kronecker_t *, kronecker_t *, int);
void copy_kronecker_deltas(kronecker_t * dest, kronecker_t * source, int n);
void copy_predfac(predfac_t * temp, predfac_t source);
void copy_all_kronecker_deltas(all_kronecker_t *temp, all_kronecker_t source);

void fill_kronecker(kronecker_t *, char *, char *, short, short, short, short);


void print_kronecker_standard(kronecker_t);
void print_kroencker1D_standard(kronecker_t *, short, int);
void print_all_kronecker_deltas(all_kronecker_t delta);

void kronecker_free(kronecker_t *);
void kronecker_2D_free(kronecker_t **);
void kronecker_all_free(all_kronecker_t *all);

void test_kronecker();

#endif
