#ifndef _READING_H
#define _READING_H

#include "operator.h"

typedef struct{
short aut;
char *hi;//u pravilu to ukljucuje i i1, i2, i3 i sl. kao indekse
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
