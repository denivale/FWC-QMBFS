#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "operator.h"
#include "point.h"

static void error_message(char *);

static void error_message(char *s){
fprintf (stderr, "%s\n", s);
exit(3);
}


void display_point(point_t T, char *s){
fprintf(stdout, "%s", s);
fprintf(stdout, "T.x = %lf\tT.y = %lf\n",T.x, T.y);
return;
}



void display_points(point_t *T, int n){
register int i;
for (i = 0; i < n; i++)
fprintf (stdout, "%s.x = %lf\t%s.y = %lf\n", T[i].name, T[i].x, T[i].name, T[i].y);
return;
}


void display_all_points(all_point_t points){
display_points(points.point, points.n);
return;
}

//=========================================================================================
// Function create_operator_points()
// Description:
// The function creates an array of points associated with a set of operators, so that
// each point on unit circle (or of a regular n-polygone) is associated with a certain 
// operator which later contract. The order of points is fixed by selecting the starting point
// point - vertex that corresponds to the first operator in the array, while the rest
// points in order we join the remaining operators in the array moving in
// mathematically positive direction. Choosing the starting point is arbitrary. The same 
// is true for the choice of direction.
// Input arguments:
// n - number of operators (int)
// op - operator field address (operator_t *)
// Exit:
// The function returns the address of the created array of points.
//=========================================================================================
point_t * create_operator_points(int n, operator_t *op){
point_t *T;
char *s = "\\\\dagger";
register int i;

//Ako nemamo bar dvije točke, onda nemamo ni kontrakcije
if (n < 2) error_message("Number of points < 2! Stopping calculation!\n");

T = (point_t*) malloc(sizeof(point_t)*n);
if (T == NULL)
	error_message("Creation of the array of empty points failed!\n");

for (i = 0; i < n; i++){
        T[i].x = cos(i*2.0*M_PI/n+M_PI/6.0);
        T[i].y = sin(i*2.0*M_PI/n+M_PI/6.0);
        
	if (op[i].c == 1) {
                sprintf (T[i].name, "%c^{%s}_{%s}", op[i].t, s, op[i].ind);
                }
        else
                sprintf (T[i].name, "%c_{%s}", op[i].t, op[i].ind);
        }

return T;
}


all_point_t create_all_operator_points(all_operator_t ops){
all_point_t temp;

if (ops.n <= 0)
	error_message("Broj tocaka je 0 ili manji od 0!\n");

temp.n = ops.n;

temp.point = create_operator_points(ops.n, ops.op);
if (temp.point == NULL)
	error_message("Neuspjela alokacija polja tocaka!\n");

return temp;
}


void coordinate_copy_point(point_t *P, point_t T){
P->x = T.x;
P->y = T.y;
return;
}


void complete_copy_point(point_t *P, point_t T){
P->x = T.x;
P->y = T.y;
strcpy(P->name, T.name);
return;
}

void copy_all_points(all_point_t *temp, all_point_t source){
int i;
if (temp->n == source.n && source.n == 0) return;

if (temp->n != source.n)
	error_message("Nemoguće kopirati! Dimenzije polja tocaka nisu iste!\n");


for (i = 0; i < source.n; i++){
	complete_copy_point(&temp->point[i], source.point[i]);
	}

return;
}


point_t duplicate_point(point_t T){
point_t temp;

temp.x = T.x;
temp.y = T.y;

strcpy(temp.name, T.name);

return temp;
}



all_point_t duplicate_all_points(all_point_t all){
all_point_t temp;
int i;

temp = create_array_of_empty_points(all.n);
	

for (i = 0; i < temp.n; i++)
	temp.point[i] = duplicate_point(all.point[i]);

return temp;
}


point_t * create_empty_points(int n){
point_t * temp;

if (n < 0) 
	error_message("point : n < 0!\n");

if (n == 0){
	temp = NULL;
	return temp;
	}

temp = (point_t*) malloc(sizeof(point_t)*n);

if (temp == NULL) 
	error_message("point -> NULL\n");

return temp;
}


all_point_t create_array_of_empty_points(int n){
all_point_t temp;

if (n < 0) error_message("Number of points is less than 0!\n");

if (n == 0){
	temp.point = NULL;
	temp.n = 0;
	return temp;
	}

temp.n = n;

temp.point = create_empty_points(n);

if (n > 0 && temp.point == NULL) 
	error_message("Creation of array of empty foints failed!\n");

return temp;
}



void free_all_points(all_point_t *temp){

if (temp->n == 0) return;

free(temp->point);
temp->point = NULL;
temp->n = 0;

return;
}

