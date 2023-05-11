#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"

static short automatic = 1;
static char hole_index[] = {'i', 'j', 'k', 'l', 'q'};
static char particle_index[] = {'m', 'n', 'p', 'o', 'r'};

static void error_message(char *s);

static void error_message(char *s){
fprintf (stderr, "%s\n", s);
exit(3);
}


void print_operator_series(operator_t *op, int n){
int i;
char dag[] = "^\\dagger";
char t, *s;
for (i = 0; i < n; i++){
        t = op[i].t;
        s = op[i].ind;
        if (op[i].c == 1) {
                printf ("%c%s_{%s}",t,dag,s);
                }
        else
                printf ("%c_{%s}",t,s);
        }
printf ("\n");
return;
}


void print_all_operator(all_operator_t all){
print_operator_series(all.op, all.n);
}



void print_all_comb_of_operator(all_comb_of_operator_t comb){
int i;
for (i = 0; i < comb.nc; i++)
	print_all_operator(comb.all[i]);
return;
}


operator_t *create_operators(int n){

if (n < 1) error_message("Creation of operators was not successful, n < 1!\n");

operator_t *temp;

temp = (operator_t*) malloc(n*sizeof(operator_t));

if (temp == NULL) error_message("Creation of operators was not successful, NULL-pointer!");

return temp;
}


all_operator_t create_all_empty_operators(int n){
all_operator_t temp;

if (n < 1) error_message("Creation of the empty array of operators failed, n < 1!\n");

temp.n = n;
temp.op = create_operators(n);

return temp;
}


//============================================================================================================
// Function all_comb_of_operator_t create_all_comb_of_empty_operators(int n)
// Description:
// The function creates an array of n "empty" realizations of operators.
// Input argument:
// nc - number of combinations of canonical transformations
// n - total number of operators
// The function returns data of type all_comb_of_operator_t unlike the previously mentioned function.
//============================================================================================================
all_comb_of_operator_t create_all_comb_of_empty_operators(int nc, int n){
all_comb_of_operator_t temp;
int i;

if (nc < 1) error_message("Broj kombinacija mora biti najmanje 1, cak i kad nema kanonskih transformacija!\n");

temp.nc = nc;
temp.n = n;

temp.all = (all_operator_t*) malloc(sizeof(all_operator_t)*nc);
if (temp.all == NULL) 
	error_message("Neuspjelo stvaranja polja kombinacija operatora!\n");

for (i = 0; i < nc; i++){
	temp.all[i] = create_all_empty_operators(n);
	}

return temp;
}

operator_t **create_2D_operators(int n, int m){
char buffer[80];
int i;
if (n < 1 || m < 1) error_message("Creation of 2D array of operators was not successful! At least one dim. < 1!\n");
operator_t **temp;
temp = (operator_t**)malloc(n*sizeof(operator_t*));
if (temp == NULL)  error_message("Creation of 2D array of operators was not successful, NULL-pointer");
temp[0] = (operator_t*)malloc(sizeof(operator_t)*n*m);
if (temp[0] == NULL) error_message("_2Ds : temp[0]-> NULL");
for (i = 1; i < n; i++){
        temp[i] = temp[i-1] + m;
	//if (TEST) printf ("%p\t%p\n", temp[i], temp[i-1]);
        if (temp[i] == NULL){
                sprintf(buffer, "_2Ds : temp[%d] -> NULL", n);
                error_message(buffer);
                }
        }

return temp;
}


operator_t copy_operator(operator_t op){
operator_t temp;
temp.t = op.t;
temp.c = op.c;
temp.pos = op.pos;
strcpy(temp.ind, op.ind);
return temp;
}


void copy_operator2(operator_t * fin, operator_t op){
fin->t = op.t;
fin->c = op.c;
fin->pos = op.pos;
strcpy(fin->ind, op.ind);
return;
}


void copy_indeks(char *indfin, char *indsource){
strcpy(indfin, indsource);
return;
}


//============================================================================================================
// Funkcija operator_t * read_input(char *filename, int *nmax)
// Opis:
//	Funkcija koja očitava operatore unutar braket-a prethodno sačuvane u datoteci.
// Ulazni argumenti:
//	filename	-	naziv datoteke (tipa char*)
//	nmax		-	adresa varijable u koju spremamo ukupan broj operatora (pok. tipa int)
// Funkcija vraća adresu početnog elementa polja operatora (tipa operator_t).
//============================================================================================================
operator_t * read_input(char *filename, int *nmax){
register int count = 0;
char c;
register short start = 0;
register int i;
operator_t *op;
op = create_operators(12);
FILE *fp;
if ((fp = fopen(filename,"r")) == NULL){
        error_message("Error opening file!");
        }
while (fscanf(fp, " %c ", &c) != EOF){
        if ((c == 'a' || c == 'c' || c == 'h') && start == 0){
                op[count].t = c;
                op[count].c = -1;
                op[count].pos = count;
                i = 0;
                start = 1;
                }
        else if (start == 1){
                if (c == '*') op[count].c = 1;
                else if (c == '(') start = 2;
                }
        else if (start == 2){
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                        //op[count].c = -1;
                        op[count].ind[i++] = c;
                        }
                else if (c >= '1' && c <= '9'){
                        op[count].ind[i++] = c;
                        }
                else if (c == ')') {
                        start = 0;
                        op[count].ind[i] ='\0';
                        count++;
                        }
                }
        else {
                error_message("Error reading file!");
                }
        }
*nmax = count;
op = realloc(op, *nmax*sizeof(operator_t));
fclose(fp);
if (op == NULL) error_message("op -> NULL");
return op;
}


all_operator_t read_input_from_file(char *filename){
all_operator_t temp;
int i;
short start, nmax, count;
char c;
FILE *fp;
if ((fp = fopen(filename,"r")) == NULL){
        error_message("Error opening file!");
        }

count = 0; start = 0;

while (fscanf(fp, " %c ", &c) != EOF){
        if ((c == 'a' || c == 'c' || c == 'h') && start == 0){
                start = 1;
		i = 0;
                }
        else if (start == 1){
                if (c == '(') start = 2;
                }
        else if (start == 2){
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
			i++;
                        }
                else if (c >= '1' && c <= '9'){
                        i++;
                        }
                else if (c == ')') {
                        if (i > 0)
                        	count++;
			else error_message("Index of operator is missing!\n");
                        }
                }
        else {
                error_message("Syntax error!");
                }
        }

printf ("Number of operators = %d\n", count);

rewind(fp);

nmax = count;
temp.n = nmax;

temp = create_all_empty_operators(nmax);

count = 0;
start = 0;
operator_t *op;

op = &(temp.op[0]);

while (fscanf(fp, " %c ", &c) != EOF){
        if ((c == 'a' || c == 'c' || c == 'h') && start == 0){
                op[count].t = c;
                op[count].c = -1;
                op[count].pos = count;
                i = 0;
                start = 1;
                }
        else if (start == 1){
                if (c == '*') op[count].c = 1;
                else if (c == '(') start = 2;
                }
        else if (start == 2){
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                        op[count].ind[i++] = c;
                        }
                else if (c >= '1' && c <= '9'){
                        op[count].ind[i++] = c;
                        }
                else if (c == ')') {
                        start = 0;
                        op[count].ind[i] ='\0';
                        count++;
                        }
                }
        else {
                error_message("Error reading file!");
                }
	}

fclose(fp);        

return temp;
}




void print_operator(operator_t op){
printf ("t=%c\tc=%1d\tindex=%s",op.t,op.c,op.ind);
return;
}


void print_operators(operator_t *op, int nmax){
short i;
for (i = 0; i < nmax; i++){
        printf ("ord.: %3.1d ->\tt=%c\tc=%1d\tindex=%s\n",i,op[i].t,op[i].c,op[i].ind);
        }
}


void write_first_info(){
register short i;
printf ("status of static variable = %d", automatic);
for (i = 0; i < sizeof(hole_index); i++)
	printf ("hole_index[%d] = %c", i, hole_index[i]);
for (i = 0; i < sizeof(hole_index); i++)
        printf ("particle_index[%d] = %c", i, particle_index[i]);

return;
}


#ifndef TEST
#define TEST 1
//=========================================================================================================
// void fill_operator(operator_t *op, char type, short cora, char *ind)
// Opis: 
// Funkcija popunjava sadržaj operatora sljedećim podacima:
//	i) tip, čestica (c), šupljina (h) i općeniti tip (a)
//	ii) stvaranje (+1) /poništenje (-1)
// 	iii) indeks operatora
//	iv) red. br. unutar braket-a (opcionalno, ovdje ne!)
// Ulazni argumenti:
// 	op	-	adresa operatora čiji sadržaj popunjavamo (operator_t)
//	type	-	tip operatora (vidi gore) (tipa char)
//	cora	-	stvaranje/poništenje (tipa short)
//	ind	-	idenks (tipa char *)
//=========================================================================================================
void fill_operator(operator_t *op, char type, short cora, char *ind){
char buffer[80];
short i = 0;
//printf ("popunjavam operator...\n");
if (type == 'a' || type == 'c' || type == 'h'){
	op->t = type;
	}
else {
	sprintf (buffer, "Wrong type of operator (transferred -> %c)!\n", type);
	error_message(buffer);
	}

if (cora == 1 || cora ==-1){
	op->c = cora;
	}
else {
        sprintf (buffer, "Operator can be related to creation (+1) or annihilation (-1) : (transferred -> %d)", cora);
        error_message(buffer);
        }

while (ind[i] != '\0' && i < INDEX_SIZE-1){
	op->ind[i] = ind[i];
	i++;
	}
if (i == 0) error_message("There is no index related to the operator!!!\n");
op->ind[i] = '\0';

return;
}


//=========================================================================================================
// operator_t return_operator(char type, short cora, char *ind)
// Opis: 
// Funkcija popunjava sadržaj operatora sljedećim podacima:
//      i) tip, čestica (c), šupljina (h) i općeniti tip (a)
//      ii) stvaranje (+1) /poništenje (-1)
//      iii) indeks operatora
//      iv) red. br. unutar braket-a (opcionalno, ovdje ne!)
// Vidi funkciju void fill_operator(operator_t *op, char type, short cora, char *ind).
// Ulazni argumenti:
//      type    -       tip operatora (vidi gore) (tipa char)
//      cora    -       stvaranje/poništenje (tipa short)
//      ind     -       idenks (tipa char *)
// Funkcija vraća operator
//=========================================================================================================
operator_t create_operator(char type, short cora, char *ind){
operator_t temp;
char buffer[80];
short i = 0;

//printf ("popunjavam operator...\n");
if (type == 'a' || type == 'c' || type == 'h'){
        temp.t = type;
        }
else {
        sprintf (buffer, "Wrong type of operator (transferred -> %c)\n", type);
        error_message(buffer);
        }

if (cora == 1 || cora ==-1){
        temp.c = cora;
        }
else {
        sprintf (buffer, "Operator can be related to creation (+1) or annihilation (-1) : (transferred -> %d)\n", cora);
        error_message(buffer);
        }

while (ind[i] != '\0' && i < INDEX_SIZE-1){
        temp.ind[i] = ind[i];
        i++;
        }
if (i == 0) error_message("There is no index related to the operator!!!\n");
temp.ind[i] = '\0';

return temp;
}


#undef TEST
#endif



void free_all_operator(all_operator_t *temp){
free(temp->op);
temp->n = 0;
return;
}



void free_all_comb_of_operator(all_comb_of_operator_t *temp){
int i;
for (i = temp->nc-1; i >= 0; i--)
	free_all_operator(&temp->all[i]);

if (temp->nc > 0) free(temp->all);
temp->nc = 0;
temp->n = 0;

return;
}



void E2Doperator(operator_t **temp){
free(temp[0]);
free(temp);
return;
}
