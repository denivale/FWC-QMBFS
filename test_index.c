#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"
#include "reading.h"
#include "transindex.h"
#include "shalloc.h"


void test_transformation(){
operator_t * op;
int n_op = 6, t;
op = create_operators(n_op);


printf (">>>> Testing transformations...\n");
option_t opt;
paramet_t par;
opt.type = 2;
read_parameters(opt, &par);


op[0].t = 'a'; op[0].c = 1; sprintf(op[0].ind,"l1");
op[1].t = 'a'; op[0].c = -1; sprintf(op[1].ind,"m");
op[2].t = 'a'; op[2].c = 1; sprintf(op[2].ind,"m");
op[3].t = 'a'; op[3].c = -1; sprintf(op[3].ind,"k2");
op[4].t = 'c'; op[4].c = -1; sprintf(op[4].ind,"m");
op[5].t = 'h'; op[5].c = 1; sprintf (op[5].ind,"k");
printf ("OLD:\n");

print_operator_series(op, n_op);

operator_t *op_new;
op_new = create_operators(n_op);
op_new = transformation_of_indices(op, par, n_op, &t);

print_operator_series(op_new, n_op);

printf ("Changes made on %d operators\n", t);
printf ("End of testing <<<<\n");
return;
}


int main(){

test_transformation();
return 0;
}
