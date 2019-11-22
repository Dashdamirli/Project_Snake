#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "cellList.h"
#include "arena.h"
#include "ppm.h"



struct cell CL_random(struct cellList cl){
	
	int i = rand()%cl.size;
	//printf("%d--size--\n",cl.size);
	// printf("%d--random_number--\n",i);
	if(cl.size<=0){
		printf("Empty");
		exit(1);
	}else{
		return cl.arr[i];
	}
}

struct cellList CL_neighbors(struct cell c, struct arena ar){
	struct cellList c1;

	ar.arr[c.row][c.col]=1;
	int i=0;

	//upper
	if((c.row-1)<ar.nb_rows && (c.row-1)>=0){
		c1.arr[i].row=c.row-1;  
		c1.arr[i].col=c.col;
		i++;
	}

	//lower
	if((c.row+1)<ar.nb_rows && (c.row+1)>=0){
		c1.arr[i].row=c.row+1; 
		c1.arr[i].col=c.col;
		i++;
	}
	

	//left
	if(c.col-1<ar.nb_cols && (c.col-1)>=0){
		c1.arr[i].row=c.row;   
		c1.arr[i].col=c.col-1;
		i++;
	}

	//right
	if(c.col+1<ar.nb_cols && (c.col+1)>=0){
		c1.arr[i].row=c.row;   //right
		c1.arr[i].col=c.col+1;  
		i++;
	}
	c1.size=i;
	return c1;
}

struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar){
	struct cellList cl=CL_new();
	struct cell c;

	cl=CL_add(cl,start);
	int area[ar.nb_rows][ar.nb_cols];
	for(int i=0;i<=ar.nb_rows;i++){
		for(int j=0;j<ar.nb_cols;j++){
			area[i][j]=0;
		}
	}
	area[start.row][start.col]=1;
	int i=1;
	int k=0;
	while(i<(nb_cells)){
		struct cell random_following = CL_random(CL_neighbors(cl.arr[i-1],ar));
		// C_print(random_following,"sad");
		if(area[random_following.row][random_following.col]==0 && random_following.row>0 && random_following.col>0){
			area[random_following.row][random_following.col]=1;
			cl=CL_add(cl,random_following);
			i++;
		}else{
			k++;
			if(k==100) break;
		}
		
	}
	return cl;
}


void CL_draw(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.7;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	struct cell c = CL_get(cl,0);
	img = PPM_drawCell(img, c.row, c.col);

	for(int i=1; i<cl.size;i++)
	{
		struct cell c = CL_get(cl,i);
		struct cell c2 = CL_get(cl,i-1);
		img = PPM_drawLink(img, c.row, c.col, c2.row, c2.col);
		img = PPM_drawCell(img, c.row, c.col);
	}
	sprintf(ppm_file_name,"%s.ppm",ppm_name);
	PPM_save(img,ppm_file_name);
}

void CL_animate(struct cellList cl, int nb_rows, int nb_cols, char *ppm_name)
{
	int pixels_per_cell = 20;
	char ppm_file_name[50];
	float proportion_serpent = 0.7;
	struct ppm img = PPM_new(nb_rows, nb_cols, pixels_per_cell, proportion_serpent);
	img = PPM_drawBG(img);

	struct cell c = CL_get(cl,0);
	img = PPM_drawCell(img, c.row, c.col);
	sprintf(ppm_file_name,"%s_%02d.ppm",ppm_name,0);
	PPM_save(img,ppm_file_name);

	for(int i=1; i<cl.size;i++)
	{
		struct cell c = CL_get(cl,i);
		struct cell c2 = CL_get(cl,i-1);
		img = PPM_drawLink(img, c.row, c.col, c2.row, c2.col);
		img = PPM_drawCell(img, c.row, c.col);

		sprintf(ppm_file_name,"%s_%02d.ppm",ppm_name,i);
		PPM_save(img,ppm_file_name);
	}
}

struct cell CL_get(struct cellList cl, int ind){
	if(cl.size<ind){
		printf("Cell List is empty");
		exit(1);
	}else{
		return cl.arr[ind];
	}
}


struct cellList CL_new(){
	struct cellList c;
	c.size=0;
	return c;
}

struct cellList CL_add(struct cellList cl, struct cell c){
	cl.arr[cl.size]=c;
	cl.size++;
	return cl;
}

void CL_print(struct cellList c, char *label){
	printf("%s\n",label);
	for(int i=0;i<c.size;i++){
		printf("%d : (%d,%d)\n",i,c.arr[i].row,c.arr[i].col);
	}
}





