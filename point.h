//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 25 2019
 - last modification May 21 2023 (D. Vale)
*/
//========================================================================

#ifndef _POINT_H
#define _POINT_H


#include "operator.h"



typedef struct{
double x, y;
short pos;
char name[30];
//char ind[3];
} point_t;

typedef struct{
point_t *point;
int n;
} all_point_t;

all_point_t create_array_of_empty_points(int n);
all_point_t create_all_operator_points(all_operator_t ops);

point_t * create_operator_points(int, operator_t *);
point_t * create_empty_points(int);


void display_point(point_t, char *);
void display_points(point_t *, int);
void display_all_points(all_point_t points);

void coordinate_copy_point(point_t *, point_t);
void complete_copy_point(point_t *, point_t);
void copy_all_points(all_point_t *temp, all_point_t source);
point_t duplicate_point(point_t T);
all_point_t duplicate_all_points(all_point_t all);


void free_all_points(all_point_t *temp);

void test_point();
void test_copy_point();
void test_n_poligon(int, operator_t*);

#endif
