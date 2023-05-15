//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 24 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#ifndef _COMBINATORICS_H
#define _COMBINATORICS_H

typedef struct{
short * cf;
int n;
} cf_t;

typedef struct{
short **cf;
int n;
} cf2_t;

extern int factoriel(int);
extern long int lfactoriel(int);

extern short **create_field_of_combinations(short *, short);

extern cf2_t create_and_fill_alternation_of_pm_one(cf_t);

extern void reset_counter();
extern void get_all_permutations(short *, int, int, int, short**);

extern void free_cf2(cf2_t *);

#endif
