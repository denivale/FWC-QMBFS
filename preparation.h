//========================================================================
/*
D. Vale, N. Paar 
 - created Jan 31 2019
 - last modification May 21 2023 (D. Vale)
*/
//========================================================================
#ifndef _PREPARATION_H
#define _PREPARATION_H

#include "latex.h"
#include "draw.h"

typedef struct{
all_operator_t all_op;
} input_t;

typedef struct{
input_t in;
latex_info_t lat;
info_draw_t draw;
} prep_t;

prep_t preparation(option_t option);

#endif
