//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 25 2019
 - last modification May 11 2023 (D. Vale)
*/
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "point.h"
#include "operator.h"


void test_n_poligon(int n, operator_t *op){
point_t *T;
T = create_operator_points(n, op);
display_points(T, n);
free(T);
return;
}


void test_point(){
int i, n = 12;
char buffer[10];
operator_t *op;

printf ("Testing fun test_point()\n");
op = create_operators(n);
for (i = 0; i < n; i++){
        if (i < n/2) {
                sprintf(buffer, "%c%d", 'm', i+1);
                fill_operator(&op[i], 'c', (short)pow(-1,i), buffer);
                }
        else {
                sprintf(buffer, "%c%d", 'i', i+1-n/2);
                fill_operator(&op[i], 'h', (short)pow(-1,i), buffer);
                }
        }
printf("Array of operators:\n");
print_operator_series(op, n);
printf ("Calling fun test_n_poligon:\n");
test_n_poligon(n, op);
printf ("end of testing fun test_point()\n");
return;
}

void test_copy_point(){
point_t t1,t2;
t1.x = 0.1;
t1.y = 1.2;
printf ("Test copy_point()...\n");
coordinate_copy_point(&t2, t1);
printf ("%lf\t%lf\n", t2.x, t2.y);
printf ("...end of testing\n");
return;
}


int main(){

return 0;
}
