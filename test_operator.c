#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"


void test_fill_operator(){
operator_t op;
printf ("Testing operator!\n");
fill_operator(&op, 'c', 1, "123");
printf ("Operator filled!\n");
print_operator(op);
return;
}

void test_all_operators(){
operator_t op;
op = create_operator('c', 1, "123");
print_operator(op);
printf("\n");
all_operator_t all;
int n = 5;
all = create_all_empty_operators(n);
free_all_operator(&all);
return;
}


void test_comb_of_operators(){

return;
}

void test_reading_of_operators_from_file(){
char filename [80] = "in_test.dat";
all_operator_t all;

all = read_input_from_file(filename);
print_all_operator(all);

free_all_operator(&all);
return;
}

int main(){
//test_fill_operator();
//test_all_operators();
test_reading_of_operators_from_file();
return 0;
}
