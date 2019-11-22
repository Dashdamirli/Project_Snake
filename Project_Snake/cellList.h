#ifndef __CELLLIST_H__
#define __CELLLIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "ppm.h"
#include "arena.h"

#define CL_MAX 1000

struct cellList
{
	int size;
	struct cell arr[CL_MAX];
};

struct cellList CL_new();
struct cellList CL_add(struct cellList cl, struct cell c);
void CL_print(struct cellList c, char *label);
struct cell CL_get(struct cellList cl, int ind);
struct cell CL_random(struct cellList cl);


struct cellList CL_neighbors(struct cell c, struct arena ar);
struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar);


void CL_draw(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name);
void CL_animate(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name);





#endif