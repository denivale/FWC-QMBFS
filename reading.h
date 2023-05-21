//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 25 2019
 - last modification May 21 2023 (D. Vale)
*/
//========================================================================

#ifndef _READING_H
#define _READING_H

#include "operator.h"

typedef struct{
short aut;
char *hi;
short hin;
char *pi;
short pin;
char pvr, dvr, svr;
char pld, wld, sld;
char program_name[80];
} paramet_t;

typedef struct{
char type;
char *filename;
} option_t;


void read_parameters(option_t opt, paramet_t *par);
void test_reading_parameters();


#endif
