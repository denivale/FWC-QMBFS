//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 31 2019
 - last modification May 21 2023 (D. Vale)
*/
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shalloc.h"
#include "combinatorics.h"

static void swap(int *x, int *y){
int temp;
temp = *x;
*x = *y;
*y = temp;
}

static void swap_short(short *x, short *y){
short temp;
temp = *x;
*x = *y;
*y = temp;
}



static void permute(int *polje, int l, int r, int n){
int i;
if (l == r){
        for (i = 0; i < n; i++){
                printf ("%d\t", polje[i]);
                }
        printf ("\n");
        }
else{
        for (i = l; i <= r; i++){
                swap((polje+l), (polje+i));
                permute(polje, l+1, r, n);
                swap((polje+l), (polje+i));
                }

        }
}



void test_permutations(){
int *polje;
polje = (int*)malloc(sizeof(short)*4);
polje[0] = 1;
polje[1] = 2;
polje[2] = 3;
polje[3] = 4;
printf (">>> Testing permutations... \n");
permute(polje, 0, 3, 4);

short *p;
p = _1Ds(4);
p[0] = 1;
p[1] = 2;
p[2] = 3;
p[3] = 4;

short **p2;
p2 = _2Ds(factoriel(4),4);
printf ("Get all permutations of operators!\n");
get_all_permutations(p, 0, 3, 4, p2);

int i, j;
for (i = 0; i < factoriel(4); i++){
        for (j = 0; j < 4; j++)
                printf("%4.1d", p2[i][j]);
        printf ("\n");
        }
return;
}

void test_combinations(){
short *change;
int n = 6, i, j;
change = (short*)malloc(sizeof(short)*3);
for (i = 0; i < n; i++)
        change[i] = 1;
change[0] = -1;
change[4] = -1;
short **temp;
temp = create_field_of_combinations(change, n);
for (j = 0; j < (short)pow(2,n); j++){
        for (i = 0; i < n; i++){
                printf ("%4.1d", temp[i][j]);
                }
        printf ("\n");
        }
E2Ds(temp);
free(change);
return;
}


int main(){
printf ("Testing permutations...\n");
test_combinations();
test_permutations();
printf ("... end of testing\n");

return 0;
}
