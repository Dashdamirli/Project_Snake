#ifndef __ARENA_H__
#define __ARENA_H__

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "cellList.h"


struct arena {
	int nb_rows;
	int nb_cols;
	int arr[][1000];
};

struct arena A_new(int nb_rows, int nb_cols);
int A_isInside(struct cell c, struct arena ar);





#endif