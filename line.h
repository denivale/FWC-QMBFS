//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 23 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#ifndef _LINE_H
#define _LINE_H

#include "point.h"

typedef struct{
short beg, end;//index
char t;//c or h, eventaully a
short num;
} directed_line_t;

typedef struct{
directed_line_t *line;
int n;
} all_directed_lines_t;

typedef struct{
double A, B, C; //coefficients in explicit form of line equation
} line_t;

typedef struct{
line_t *line;
int n;
} all_lines_t;


all_lines_t create_all_empty_lines(int n);
all_directed_lines_t create_all_empty_directed_lines(int n);

line_t * create_empty_lines(int);
directed_line_t * create_empty_directed_lines(int);


int calculate_intersections(point_t *, point_t *, directed_line_t *, operator_t *, int);



int check_intersections(line_t, line_t, point_t *);
void display_explicit_form_line(line_t, char *);

line_t get_coeficients_of_line(point_t, point_t);

void test_intersections();
void print_dline(operator_t *op, directed_line_t dline);


void complete_copy_dline(directed_line_t *, directed_line_t);
void copy_all_dlines(all_directed_lines_t *dest, all_directed_lines_t source);


void free_all_directed_lines(all_directed_lines_t *temp);

#endif
