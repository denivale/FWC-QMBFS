#include <stdio.h>
#include <stdlib.h>

#include "shalloc.h"


static void error_message(char *);
static int mtest_func(int *, int);
static long int determine_block_size(int, int *);

static void test_1D();
static void test_2D();
static void test_2D_adjustable();

static void error_message(char *s){
fprintf (stderr, "Error!!!!\n%s\n", s);
exit(2);
}

short * _1Ds(int n){
short * temp;
if (n < 1) error_message("_1Ds : n < 1!\n");
temp = (short*) malloc(sizeof(short)*n);
if (temp == NULL) error_message("_1Ds : temp-> NULL");
return temp; 
}

#define TEST 1
short ** _2Ds(int n, int m){
short ** temp;
char buffer[80];
if (n < 1 || m < 1) {
	sprintf (buffer, "_2DS : n = %d, m = %d!!!!", n, m);
	error_message(buffer);
	}

temp = (short**)malloc(sizeof(short*)*n);
if (temp == NULL) error_message("_2Ds : temp-> NULL");
int i;
temp[0] = (short*)malloc(sizeof(short)*n*m);
if (temp[0] == NULL) error_message("_2Ds : temp[0]-> NULL");
for (i = 1; i < n; i++){
	temp[i] = temp[i-1] + m;
//	if (TEST) printf ("%p\t%p\n", temp[i], temp[i-1]);
	if (temp[i] == NULL){
		sprintf(buffer, "_2Ds : temp[%d] -> NULL", n);
		error_message(buffer);
		}
	}
return temp;
}

static int mtest_func(int *m, int n){
register int i;
for (i = 0; i < n; i++){
	if (m[i] < 1) return 0;
	}
return 1;
}

static long int determine_block_size(int n, int *m){
register int i;
register long int count = 0;
for (i = 0; i < n; i++){
	count += m[i];
	}
return count;
}

short ** _2Ds_adjustable(int n, int *m){
short ** temp;
int mtest;
char buffer[80];
mtest = mtest_func(m,n);
if (n < 1 || mtest < 1) {
        sprintf (buffer, "_2DS_adjustable : n = %d, mtest = %d!!!!", n, mtest);
        error_message(buffer);
        }

temp = (short**)malloc(sizeof(short*)*n);
if (temp == NULL) error_message("_2Ds_adjustable : temp-> NULL");
register int i;
register long int size;
size = determine_block_size(n, m);
if (TEST) printf ("size = %ld * sizeof(short) = %ld\n", size, size*sizeof(short));
temp[0] = (short*)malloc(sizeof(short)*size);
if (temp == NULL) error_message("_2Ds_adjustable : temp[0]-> NULL");
for (i = 1; i < n; i++){
        temp[i] = temp[i-1] + m[i-1];
        //if (TEST) printf ("%p\t%p\n", temp[i], temp[i-1]);
        if (temp[i] == NULL){
                sprintf(buffer, "_2Ds_adjustable : temp[%d] -> NULL", n);
                error_message(buffer);
                }
        }
return temp;
}
#undef TEST

void E1Ds(short *a){
free(a);
}

void E2Ds(short **a){
free(a[0]);
free(a);
}

static void test_1D(){
short *polje;
int i, n = 3;
polje = _1Ds(n);
for (i = 0; i < n; i++){
	polje[i] = i;
	printf ("%d\tAdress: %p\n", polje[i], &polje[i]);
	}
E1Ds(polje);
return;
}

static void test_2D(){
short **polje;
int i, j, n = 3;
polje = _2Ds(n,n);
for (i = 0; i < n; i++){
	for (j = 0; j < n; j++){ 
        	polje[i][j] = i-j;
        	printf ("%d\tAdress: %p\n", polje[i][j], &polje[i][j]);
		}
        }
E2Ds(polje);
return;
}

static void test_2D_adjustable(){
short **polje;
int i, j, n = 3, *m;
m = (int*)malloc(sizeof(int)*n);
for (i = 0; i < n; i++){
	m[i] = i+1;
	}
polje = _2Ds_adjustable(n,m);
for (i = 0; i < n; i++){
        for (j = 0; j < m[i]; j++){
                polje[i][j] = i;
                printf ("%d\tAdress: %p\n", polje[i][j], &polje[i][j]);
                }
        }
E2Ds(polje);
return;
}



void test_shalloc(){
test_1D();
test_2D();
test_2D_adjustable();
printf("Test completed successfully!");
return;
}
