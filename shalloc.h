//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 25 2019
 - last modification May 21 2023 (D. Vale)
*/
//========================================================================
#ifndef _SHALLOC_H
#define _SHALLOC_H

typedef struct{
short * v;
int n;
} _1D_short_t;//vector (1d array)

short * _1Ds(int);
short ** _2Ds(int, int);
short ** _2Ds_adjustable(int, int *);
void test_shalloc();
void E1Ds(short *);
void E2Ds(short **);


#endif
