#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "point.h"
#include "operator.h"
#include "point.h"
#include "line.h"

#define TEST 1
#define EPS 1.0e-10

static void error_message(char *);
//static void print_coordinates(point_t);


static void error_message(char *s){
fprintf (stderr, "%s\n", s);
exit(3);
}

//==============================================================================================================
// void print_dline(operator_t *op, directed_line_t dline)
// Description:
// Prints the contraction of two operators. The arrow indicates the (directional) contraction of the two operators.
// Input arguments:
// op - a set of operators that is contracted (all, not a pair of operators, operator_t type field)
// dline - directed line - contraction (type directed_line_t)
//==============================================================================================================
void print_dline(operator_t *op, directed_line_t dline){
print_operator(op[dline.beg]);
printf ("----->");
print_operator(op[dline.end]);
printf("\n");
return;
}

//==============================================================================================================
// Function int check_intersections(line_t first, line_t second, point_t *T)
// Description:
// Checks if two lines intersect within the unit circle.
// Input arguments:
// first - line 1 (line_t data type)
// second - line 2 (line_t data type)
// T - address of the intersection point (if it exists, of type point_t *)
// The function returns cut (type int):
// 0 - there is no intersection point that meets the mentioned conditions
// 1 - there is an intersection point that satisfies the mentioned conditions
//==============================================================================================================
int check_intersections(line_t first, line_t second, point_t *T){
register int rez = 0;
register double DS, DX, DY;


DS = first.A*second.B - second.A*first.B;
if (fabs(DS) < EPS) {
        fprintf (stdout, "No intersection!\n");
	return rez;
	}
else {
        DX = first.C*second.B - first.B*second.C;
        DY = -first.C*second.A + first.A*second.C;

        T->x = DX/DS;
        T->y = DY/DS;

	
        if (sqrt(T->x*T->x+T->y*T->y) <= 1.0) {
                rez = 1;
                display_point(*T, "Intersection:");
                }
        else  {
                display_point(*T, "Intersection is not inside of the unit circle:");
                return 0;
                }
        }
return rez;
}

#undef TEST
#undef EPS


void display_explicit_form_line(line_t line, char *s){
fprintf (stdout, "line %s:\t%lf x + %lf y + %lf = 0.0\n", s , line.A, line.B, -line.C);
return;
}


//=============================================================================================================
// Function line_t get_coefficients_of_line(point_t t1, point_t t2)
// Description:
// Determining the explicit equation of the line Ax + By = C based on
// point t1 and t2
// Input arguments:
// t1 - first point (type point_t)
// t2 - second point (type point_t)
// The function returns a line (type line_t) that contains the coefficient:
// A, B, C - coefficients of explicit form
//=============================================================================================================
line_t get_coeficients_of_line(point_t t1, point_t t2){
line_t temp;
temp.A = t1.y-t2.y;
temp.B = t2.x-t1.x;
temp.C = t1.y*(t2.x-t1.x) - (t2.y-t1.y)*t1.x;
return temp;
}


void test_paralelne_linije(){
point_t t1[2], t2[2];
t1[0].x = 1.00; t1[0].y = 2.00;
t2[0].x = 3.00; t2[0].y = 4.00;

t1[1].x = 1.00; t1[1].y = 3.00;
t2[1].x = 3.00; t2[1].y = 5.00;

line_t l1;
line_t l2;

l1 = get_coeficients_of_line(t1[0], t2[0]);
l2 = get_coeficients_of_line(t1[1], t2[1]);

display_explicit_form_line(l1, "l1");
display_explicit_form_line(l2, "l1");

point_t T;

check_intersections(l1, l2, &T);

}

void test_opce_linije(){
point_t t1[2], t2[2];
t1[0].x = 1.00; t1[0].y = 2.00;
t2[0].x = 3.00; t2[0].y = 8.00;

t1[1].x = 1.00; t1[1].y = 3.00;
t2[1].x = 3.00; t2[1].y = 5.00;

line_t l1;
line_t l2;

l1 = get_coeficients_of_line(t1[0], t2[0]);
l2 = get_coeficients_of_line(t1[1], t2[1]);

display_explicit_form_line(l1, "l1");
display_explicit_form_line(l2, "l1");

point_t T;

check_intersections(l1, l2, &T);

}


void test_intersections(){
printf ("Testing intersections...\n");
printf ("Parallel lines:\n");
test_paralelne_linije();
printf ("General case:\n");
test_opce_linije();
printf ("....end of testing!\n");
return;
}


directed_line_t * create_empty_directed_lines(int n){
directed_line_t * temp;

if (n <= 0) error_message("Number of directed lines is less or equal 0!\n");

temp = (directed_line_t*)malloc(sizeof(directed_line_t)*n);
if (temp == NULL) 
    error_message("Creation of the array of empty directed lines failed!\n");

return temp;
}



all_directed_lines_t create_all_empty_directed_lines(int n){
all_directed_lines_t temp;

if (n < 0) error_message("Number of directed lines is less or equal 0!\n");

if (n == 0){
	temp.n = 0;
	temp.line = NULL;
	return temp;
	}

temp.line = create_empty_directed_lines(n);
temp.n = n;

if (temp.line == NULL) error_message("Creation of the array of empty directed lines failed!\n");

return temp;
}


line_t * create_empty_lines(int n){
line_t * temp;
temp = (line_t*)malloc(sizeof(line_t)*n);
if (temp == NULL) error_message("line -> NULL");

return temp;
}


all_lines_t create_all_empty_lines(int n){
all_lines_t temp;

if (n <= 0) error_message("Number of lines is less or equal 0!\n");

temp.line = create_empty_lines(n);

if (temp.line == NULL)
	error_message("Creation of the array of empty lines failed!\n");

return temp;
}


//============================================================================================================
// Func. calculate_intersections(point_t * T, point_t * I, directed_line_t *dline, operator_t *op, int n)
// Description:
// The function calculates the total number of intersections of directed lines (vectors) representing contractions of two
// operator. Based on the position of the operator at the vertices of a regular n-terrigon and directed lines which
// connect pairs of operators, the function first determines the line equation for each contracted pair (1st loop).
// Then tests if there is an intersection of any two contraction lines within the unit circle which
// describes a regular n-teragon. If there is an intersection that meets the mentioned conditions, it is saved
// points of corresponding intersection (2nd loop).
// Input arguments:
//  T - address of the array of points representing operators in a regular polygon or equidistant points on unit
//      circle (type point_t*)
//  length - a directed line that connects only the indices (order no.) of the operators that are contracted
//  op - field address of all operators participating in contractions (field of type operator_t)
//  n - total number of operators we contract
//  I - field address of line intersection points
// The function returns the total number of intersections:
//  0 - no intersection of lines within the unit circle
//  >0 - there is an intersection that satisfies the mentioned condition
//
//============================================================================================================
int calculate_intersections(point_t * T, point_t * I, directed_line_t *dline, operator_t *op, int n){
int i, j, num = 0;
char buffer[50];
line_t * line;
point_t Itemp;


line = create_empty_lines(n/2);

for (i = 0; i < n/2; i++){
        line[i] = get_coeficients_of_line(T[dline[i].beg], T[dline[i].end]);
        sprintf (buffer, "%.1d.", i);
        display_explicit_form_line(line[i], buffer);
        }

for (i = 0; i < n/2; i++){
        for (j = i+1; j < n/2; j++){
                
                if (check_intersections(line[i], line[j], &Itemp) == 1){
			coordinate_copy_point(&I[num], Itemp);
			num++;
			}
                }
        }
printf ("Total minimal number of intersections: %d\n", num);
free(line);
return num;
}


void complete_copy_dline(directed_line_t * fin, directed_line_t in){
fin->beg = in.beg;
fin->end = in.end;
fin->t = in.t;
fin->num = in.num;

return;
}


void copy_all_dlines(all_directed_lines_t *dest, all_directed_lines_t source){
int i;
if (dest->n != source.n)
	error_message("Error copying directed lines, different number of directed lines!\n");

for (i = 0; i < source.n; i++)
	complete_copy_dline(&dest->line[i], source.line[i]);

return;
}




void free_all_directed_lines(all_directed_lines_t *temp){

if (temp->n == 0) return;

free(temp->line);
temp->n = 0;

return;
}
