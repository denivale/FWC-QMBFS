//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 22 2019
 - last modification May 15 2023 (D. Vale)
*/
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "draw.h"
#include "operator.h"
#include "point.h"
#include "line.h"

static void create_necessary_files(drawing_data_t, gp_t);
static void show_ps_file(char *);
static int create_latex_ps_file(gp_t);
//static void draw_standalone_contractions(info_draw_t, drawing_data_t, short);

static void print_points_to_file(FILE*, char *, point_t *, int, short, short);
static void error_opening(char *);

static void error_opening(char *s){
fprintf (stderr, "Failed to create %s!\n", s);
exit(3);
return;
}


static void print_points_to_file(FILE* fp, char *filename, point_t *T, int n, short name_yno, short info){
int i;

if ((fp = fopen(filename, "w")) == NULL) 
	error_opening(filename);

if (name_yno == 1)
	for (i = 0; i < n; i++){
		fprintf (fp, "%lf\t%lf\t$%s$\n", T[i].x, T[i].y, T[i].name);
		}
else {
	for (i = 0; i < n; i++){
                fprintf (fp, "%lf\t%lf\n", T[i].x, T[i].y);
                }
	}
if (info == 1)
	fprintf (stdout, "Created file %s! <<<<\n", filename);
fclose(fp);
return;
}



static void print_vectors_to_file(FILE* fp, char *filename, point_t *T, directed_line_t *dline, int n, short info){
int i;

if ((fp = fopen(filename, "w")) == NULL)
        error_opening(filename);

for (i = 0; i < n/2; i++){
         fprintf (fp, "%lf\t%lf\t%lf\t%lf\n", T[dline[i].beg].x, T[dline[i].beg].y, T[dline[i].end].x -T[dline[i].beg].x, T[dline[i].end].y -T[dline[i].beg].y);
        }

if (info == 1)
         fprintf (stdout, "Created file %s! <<<<\n", filename);
fclose(fp);
return;
}





static void create_necessary_files(drawing_data_t d, gp_t gp){
print_points_to_file(gp.PF, gp.point_f, d.T, d.n, 1, 1);
print_vectors_to_file(gp.VF, gp.vector_f, d.T, d.dline, d.n, 1);
print_points_to_file(gp.IF, gp.inter_f, d.I, d.i, 0, 1);

return;
}



static int create_latex_ps_file(gp_t gp){
char command[80];
sprintf (command, "gnuplot %s > /dev/null 2>&1", gp.gplot_f);
system(command);
sprintf (command, "latex %s > /dev/null 2>&1", gp.output);
system(command);
sprintf (command, "dvips -o %s %s > /dev/null 2>&1", gp.ps_f, gp.dvi_f);
system(command);
sprintf (command, "dvips -E* -o %s %s > /dev/null 2>&1", gp.eps_f, gp.dvi_f);
system(command);
sprintf (command, "mv %s* %s/", gp.rep_part, gp.folder_name);
system(command);
return 1;
}


static void show_ps_file(char *s){
char command[80];
sprintf (command, "evince %s &", s);
system(command);
}


static void create_standalone_gnuplot_file(gp_t gp){

if ((gp.GP = fopen(gp.gplot_f, "w")) == NULL)
        error_opening(gp.gplot_f);

fprintf (gp.GP, "#\\bin\\gnuplot\n");
fprintf (gp.GP, "set terminal epslatex size %.4g,%.4g standalone color colortext 14\n", gp.size, gp.size);
fprintf (gp.GP, "set output \'%s\'\n", gp.output);
fprintf (gp.GP, "set size square\n");
fprintf (gp.GP, "set xrange [%.4g:%.4g]\n", gp.x1, gp.x2);
fprintf (gp.GP, "set yrange [%.4g:%.4g]\n", gp.y1, gp.y2);
if (gp.test == 0){
        fprintf (gp.GP, "unset key; unset tics; unset border\n");
}
fprintf (gp.GP, "r = %.4g\n", gp.r);
fprintf (gp.GP, "s = %.4g\n", gp.s);
fprintf (gp.GP, "s2 = %.4g\n", gp.s2);
//fprintf (gp.GP, "set object 1 circle at %.4g,%.4g size %.4g fs transparent solid 0.15 noborder\n", gp.s, gp.s, gp.r);
fprintf (gp.GP, "set object 1 circle at %.4g,%.4g size %.4g fs transparent solid 0.25 fillcolor rgb \"orange\" lw 1\n", gp.s, gp.s, gp.r);
//fprintf (gp.GP, "unset object\n");
fprintf (gp.GP, "plot \"%s\" u ($1+%.4g):($2+%.4g):3 with labels point pt 7 ps 2 offset char %.1d,%.1d notitle, \\\n", gp.point_f, gp.s, gp.s, gp.offset, gp.offset);

if (gp.si == 1){
	fprintf (gp.GP, "\"%s\" using ($1+%.4g):($2+%.4g):($3+%.4g):($4+%.4g) with vectors filled head lw 2 notitle; \\\n", gp.vector_f, gp.s, gp.s, gp.s2, gp.s2);
	fprintf (gp.GP, "unset object\n");
	}
else {

	fprintf (gp.GP, "\"%s\" using ($1+%.4g):($2+%.4g):($3+%.4g):($4+%.4g) with vectors filled head lw 2 notitle, \\\n", gp.vector_f, gp.s, gp.s, gp.s2, gp.s2);
	fprintf (gp.GP, "\"%s\" u ($1+%.4g):($2+%.4g) with point pt 7 ps 2 pc 1;\n", gp.inter_f, gp.s, gp.s);
	fprintf (gp.GP, "unset object\n");
	}

fclose(gp.GP);

return;
}



static void fill_necessary_buffers(info_draw_t info, gp_t *gp){


sprintf (gp->gplot_f, "%s/%s%.1d_%.1d.gnu", gp->folder_name, info.infopart, info.c, info.p);
sprintf (gp->point_f, "%s/point%.1d_%.1d.dat", gp->folder_name, info.c, info.p);
sprintf (gp->vector_f, "%s/vector%.1d_%.1d.dat",gp->folder_name, info.c, info.p);
sprintf (gp->inter_f, "%s/inter%.1d_%.1d.dat", gp->folder_name, info.c, info.p);//ovo ce cesto biti prazna datoteka!
sprintf (gp->output, "%s%.1d_%.1d.tex", info.infopart, info.c, info.p);
sprintf (gp->dvi_f, "%s%.1d_%.1d.dvi", info.infopart, info.c, info.p);
sprintf (gp->ps_f, "%s%.1d_%.1d.ps", info.infopart, info.c, info.p);
sprintf (gp->eps_f, "%s%.1d_%.1d.eps", info.infopart, info.c, info.p);
sprintf (gp->rep_part, "%s%.1d_%.1d", info.infopart, info.c, info.p);
printf ("... Filling buffers!\n");

return;
}

short fe = 0;;
static void prepair_folder(gp_t gp){
if (fe++ > 0) return;
char text[80];
sprintf(text, "if test -d %s; then rm -rf %s; fi", gp.folder_name, gp.folder_name);
system(text);
sprintf(text, "mkdir %s", gp.folder_name);
system(text);
return;
}

static void prepair_and_create_gnuplot_file(info_draw_t info, drawing_data_t d){

gp_t gp;

fill_necessary_buffers(info, &gp);
create_necessary_files(d, gp);

printf ("All necessary files created!\n");

printf (">>>\n");
printf ("Prepairing gnuplot file!\n");
gp.x1 = gp.y1 = 0.55;
gp.x2 = gp.y2 = 2.55;
gp.offset = 1;
gp.r = 1.0;
gp.s = 1.0;
gp.s2 = 0.0;
gp.size = 4.5;
gp.test = 0;

sprintf (gp.folder_name, "VISUAL");

printf ("Prepairing folder for geometrical representation of Wick's contractions:\n");
printf ("%s\n", gp.folder_name);

create_standalone_gnuplot_file(gp);

printf ("<<<\n");
printf ("Gnuplot file is created!\n");

create_latex_ps_file(gp);
if (info.show == 1){
        show_ps_file(gp.eps_f);
        }
return;
}

void test_gnuplot_file_print(){
gp_t gp;
info_draw_t info;

sprintf (info.infopart, "test_sa");
info.p = 0;
info.c = 0;
info.show = 1;
fill_necessary_buffers(info, &gp);
//create_necessary_files(d, gp);

//printf ("Stvorene kljucne datoteke!\n");

printf (">>>\n");
printf ("Prepairing gnuplot file\n");
gp.x1 = gp.y1 = 0.55;
gp.x2 = gp.y2 = 2.55;
gp.offset = 1;
gp.r = 1.0;
gp.s = 1.0;
gp.s2 = 0.0;
gp.size = 4.5;
gp.test = 0;

create_standalone_gnuplot_file(gp);


return;
}


void draw_sa_file(info_draw_t info, drawing_data_t d){
gp_t gp;

if (info.prepair == 0) return;

printf ("info.infopart = %s\n", info.infopart);
printf ("info.p = %d\n", info.p);
printf ("info.c = %d\n", info.c);
printf ("info.show = %d\n", info.show);
printf ("info.draw = %d\n", info.draw);

sprintf (gp.folder_name, "VISUAL");
printf ("Prepairing folder for geometrical representation of Wick's contractions:\n");
printf ("%s\n", gp.folder_name);

prepair_folder(gp);


fill_necessary_buffers(info, &gp);

create_necessary_files(d, gp);
printf ("Created necessary files!\n");

printf (">>>\n");
printf ("Prepair gnuplot file!\n");
gp.x1 = gp.y1 = -1.55;
gp.x2 = gp.y2 = 1.55;
gp.offset = 1;
gp.r = 1.0;
gp.s = 0.0;
gp.s2 = 0.0;
gp.size = 4.5;
gp.test = 0;
gp.si = 0;

if (d.i == 0)
	gp.si = 1;

create_standalone_gnuplot_file(gp);


printf ("<<<\n");
printf ("Created file!\n");

if (info.draw == 0)
	return;

create_latex_ps_file(gp);
if (info.show == 1){
        show_ps_file(gp.eps_f);
        }


return;
}



//=================================================================================================
/*
   Function void fill_drawing_data(drawing_data_t * data, int n, int inter, point_t * T, 
    directed_line_t *length, point_t * I)
   Description:
    Function creates key elements for visual representation of Wick contractions
   Input arguments:
     data - the address of the data from which the image is obtained.
     n - number of operators (vertices of n-triangles)
     inter - number of intersections
     T - point array address (type point_t*)
     dline - vector array address (type directed_line_t*)
     I - point array address (type point_t*)
*/
//=================================================================================================
void fill_drawing_data(drawing_data_t * data, int n, int inter, point_t * T, directed_line_t *dline, point_t * I){
register int i;
data->n = n;
data->i = inter;

printf ("Prepair drawing data...\n");

data->T = create_empty_points(n);
for (i = 0; i < n; i++){
        complete_copy_point(&(data->T[i]), T[i]);
        }

data->dline = create_empty_directed_lines(n/2);
for (i = 0; i < n/2; i++){
        complete_copy_dline(&(data->dline[i]), dline[i]);
        }

if (inter < 1) return;
data->I = create_empty_points(inter);
for (i = 0; i < inter; i++){
        complete_copy_point(&(data->I[i]), I[i]);
        }

printf ("... prepaired!\n");

return;
}


void free_drawing_data(drawing_data_t * data){
if (data->i > 0) free(&data->I[0]);
if (data->n > 0) free(&data->dline[0]);
if (data->n > 0) free(&data->T[0]);
return;
}


void fill_drawing_info(info_draw_t *info, char pvr, char dvr, char svr, char *program_name){

strcpy(info->infopart, "sa");
strcpy(info->program_name, program_name);
if (pvr == 'p') info->prepair = 1;
else {
	info->prepair = 0;
	info->draw = 0;
	info->show = 0;

	return;
	}
if (dvr == 'd'){
	info->draw = 1;
	}
else {
	info->draw = 0;
	info->show = 0;

	return;
	}
if (svr == 's'){
	info->show = 1;
	}
else {
	info->show = 0;
	}
return;
}
