#ifndef _KRONECKER_H
#define _KRONECKER_H

#include "operator.h"
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


//stvaranje polja Kroneckerovih simbola
kronecker_t * create_field_kronecker(int);
kronecker_t ** create_2D_field_kronecker(int, int);
all_kronecker_t create_empty_all_kronecker(int n);

//kopiranje polja Kroneckerovih simbola
//kronecker_t * copy_kronecker_field(kronecker_t *, int);
void copy_kronecker_field(kronecker_t *, kronecker_t *, int);
void copy_kronecker_deltas(kronecker_t * dest, kronecker_t * source, int n);
void copy_predfac(predfac_t * temp, predfac_t source);
void copy_all_kronecker_deltas(all_kronecker_t *temp, all_kronecker_t source);

//fill kronecker
void fill_kronecker(kronecker_t *, char *, char *, short, short, short, short);

//print kronecker
void print_kronecker_standard(kronecker_t);
void print_kroencker1D_standard(kronecker_t *, short, int);
void print_all_kronecker_deltas(all_kronecker_t delta);

//brisanje polja Kroneckerovih simbola
void kronecker_free(kronecker_t *);
void kronecker_2D_free(kronecker_t **);
void kronecker_all_free(all_kronecker_t *all);

//testovi
void test_kronecker();

#endif
