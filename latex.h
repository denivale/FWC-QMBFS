//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 22 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#ifndef _LATEX_H
#define _LATEX_H

#include "operator.h"
#include "contraction.h"
#include "reading.h"

typedef struct{
char latex_f[80]; FILE *LF;
char pdf_f[80]; FILE *PF;

short prepair;
short create;
short show;
char opt;//append, new
char program_name[80];
} latex_info_t;

typedef struct{
short *beg, *end;

short p;//info
short c;//info
int n; //broj operatora
short exist;
operator_t *op;
} latex_data2_t;

typedef struct{
operator_t *op;
int n;
} latex_data3_t;

typedef struct{
kronecker_t *delta;
int faza;
int n;//on je n/2 operatora
} latex_data4_t;

extern int lat_c;
extern int lat_p;
extern int lat_d;
extern latex_data3_t *latex_data_c;
extern latex_data2_t *latex_data_p;
extern latex_data3_t latex_data_init;
extern latex_data4_t *latex_delta;
extern short simplew;
extern short lat_zero;
void test_pure_operators_latex();

void prepair_latex_headers(latex_info_t *);

void latex_fill_info(latex_info_t *info, char pld, char wld, char sld, char * program_name);
void latex_initialize_arrays_and_counters(int nc, int np, int nd);

void latex_prepair_contractions(latex_data2_t *data, directed_line_t *dline, operator_t *op, short c, short p, int n);
void latex_prepair_kronecker(latex_data4_t *, kronecker_t *, int, int);
void latex_change_index(char *, char *);
void latex_print_kronecker(latex_info_t *, latex_data4_t);
void print_contractions(latex_info_t *, latex_data2_t, short);
void print_pure_operators(latex_info_t *, latex_data3_t, short);
void latex_prepair_operators(latex_data3_t *, operator_t *, int);
void test_pure_operators_latex();


void free_latex_data4_t(latex_data4_t *, int);
void free_latex_data3_t(latex_data3_t *, int);
void free_latex_data2_t(latex_data2_t *, int);



void latex_print();


void create_pdf_from_latex_file(latex_info_t *lat);




void latex_reset_counters();
void latex_initialize();

void latex_kill();


#endif
