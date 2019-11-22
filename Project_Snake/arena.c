#include<stdio.h>
#include<stdlib.h>
#include "arena.h"
#include "cellList.h"

struct arena A_new(int nb_rows, int nb_cols){
	struct arena a;
	a.nb_rows=nb_rows;
	a.nb_cols=nb_cols;
	a.arr[a.nb_rows][a.nb_cols];
	for(int i=0;i<=nb_rows;i++){
		for(int j=0;j<nb_cols;j++){
			a.arr[i][j]=0;
		}
	}
}




int A_isInside(struct cell c, struct arena ar){
	if(c.row<=ar.nb_rows && c.col<=ar.nb_cols){
		return 1;
	}else return 0;
}




