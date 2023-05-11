#include <stdio.h>
#include <stdlib.h>

#include "reading.h"
#include "operator.h"
#include "draw.h"
#include "transindex.h"
#include "latex.h"
#include "canonical.h"
#include "preparation.h"

prep_t preparation(option_t option){
prep_t temp;
all_operator_t all_op;
paramet_t par;

printf ("Preparation of input ....\n");
printf ("Reading input parameters...\n");

read_parameters(option, &par);

latex_fill_info(&temp.lat, par.pld, par.wld, par.sld, par.program_name);

fill_drawing_info(&temp.draw, par.pvr, par.dvr, par.svr, par.program_name);

printf ("... reading input parameters done!\n");

printf ("Reading input arrangement of operators from file ...\n");
if (option.type == 'f')
        all_op = read_input_from_file(option.filename);

printf ("... reading input arrangement of operators from file done!");

print_all_operator(all_op);

int war, trans;
short count;


war = warning_repeating_indices(all_op.op, all_op.n);
if (war != 0) printf ("Some indices are repeating!\n");


temp.in.all_op = transformation_of_indices_if_needed(all_op, par, &trans);


print_all_operator(temp.in.all_op);

free_all_operator(&all_op);

printf ("... end of preparation of input!\n");


return temp;
}

