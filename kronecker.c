#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "operator.h"
#include "kronecker.h"

static void error_message(char *);


static void error_message(char *s){
fprintf (stderr, "Error!!!!\n%s\n", s);
exit(2);
}



void print_kroencker1D_standard(kronecker_t *delta, short phase, int num_lines){
short i;
if (phase == -1) printf ("%4.1d", phase);
for (i = 0; i < num_lines; i++){
        print_kronecker_standard(delta[i]);
        }

return;
}


void print_all_kronecker_deltas(all_kronecker_t delta){

print_kroencker1D_standard(delta.delta, delta.predfac.rez, delta.n);

return;
}


void print_kronecker_standard(kronecker_t delta){
if (delta.rez == 0) {
        printf ("0\n");
        return;
        }
printf ("\\delta_{%s %s}", delta.ind1, delta.ind2);
if (delta.fermi == 1) {
        printf ("\\Theta(\\epsilon_{%s} - \\epsilon_F)", delta.ind1);
        }
else if(delta.fermi == -1) {
        printf ("\\Theta(\\epsilon_F - \\epsilon_{%s})", delta.ind1);
        }


printf("\n");
return;
}



void fill_kronecker(kronecker_t *delta, char *ind1, char *ind2, short pos1, short pos2, short rez, short fermi){
register short i = 0;

while (ind1[i] != '\0' && i < INDEX_SIZE-1){
        delta->ind1[i] = ind1[i];
        i++;
        }
if (i == 0)  error_message("Failed, no index related to Kronecker symbol!!!\n");
delta->ind1[i] = '\0';

i = 0;
while (ind2[i] != '\0' && i < INDEX_SIZE-1){
        delta->ind2[i] = ind2[i];
        i++;
        }
if (i == 0) error_message("Failed, no index related to Kronecker symbol!!!\n");
delta->ind2[i] = '\0';

delta->pos1 = pos1;
delta->pos2 = pos2;
delta->rez = rez;
delta->fermi = fermi;



return;
}



void kronecker_free(kronecker_t *delta){
free(delta);
}


void kronecker_all_free(all_kronecker_t *all){
if (all->n != 0)
	free(all->delta);
all->delta = NULL;
all->n = 0;
}


void kronecker_2D_free(kronecker_t **delta){
free(delta[0]);
free(delta);
}



void copy_kronecker_deltas(kronecker_t * dest, kronecker_t * source, int n){
int i;
for (i = 0; i < n; i++){
        copy_indeks(dest[i].ind1, source[i].ind1);
        copy_indeks(dest[i].ind2, source[i].ind2);
        dest[i].pos1 = source[i].pos1;
        dest[i].pos2 = source[i].pos2;
        dest[i].rez = source[i].rez;
        dest[i].fermi = source[i].fermi;
        }

return;
}


void copy_predfac(predfac_t * dest, predfac_t source){
dest->rez = source.rez;
return;
}



void copy_kronecker_delta(kronecker_t * dest, kronecker_t source){
        
copy_indeks(dest->ind1, source.ind1);
copy_indeks(dest->ind2, source.ind2);
        
dest->pos1 = source.pos1;
dest->pos2 = source.pos2;
dest->rez = source.rez;
dest->fermi = source.fermi;
        
return;
}



void copy_all_kronecker_deltas(all_kronecker_t *dest, all_kronecker_t source){
int i;
if (dest->n != source.n){
	error_message("Error! Cannot copy Kronecker delta array! Dimensions of arrays are different\n");
	}

copy_predfac(&dest->predfac, source.predfac);

for (i = 0; i < source.n; i++)
	copy_kronecker_delta(&dest->delta[i], source.delta[i]);

return;
}



kronecker_t * create_field_kronecker(int n){
kronecker_t * temp;

if (n < 1)  error_message("Kronecker_t 1D : n < 1!\n");

temp = (kronecker_t*) malloc(sizeof(kronecker_t) * n);
if (temp == NULL) error_message("Kronecker_t 1D : temp-> NULL");

return temp;
}



all_kronecker_t create_empty_all_kronecker(int n){
all_kronecker_t temp;

if (n < 0)
	error_message("Error, dimension of array of Kronecker symbols is less than zero!\n");

if (n == 0){
	temp.n = 0;
	temp.delta = NULL;
	return temp;
	}

temp.n = n;

temp.delta = create_field_kronecker(n);

if (temp.delta == NULL)
	error_message("Error, allocation of array of Kronecker symbols failed!\n");

return temp;
}


kronecker_t ** create_2D_field_kronecker(int n, int m){
kronecker_t ** temp;
char buffer[80];
if (n < 1 || m < 1) {
        sprintf (buffer, "Kronecker 2D : n = %d, m = %d!!!!", n, m);
        error_message(buffer);
        }

temp = (kronecker_t**)malloc(sizeof(kronecker_t*)*n);
if (temp == NULL) error_message("Kronecker 2D : temp-> NULL");
int i;
temp[0] = (kronecker_t*)malloc(sizeof(kronecker_t)*n*m);
if (temp[0] == NULL) error_message("Kronecker 2D : temp[0]-> NULL");
for (i = 1; i < n; i++){
        temp[i] = temp[i-1] + m;
       // if (TEST) printf ("%p\t%p\n", temp[i], temp[i-1]);
        if (temp[i] == NULL){
                sprintf(buffer, "Kronecker 2D : temp[%d] -> NULL", n);
                error_message(buffer);
                }
        }
return temp;
}

