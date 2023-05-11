#ifndef _COMBINATORICS_H
#define _COMBINATORICS_H

//Deklaracija i definicija struktura:
typedef struct{
short * cf;
int n;
} cf_t;

typedef struct{
short **cf;
int n;
} cf2_t;

//Deklaracije funkcija
extern int factoriel(int);
extern long int lfactoriel(int);

extern short **create_field_of_combinations(short *, short);

extern cf2_t create_and_fill_alternation_of_pm_one(cf_t);

extern void reset_counter();
extern void get_all_permutations(short *, int, int, int, short**);

extern void free_cf2(cf2_t *);

#endif
