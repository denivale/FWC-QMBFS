#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"
#include "line.h"
#include "latex.h"
#include "contraction.h"
#include "shalloc.h"
#include "reading.h"


int lat_c;//counting only different from zero!
int lat_p;
int lat_d;
short lat_zero = 0;
latex_data3_t *latex_data_c;
latex_data2_t *latex_data_p;
latex_data3_t latex_data_init;
latex_data4_t *latex_delta;
short simplew;
static void write_sign(latex_info_t *lif, char c);
static void write_string(latex_info_t *lif, char *c);
static void begin_latex_document(latex_info_t *);
static void end_latex_document(latex_info_t *);
static void newline(latex_info_t *);
static void open_latex_file(latex_info_t *);
static void finish_latex_file(latex_info_t *);




void latex_fill_info(latex_info_t * lat, char pld, char wld, char sld, char * program_name){


strcpy(lat->program_name, program_name);
strcpy(lat->latex_f, "latout.tex");
strcpy(lat->pdf_f, "latout.pdf");

FILE *fp;
fp = fopen("parout.out", "w");
fprintf (fp, "info->program_name :\t%s\n", lat->program_name);
fprintf (fp, "info->latex_f :\t%s\n", lat->latex_f);
fprintf (fp, "info->pdf_f :\t%s\n", lat->pdf_f);

if (pld == 'p') {
	lat->prepair = 1;
	fprintf (fp, "info->prepair :\t%d\n", lat->prepair);
	}
else {
        lat->prepair = 0;
        lat->create = 0;
        lat->show = 0;
	fprintf (fp, "info->prepair :\t%d\n", lat->prepair);
	fprintf (fp, "info->create :\t%d\n", lat->create);
	fprintf (fp, "info->show :\t%d\n", lat->show);

        return;
        }
if (wld == 'w'){
        lat->create = 1; lat->opt = 'w';
	fprintf (fp, "info->create :\t%d\n", lat->create);
        }
else if (wld == 'a'){
	lat->create = 2; lat->opt = 'a';
	fprintf (fp, "info->create :\t%d\n", lat->create);
	}
else {
        lat->create = 0;
	fprintf (fp, "info->create :\t%d\n", lat->create);
        lat->show = 0;
	fprintf (fp, "info->show :\t%d\n", lat->show);

        return;
        }
if (sld == 's'){
        lat->show = 1;
	fprintf (fp, "info->show :\t%d\n", lat->show);
        }
else {
        lat->show = 0;
	fprintf (fp, "info->show :\t%d\n", lat->show);
        }
fclose(fp);
return;
}


void latex_reset_counters(){
lat_c = 0;
lat_p = 0;
lat_d = 0;
}


void latex_initialize_combinations(int n){
printf ("Initialization of memory reserved for printing all combinations in latex file!\n");
latex_data_c = (latex_data3_t*)malloc(sizeof(latex_data3_t)*n);
printf ("Array latex_data_c is allocated!\n");
}


void latex_initialize_arrays_and_counters(int nc, int np, int nd){
lat_c = 0;
lat_p = 0;
lat_d = 0;
printf ("Prepairing latex arrays...(%d, %d, %d)\n", nc, np, nd);
latex_data_c = (latex_data3_t*)malloc(sizeof(latex_data3_t)*nc);
printf ("Array latex_data_c is allocated!\n");
latex_data_p = (latex_data2_t*)malloc(sizeof(latex_data2_t)*np);
printf ("Array latex_data_p is allocated!\n");
latex_delta = (latex_data4_t*)malloc(sizeof(latex_data4_t)*nd);
printf ("Array latex_delta is allocated!\n");
printf ("... latex arrays prepaired!\n");
return;
}

void latex_kill(){
printf ("Set all latex counters back to 0!\n");
lat_c = 0;
lat_p = 0;
lat_d = 0;
printf ("Cleaning memory previously reserved for latex objects\n");
free_latex_data3_t(latex_data_c, lat_c);
free_latex_data2_t(latex_data_p, lat_p);
free_latex_data4_t(latex_delta, lat_d);
printf ("... memory is free now!\n");
return;
}

void free_latex_data4_t(latex_data4_t *lat, int num){
register int i;
for (i = 0; i < num; i++){
	free(lat[i].delta);
	}
if (num > 0) free(lat);
return;
}

void free_latex_data3_t(latex_data3_t *lat, int num){
register int i;
for (i = 0; i < num; i++){
	free(lat[i].op);
	}
if (num > 0) free(lat);
return;
}

void free_latex_data2_t(latex_data2_t *lat, int num){
register int i;
for (i = 0; i < num; i++){
	free(lat[i].op);
	free(lat[i].end);
	free(lat[i].beg);
	}

if (num > 0) free(lat);
return;
}




void be_eq(latex_info_t *lif, char *be, char *choice){
if (strcmp(be, "begin") == 0 || strcmp(be, "end")== 0) {
	if (strcmp(be, "end")==0) fprintf (lif->LF, "\n\\%s{", be);
	else fprintf (lif->LF, "\\%s{", be);
	}
else {
	fprintf (stderr, "Error in writing latex file!!!\n");
	exit(10);
	}
if (strcmp(choice, "equation") == 0 || strcmp(choice,"multline") == 0 || strcmp(choice,"align") == 0){
	fprintf (lif->LF, "%s}\n", choice);
	}
else{
	fprintf (stderr, "Error in writing latex file!!!\n");
	exit(10);
	}

return;
}

static void nonumber(latex_info_t *lif){
fprintf (lif->LF, "\\nonumber");
}

static void newline(latex_info_t *lif){
fprintf (lif->LF, "\\\\ \n");
return;
}

static void begin_latex_document(latex_info_t *lif){
fprintf (lif->LF, "\\begin{document}\n");
return;
}


static void end_latex_document(latex_info_t *lif){
fprintf (lif->LF, "\\end{document}\n");
return;
}
static void write_sign(latex_info_t *lif, char c){
fprintf (lif->LF, "%c", c);
}
static void write_string(latex_info_t *lif, char *c){
fprintf (lif->LF, "%s", c);
}

void print_latex_zero(latex_info_t *lif){
write_sign(lif, '0');
return;
}


void latex_print(latex_info_t *lat){
int i, num, divider, divider2 = 1;

//latex_fill_info(&lat, par.pld, par.wld, par.sld, par.program_name);

if (lat->create == 0){
	printf ("Option for writing latex objects in document was not set!\n");
	return;
	}

open_latex_file(lat);

prepair_latex_headers(lat);

begin_latex_document(lat);

//be_eq(lat,"begin","multline");
be_eq(lat,"begin","align");

if (latex_data_init.n > 6)
	write_string(lat, "&");
print_pure_operators(lat, latex_data_init, 1);

if (lat_zero == 1) {
    write_string(lat, "~=~");
    goto zero_rez;
    }

if (latex_data_init.n> 6)
	write_string(lat, "~=~");
else
	write_string(lat, "~&=~");

num = latex_data_init.n;
if (num > 1 && num <= 4){
	divider = 3;
	divider2 = 3;
	}
else if (num > 4 && num <= 12){
	divider = 2;
    divider2 = 2;
	}
else divider = 1;

for (i = 0; i < lat_c-1; i++){
	print_pure_operators(lat, latex_data_c[i], 1);
	if (i % divider == divider - 1) {nonumber(lat); newline(lat); write_string(lat, "~&+~"); continue;}
	write_string(lat, "~+~");
	}
if (simplew == 0) print_pure_operators(lat, latex_data_c[lat_c-1], 1);

if (lat_p == 0) goto zero_rez;

newline(lat);

write_string(lat, "~&=~");

for (i = 0; i < lat_p-1; i++){
	print_contractions(lat, latex_data_p[i], 1);
	if (i % divider == divider - 1) {nonumber(lat); newline(lat); write_string(lat, "~&+~"); continue;}

	write_string(lat, "~+~");
	}

print_contractions(lat, latex_data_p[lat_p-1], 1);

newline(lat);

write_string(lat, "~&=~");

for (i = 0; i < lat_p -1 ; i++){
	if (latex_delta[i].faza == -1) write_string(lat, "(-1)");
        latex_print_kronecker(lat, latex_delta[i]);
	if (i % divider2 == divider2 - 1) {nonumber(lat); newline(lat); write_string(lat, "~&+~"); continue;}

	write_string(lat, "~+~");
        }
//write_string(&lat, "~=~");

if (latex_delta[lat_p-1].faza == -1) write_string(lat, "(-1)");

latex_print_kronecker(lat, latex_delta[lat_p -1]);

//write_string(lat, "\\\\");

//be_eq(lat,"end","multline");
be_eq(lat,"end","align");
end_latex_document(lat);

finish_latex_file(lat);

if (lat->show == 1){
    char command[80];
    sprintf (command, "%s %s &", lat->program_name, "latout.pdf");
    system(command);
    
    }

return;


zero_rez:
	print_latex_zero(lat);
	be_eq(lat,"end","align");
	end_latex_document(lat);

	finish_latex_file(lat);
return;
}


static void error_message(char *s){
fprintf (stderr, "%s!\n", s);
exit(10);
return;
}

static void finish_latex_file(latex_info_t *lat){
fclose(lat->LF);
return;
}

void create_pdf_from_latex_file(latex_info_t *lat){
char command[80];
sprintf (command, "pdflatex %s > /dev/null 2>&1", lat->latex_f);
system(command);
system(command);
return;
}


static void open_latex_file(latex_info_t *lat){
char s[2];
s[0] = lat->opt; s[1] = '\0';
printf ("Write/append file %s - option: %s\n", s, lat->latex_f);
if ((lat->LF = fopen(lat->latex_f, s)) == NULL){
	error_message("Opening file was not successful!\n");
	}
//lopen = 1;
return;
}


void prepair_latex_headers(latex_info_t *lat){
printf ("Prepairing latex headers.... \n");
fprintf (lat->LF, "\\documentclass[12pt,a4paper]{article}\n");

fprintf (lat->LF, "\\usepackage[utf8]{inputenc}\n");

fprintf (lat->LF, "\\ifx\\pdftexversion\\undefined\n");
fprintf (lat->LF, "\\usepackage[dvips]{graphicx}\n");
fprintf (lat->LF, "\\else\n");
fprintf (lat->LF, "\\usepackage[pdftex]{graphicx}\n");
fprintf (lat->LF, "\\fi\n");
//fprintf (lat->LF, "\\allowdisplaybreaks\n");
fprintf (lat->LF, "\\usepackage{simpler-wick}\n");

fprintf (lat->LF, "\\usepackage[croatian]{babel}\n");

//fprintf (lat->LF, "\\usepackage[hidelinks]{hyperref}\n");

fprintf (lat->LF, "\\usepackage{charter}\n");
fprintf (lat->LF, "\\usepackage[OT1]{fontenc}\n");
fprintf (lat->LF, "\%\%http://www.tug.dk/FontCatalogue/mathfonts.html\n");

fprintf (lat->LF, "\\usepackage[]{amssymb}\n");
fprintf (lat->LF, "\\usepackage[]{mathrsfs}\n");


fprintf (lat->LF, "\\usepackage{xcolor}\n");
//fprintf (lat->LF, "\\usepackage{listings}\n");
fprintf (lat->LF, "\\usepackage{caption}\n");

fprintf (lat->LF, "\\usepackage[most]{tcolorbox}\n");
fprintf (lat->LF, "\\usepackage{inconsolata}\n");

//fprintf (lat->LF, "\\tcbuselibrary{theorems}\n");
fprintf (lat->LF, "\\tcbuselibrary{skins}\n");
fprintf (lat->LF, "\\tcbuselibrary{breakable}\n");


fprintf (lat->LF, "\\setlength{\\paperwidth}{210mm}\n");
fprintf (lat->LF, "\\setlength{\\paperheight}{297mm}\n");
fprintf (lat->LF, "\%\%margine\n");
fprintf (lat->LF, "\\setlength{\\hoffset}{4.6mm}\n");
fprintf (lat->LF, "\\setlength{\\oddsidemargin}{0pt}\n");
fprintf (lat->LF, "\\setlength{\\marginparwidth}{0pt}\n");
fprintf (lat->LF, "\\setlength{\\marginparsep}{0pt}\n");
fprintf (lat->LF, "\%\%text\n");
fprintf (lat->LF, "\\setlength{\\textheight}{252mm}\n");
fprintf (lat->LF, "\\setlength{\\textwidth}{155mm}\n");
fprintf (lat->LF, "\%\%header\n");
fprintf (lat->LF, "\\setlength{\\voffset}{-0.4mm}\n");
fprintf (lat->LF, "\\setlength{\\headheight}{0pt}\n");
fprintf (lat->LF, "\\setlength{\\topmargin}{0pt}\n");
fprintf (lat->LF, "\\setlength{\\headsep}{0pt}\n");
fprintf (lat->LF, "\%\%footer\n");
fprintf (lat->LF, "\\setlength{\\footskip}{10mm}\n");

//fprintf (lat->LF, "\\usepackage{cite}\n");
//fprintf (lat->LF, "\\usepackage[title]{appendix}\n");

fprintf (lat->LF, "\\usepackage{sectsty}\n");
fprintf (lat->LF, "\\subsectionfont{\\itshape}\n");

fprintf (lat->LF, "\\linespread{1.2}\n");
fprintf (lat->LF, "\\allowdisplaybreaks\n");

printf (".... end of prepairing latex headers!\n");
return;
}


latex_data2_t ** create_latex_data2_non_complete(int c){
latex_data2_t ** temp;
temp = (latex_data2_t**)malloc(sizeof(latex_data2_t*)*c);
return temp;
}

void latex_prepair_kronecker(latex_data4_t *data, kronecker_t *delta, int n, int rez){
printf ("Creating array of Kronecker deltas as latex objects...\n");
data->delta = create_field_kronecker(n);
printf ("... created!\n");
data->n = n;
copy_kronecker_field(&(data->delta[0]), delta, n);
printf ("Copying Kronecker deltas to latex objects\n");
data->faza = rez;
return;
}

void latex_change_index(char *str, char *s){
register int i = 0, j = 0;
while (s[i] != '\0'){
	if (((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) && (*(s+1) >= '0' && *(s+1) <= '9')){
                        str[j++] = *s;
                        str[j++] = '_';
                        }
                else str[j++] = *s;
                s++;
	}
str[j] = '\0';
return;
}


void latex_print_kronecker(latex_info_t* lif, latex_data4_t data){
register int i;
char ind1[30], ind2[30];
	
for (i = 0; i < data.n; i++){
	latex_change_index(ind1, data.delta[i].ind1);
	latex_change_index(ind2, data.delta[i].ind2);
	fprintf (lif->LF, "\\delta_{%s %s}", ind1, ind2);
	if (data.delta[i].fermi == 1)
		//fprintf (lif->LF, "\\Theta(\\epsilon_{%s} - \\epsilon_F)", ind1);
        fprintf (lif->LF, "\\Theta_{\\epsilon_{%s} \\epsilon_F}", ind1);
	else if (data.delta[i].fermi == -1){
		//fprintf (lif->LF, "\\Theta(\\epsilon_F - \\epsilon_{%s})", ind1);
        fprintf (lif->LF, "\\Theta_{\\epsilon_F \\epsilon_{%s}}", ind1);
		}
	}
return;
}


void latex_prepair_contractions(latex_data2_t *data, directed_line_t *dline, operator_t *op, short c, short p, int n){
register int i;
printf ("Creating operators...\n");
data->op = create_operators(n);
printf ("... created!\n");
data->n = n;

for (i = 0; i < n; i++){
	printf ("Copying operator... %d/%d\n",i,n);
        copy_operator2(&(data->op[i]),op[i]);
        }

//Aha tu si!!!
data->beg = (short*)_1Ds(n/2);
data->end = (short*)_1Ds(n/2);
for (i = 0; i < n/2; i++){
	data->beg[i] = (short)dline[i].beg;
	data->end[i] = (short)dline[i].end;
	}
data->exist = 1;
data->c = c;
data->p = p;
printf ("Latex contraction prepaired!\n");
return;
}


void print_contractions(latex_info_t *lif, latex_data2_t data, short bracket){
register int i, j, k1 = 0, k2 = 0;

if (bracket == 1 || bracket == 2){
        fprintf (lif->LF, "\\langle HF |");
        }
char dag[] = "^\\dagger";
char t, str[10], *s;
fprintf (lif->LF, "\\wick[offset=1.2em]{");
for (i = 0; i < data.n; i++){
        t = data.op[i].t;
	for (k1 = 0; k1 < data.n/2; k1++)
		if (data.beg[k1] == i){
			fprintf (lif->LF, "\\c%d ", k1+1);
		}
	for (k2 = 0; k2 < data.n/2; k2++)
		if (data.end[k2] == i){
			fprintf (lif->LF, "\\c%d ", k2+1);
		}
        j = 0;
        s = &(data.op[i].ind[0]);
        while (*s != '\0'){
                if (((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) && (*(s+1) >= '0' && *(s+1) <= '9')){
                        str[j++] = *s;
                        str[j++] = '_';
                        }
                else str[j++] = *s;
                s++;
                }
	str[j] = '\0';
        if (data.op[i].c == 1) {
                fprintf (lif->LF, "%c%s_{%s}",t,dag,str);
                }
        else
                fprintf (lif->LF, "%c_{%s}",t,str);
        }

fprintf (lif->LF, "}");
if (bracket == 1 || bracket == 3){
        fprintf (lif->LF, "| HF \\rangle");
        }

return;
}


void print_pure_operators(latex_info_t *lif, latex_data3_t data, short bracket){
register int i, j;

if (bracket == 1 || bracket == 2){
	//fprintf (lif->LF, "\\left\\langle HF | ");
	fprintf (lif->LF, "\\langle HF | "); 
	}
char dag[] = "^\\dagger";
char t, str[10], *s;

for (i = 0; i < data.n; i++){
        t = data.op[i].t;
	j = 0;
	s = &(data.op[i].ind[0]);
        while (*s != '\0'){
		if (((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) && (*(s+1) >= '0' && *(s+1) <= '9')){
			str[j++] = *s;
			str[j++] = '_';//cudno
			}
		else str[j++] = *s;
		s++;
		}
	str[j] = '\0';
        if (data.op[i].c == 1) {
                fprintf (lif->LF, "%c%s_{%s}",t,dag,str);
                }
        else
                fprintf (lif->LF, "%c_{%s}",t,str);
        }
if (bracket == 1 || bracket == 3){
	//fprintf (lif->LF, "| HF \\right\\rangle");
	fprintf (lif->LF, "| HF \\rangle");
	}
return;
}



void latex_prepair_operators(latex_data3_t *data, operator_t *op, int n){
register int i;
printf ("Creating operators for tex document...\n");
data->op = create_operators(n);
printf ("... created!\n");
data->n = n;
//sleep(1);

for (i = 0; i < n; i++){
	copy_operator2(&(data->op[i]),op[i]);
	}
printf ("Operators are copied!\n");
return;
}

