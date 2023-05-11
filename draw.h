#ifndef _DRAW_H
#define _DRAW_H

#include "operator.h"
#include "point.h"
#include "line.h"
#include "combinatorics.h"
//#include "contraction.h"

typedef struct{
char infopart[80];
short p;
short c;
short show;
short draw;
short prepair;
char program_name[80];
} info_draw_t;

typedef struct{
point_t *T;
//line_t *line;
directed_line_t *dline;
point_t *I; //intersection points;
int n; //number of points
int i; //number of intersection points
} drawing_data_t;

typedef struct{
double x1, x2, y1, y2;
double r, s, s2;//postavi kao 0.0!!!!!!!!!!!!!!!!!!!!!!!!!!!!
double size;
int offset;//postavi kao 1
char point_f[80]; FILE *PF;
char gplot_f[80]; FILE *GP;
char vector_f[80]; FILE *VF;
char inter_f[80]; FILE *IF;//ako eventualno budem crtao file
char output[80];
char ps_f[80];
char dvi_f[80];
char pdf_f[80];
char eps_f[80];
char folder_name[80];
char rep_part[80];
short test;
short sd; //skip drawing due to 0 or odd num of operators 
short si; //skip intersection points
//short test = 0;
} gp_t;//ovo nuzno ne mora odgovarati standalone file-u

void fill_drawing_data(drawing_data_t *, int n, int inter, point_t * T, directed_line_t *dline, point_t * I);
void test_gnuplot_file_print();
void draw_sa_file(info_draw_t, drawing_data_t);


void fill_drawing_data(drawing_data_t *, int, int, point_t *, directed_line_t *, point_t *);
void fill_drawing_info(info_draw_t *, char, char, char, char *);

void free_drawing_data(drawing_data_t *);

#endif
