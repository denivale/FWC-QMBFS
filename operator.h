#ifndef _OPERATOR_H
#define _OPERATOR_H


#define INDEX_SIZE 3
#define INDEX_FULL_SIZE 80

#define CREATE_STD 1
#define DESTROY_STD -1

typedef struct{
char t;//a,c,h
short c;//creation or anihilation
char ind[INDEX_SIZE];
short pos;
char tind[4];//ovo treba dodati kod copy operatora i sl.
} operator_t;

typedef struct{
operator_t *op;
int n;
} all_operator_t;

typedef struct{
all_operator_t *all;
int nc, n;
} all_comb_of_operator_t;

void print_operator_series(operator_t *, int);


// stvaranje polja operatora
operator_t *create_operators(int);
all_operator_t create_all_empty_operators(int n);
all_comb_of_operator_t create_all_comb_of_empty_operators(int nc, int n);
operator_t create_operator(char type, short cora, char *ind);
operator_t copy_operator(operator_t);

// presnimavanje operatora
void copy_operator2(operator_t *, operator_t);

void copy_indeks(char[], char[]);

// Ucitavanje operatora
operator_t * read_input(char *, int *);
all_operator_t read_input_from_file(char *filename);

// Ispis operatora
void print_operators(operator_t *, int);
void print_operator(operator_t);
void print_all_operator(all_operator_t all);
void print_all_comb_of_operator(all_comb_of_operator_t comb);

// Popunjavanje
void fill_operator(operator_t *, char, short, char *);
operator_t **create_2D_operators(int, int);

//status function
void write_first_info();

//free memory
void Eop_t(operator_t *);
void E2Doperator(operator_t **);
void free_all_operator(all_operator_t *temp);
void free_all_comb_of_operator(all_comb_of_operator_t *temp);

//test function
void test_fill_operator();
#endif
