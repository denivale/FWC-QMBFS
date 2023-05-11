#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operator.h"
#include "reading.h"
#include "transindex.h"
#include "shalloc.h"


//==============================================================================================================
// static int compare(operator_t * op, char * s, int n, short * pos)
// Opis:
// Usporedba indeksa operatora. Jednostavno prolazimo kroz indekse svih operatora
//==============================================================================================================
static int compare(operator_t * op, char * s, int n, short * pos){
register int i, comp;
int sim = 0; 
if (n == 0) return sim;
for (i = 0; i < n; i++){
	comp = strcmp(op[i].ind, s);
	if (comp == 0){
		sim += 1;
		pos[i] = 1;
		}
	else pos[i] = 0;
	}
return sim;
}

//==============================================================================================================
// Funkcija warning_index(char *s, short *pos, int n)
// Opis:
// Ispisuje pojavljuje li se isti indeks kod preostalih operatora
//==============================================================================================================
static void warning_index(char *s, short *pos, int n){
register int i;
printf ("Indeks \"%s\" se jos pojavljuje na sljedecim pozicijama:\n", s);
printf("%4.1d", n);
for (i = 0; i < n; i++){
	if (pos[i] == 1) printf ("%4.1d", i);
	}
printf ("\n");
return;
}

//==============================================================================================================
// Funkcija int warning_repeating_indices(operator_t * op, int n_op)
// Opis:
// Provjerava postoji li isti indeks u polju operatorima
// Ulazni argumenti:
//	op	- 	polje operatora
//	n_op	- 	broj operatora
// Rezultat:
//	0	-	nema ponavljanja indeksa
//	>0	.	ponavljanje indeksa
//==============================================================================================================
int warning_repeating_indices(operator_t * op, int n_op){
int war = 0;
register int i;
short *pos;
pos = _1Ds(n_op);
for (i = 0; i < n_op; i++){
	if (compare(op, op[i].ind, i, pos) > 0){
		warning_index(op[i].ind, pos, i);
		war++;
		}
	}
free(pos);
return war;
}

//=============================================================================================================
// Funkcija static int test_hp(paramet_t par, operator_t op, operator_t *op_new)
//
// Opis:
// Funkcija koja provjerava postoje li predefinirani indeksi za česticna i šupljinska stanja.
// Ukoliko određeni operator sadrži indeks koji je predefiniran, tada funkcija radi transformacije 
// općenitih operatora u one čestičnog ili šupljinskog karaktera.
//
// Ulazni argumenti:
// 	par	-	predefinirani indeksi za supljinska i cesticna stanja nalaze se u strukturi paramet_t
//	op	-	operator koje testiramo
//	op_new	-	novi operator
// Rezultat:
//	0	-	nema transformacije operatora
//	1	-	transformacija operatora
//=============================================================================================================
static int test_hp(paramet_t par, operator_t op, operator_t *op_new){
register int i;
int stat = 0;
*op_new = copy_operator(op);
for (i = 0; i < par.hin; i++){
	if (op.t == 'a' && par.hi[i] == op.ind[0]){
		op_new->t = 'h';
		if (op.c == 1) op_new->c = -1;
		else op_new->c = 1;
		stat = -1;
		}
	}
for (i = 0; i < par.pin; i++){
        if (op.t == 'a' && par.pi[i] == op.ind[0]){
                op_new->t = 'c';
                if (op.c == 1) op_new->c = 1;
                else op_new->c = -1;
		stat = 1;
                }
        }

return stat;
}

//=============================================================================================================
// Opis:
// Funkcija koja stvara transformirani skup operatora baziran na predefiniranim indeksima vezanih uz 
// čestična i šupljinska stanja. 
// Ulazni argumenti:
// 	op	-	operatori
//	par	-	konkretno treba dio strukture vezan za predefinirane šupljinske i čestične indekse
//	n_op	-	broj operatora
// Izlaz:
//	transformed	- 	broj transformiranih operatora
//	vraća polje transformiranih operatora tipa operator_t
//=============================================================================================================
operator_t * transformation_of_indices(operator_t * op, paramet_t par, int n_op, int *transformed){
operator_t * temp;
temp = create_operators(n_op);
register int i;
int counter = 0;
for (i = 0; i < n_op; i++){
	if (test_hp(par, op[i], &temp[i]) != 0){
		counter++;
		}
}

*transformed = counter;
return temp;
}

int test_konz(){

return 1;
}


all_operator_t transformation_of_indices_if_needed(all_operator_t all_op, paramet_t par, int *transformed){
all_operator_t temp;

temp = create_all_empty_operators(all_op.n);

register int i;
int counter = 0;
for (i = 0; i < all_op.n; i++){
        if (test_hp(par, all_op.op[i], &temp.op[i]) != 0){
                counter++;
                }
}

*transformed = counter;

return temp;
}


