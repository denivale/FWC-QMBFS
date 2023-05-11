#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shalloc.h"
#include "combinatorics.h"

static void swap_short(short *, short *);
int factoriel(int);
long int lfactoriel(int n);


static void swap_short(short *x, short *y){
short temp;
temp = *x;
*x = *y;
*y = temp;
}


void print_permutations(short **polje, int ind, int perm){
register int i, j;
for (i = 0; i < perm; i++){
	for (j = 0; j < ind; j++){
		printf ("%4.1d", polje[i][j]);
		}
	printf ("\n");	
	}
return;
}


//======================================================================================================
/*
 Function get_all_permutations(short *field, int l, int r, int n, short**save)
 Description:
 The function calculates all permutations and records them in a 2D array. There are two static variables
 of integer type, which are used precisely for saving each permutation.
 Input arguments:
    polje - input array (short)
    l - red. no. of the initial element that change place with some other element (type int)
    r - red. no. of the final element that change place with some other element (type int)
    n - total number of field elements (type int)
 Exit:
    save - all permutations saved in a 2D array of type short.
 selected variable:
    counter_saved - realization counter
    factoriel_mem- number of permutations
*/
//======================================================================================================
static int counter_saved = 0;
static int factoriel_mem;

void reset_counter(){
counter_saved = 0;
}

void get_all_permutations(short *polje, int l, int r, int n, short**save){
int i;
if (l == r){
        for (i = 0; i < n; i++){
                save[counter_saved][i] = polje[i];
                }

	if (counter_saved == 0)
		factoriel_mem = factoriel(n);
	
	counter_saved++;
	
	if (counter_saved == factoriel_mem)
		counter_saved = 0;
        }
else{
        for (i = l; i <= r; i++){
                swap_short((polje+l), (polje+i));
                get_all_permutations(polje, l+1, r, n, save);
                swap_short((polje+l), (polje+i));
                }

        }
}



int factoriel(int n){
if (n == 0) return 1;
else return n*factoriel(n-1);
}

long int lfactoriel(int n){
if (n == 0) return 1;
else return n*factoriel(n-1);
}



short **create_field_of_combinations(short *change, short n){
short **temp, *borders;
short p, c, nums;
short i, j, k;

p = (short)pow(2,n);

if (n == 0) temp = _2Ds(1, p);
else temp = _2Ds(n, p);

for (k = 0; k < n; k++){
        nums = (short)pow(2,k+1);
        borders = _1Ds(nums);
        j = 0;
        for (i = 0; i < p; i += p/nums){
                borders[j++] = i;
                }
// remove comments for testing
//        printf ("borders : ");
//        for (i = 0; i < nums; i++)
//                printf ("%4.1d", borders[i]);
//        printf ("\n");
        j = -1 ; c = -1;
        for (i = 0; i < p; i++){
                if (i == borders[j+1]) {
                        c *= -1;
                        j++;
                        }
                if (change[k] == 1) temp[k][i] = c;
                else temp[k][i] = -c;
                }
        free(borders);
        }
// remove comments for testing
/*
for (j = 0; j < p; j++){
        for (i = 0; i < n; i++){
                printf ("%4.1d", temp[i][j]);
                }
        printf ("\n");
        }
*/

return temp;
}


cf2_t create_and_fill_alternation_of_pm_one(cf_t need_to_change){
cf2_t temp;

temp.cf = create_field_of_combinations(need_to_change.cf, need_to_change.n);

temp.n = need_to_change.n;

return temp;
}


void free_cf2(cf2_t * temp){
free (temp->cf[0]);
free (temp->cf);
return;
}
