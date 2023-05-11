#include <stdio.h>
#include <stdlib.h>
#include "reading.h"
#include "calculation.h"


static void help(){
printf ("Please, use input as follows:\n");
printf ("./run -f <filename>\n");
printf ("For additional information please read README file!\n");
return;
}



static void argument_problem(){
printf ("Please, use input as follows:\n");
printf ("./run -f <filename>\n");
printf ("Error, wrong command line arguments!\n");
return;
}


static void intro(){
printf ("====================================================================================\n");
printf ("                       PROGRAM FWC-QMBFS\n");
printf ("Title:Fast calculation full Wick's contractions in quantum many-body\n");
printf ("fermion systems\n");
printf ("Authors: Deni Vale, Nils Paar\n");
printf ("Version: v1.0\n");
printf ("All rights reserved (C)\n");
printf ("This product is protected under the Croatian law \"Zakon o autorskom pravu i\n"); 
printf ("srodnim pravima\" NN 111/21 from October 22 2021.\n");
printf ("Build: 2019 - 2023\n");
printf ("Published/avaible online: 2023\n");
printf ("Maintainer of the current version: Deni Vale\n");
printf ("Email: denivalesq@gmail.com (dvale@iv.hr), npaar@phy.hr\n");
printf ("\n");
printf ("The statements above do not include any external program or latex package \n");
printf ("called by this program!\n");
printf ("\n"); 
printf ("Please do not hesitate to contact us on the email above if you notice any\n"); 
printf ("violation of rights.\n");
printf ("====================================================================================\n");
}


static void free_option(option_t *temp){
free(temp->filename);
return;
}

int main(int argc, char ** argv){
int i;
option_t option;
char c;
short extra = 0;

intro();
//printf ("argc = %d", argc);
for (i = 1; i < argc; i++){
	if (argv[i][0] == '-'){
		extra = 1;
		c = argv[i][1];
		if (c == 'h') help();
		else if (c == 'f'){
			option.type = 'f';
			if (i+1 < argc){
				option.filename = (char*)malloc(sizeof(char)*80);
				sprintf(option.filename, "%s", argv[++i]);
				//printf ("filename = %s\n", option.filename);
				}
			else {
				argument_problem();
				return -1;
				}
			}
		else {
			fprintf (stderr, "Greska u argumentima komandne linije\n");
            return -2;
			}
		}
	//printf ("%s\n", argv[i]);
	}

if (option.type == 'f')
	start_procedure(option);
else return -3;

free_option(&option);

return 0;
}

