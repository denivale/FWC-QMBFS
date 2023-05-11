#include <stdio.h>
#include <stdlib.h>

#include "reading.h"

#define Nind 21
static int test_repeating_indices(char *s, char c, int n){
register int i;
if (n == 0) return 0;
for (i = 0; i < n; i++){
        if (s[i] == c) return 1;
        }
return 0;
}

void read_parameters(option_t opt, paramet_t *par){
char file_name[] = "paramet.par";
char line[80];
char c;
short i;
par->hi = (char*) malloc(sizeof(char)*Nind);
par->pi = (char*) malloc(sizeof(char)*Nind);
par->hin = 0;
par->pin = 0;
FILE *fp;
if((fp = fopen(file_name, "r"))==NULL) {
        printf("Cannot open file %s.\n", file_name);
        exit(4);
        }
if (fp != NULL){
        printf ("\nReading from %s...\n", file_name);

        fgets(line,sizeof line, fp);
        fprintf(stdout, "%s", line);
        fscanf(fp, "%d\n", &(par->aut));
        printf("%d\n",par->aut);

        if (par->aut == 1){
                //hole index
                fgets(line,sizeof line, fp);
                fprintf(stdout, ">%s", line);
                do {
                        fscanf (fp, "%c", &c);
		//      printf ("znak: %c\n", c);
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                                if (test_repeating_indices(par->hi, c, par->hin) == 0)
                                        par->hi[par->hin++] = c;
                } while (c != '\n');
                par->hi[par->hin] = '\0';
                printf("hole: %s\n",par->hi);

                //particle index
                fscanf(fp,"\n");
                fgets(line,sizeof line, fp);
                fprintf(stdout, ">%s", line);
                do {
                        fscanf (fp, "%c", &c);
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                                if (test_repeating_indices(par->pi, c, par->pin) == 0)
                                        par->pi[par->pin++] = c;
                } while (c != '\n' && c != EOF);
                par->pi[par->pin] = '\0';
                printf("particle: %s\n",par->pi);

                par->hi = (char*) realloc(par->hi, sizeof(char)*(par->hin+1));
                par->pi = (char*) realloc(par->pi, sizeof(char)*(par->pin+1));
                }
	else {
		for (i = 0; i < 4; i++){
			fgets(line,sizeof line, fp);
			}
		}
	fgets(line, sizeof line, fp);
	fscanf(fp, " %c %c %c \n", &(par->pvr), &(par->dvr), &(par->svr));	
	printf("visual representation: %c %c %c!\n", par->pvr, par->dvr, par->svr);
	fgets(line, sizeof line, fp);
	fscanf(fp, " %c %c %c \n", &(par->pld), &(par->wld), &(par->sld));
	printf ("latex document : %c %c %c!\n", par->pld, par->wld, par->sld);

	fgets(line, sizeof line, fp);
	fscanf(fp, " %s ", par->program_name);
        printf ("program used for opening ps or pdf format : %s!\n", par->program_name);   

        }
return;
}

void test_reading_parameters(){
option_t opt;
paramet_t par;
opt.type = 2;
read_parameters(opt, &par);
return;
}

