#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "cellList.h"
#include "arena.h"


int	main(int argc, char const *argv[])
{
	srand(time(0));
	struct cell c1 = C_new(3,3);
	struct cell c2 = C_new(0,0);
	struct cell c3 = C_new(4,4);
	struct cell c4 = C_new(1,8);
	struct cell c5 = C_new(4,2);
	struct cell c6 = C_new(5,4);
	struct cell c7 = C_new(2,8);
	struct cellList cl1=CL_new();
	cl1=CL_add(cl1,c1);
	cl1=CL_add(cl1,c2);
	cl1=CL_add(cl1,c3);

	// CL_print(cl1,"first list");
	// struct cellList cln =CL_new();
	// cln=CL_neighbors(c1);
	// CL_print(cln,"neighbors");
	// c1=CL_random(cl1);

	// C_print(CL_random(CL_neighbors(c1)),"random");

	struct arena ar;
	ar.nb_cols=10;
	ar.nb_rows=10;

	struct cellList cr = CL_new();
	cr=CL_randomPath(c1,20,ar);
	CL_print(cr,"random path");

	CL_draw(cr, ar.nb_rows, ar.nb_cols, "snake");
	CL_animate(cr, ar.nb_rows, ar.nb_cols, "snake");


	return 0;
}


struct cell CL_random(struct cellList cl){
	
	int i = rand()%cl.size;
	//printf("%d--size--\n",cl.size);
	printf("%d--random_number--\n",i);
	if(cl.size<=0){
		printf("Empty");
		exit(1);
	}else{
		return cl.arr[i];
	}
}

struct cellList CL_neighbors(struct cell c, struct arena ar){
	struct cellList c1;
	// c1.size=4;

	// struct cell cc = c;
	// cc.row=c.row-1;			//upper
	// c1=CL_add(c1,cc);
	ar.arr[c.row][c.col]=1;
	int i=0;
	if((c.row-1)<ar.nb_rows && (c.row-1)>=0 && ar.arr[c.row-1][c.col]==0){
		c1.arr[i].row=c.row-1;  //upper
		c1.arr[i].col=c.col;
		ar.arr[c.row-1][c.col]=1;
		i++;
	}
	// cc.row=c.row+1;			//lower
	// c1=CL_add(c1,cc);
	if((c.row+1)<ar.nb_rows && (c.row+1)>=0 && ar.arr[c.row+1][c.col]==0){
		c1.arr[i].row=c.row+1; //lower
		c1.arr[i].col=c.col;
		ar.arr[c.row+1][c.col]=1;
		i++;
	}
	// cc=c;
	// cc.col=c.col-1;			//left
	// c1=CL_add(c1,cc);   
	if(c.col-1<ar.nb_cols && (c.col-1)>=0 && ar.arr[c.row][c.col-1]==0){
		c1.arr[i].row=c.row;   //left
		c1.arr[i].col=c.col-1;
		ar.arr[c.row][c.col-1]=1;
		i++;
	}
	// cc.col=c.col+1;			//right
	// c1=CL_add(c1,c);
	if(c.col+1<ar.nb_cols && (c.col+1)>=0 && ar.arr[c.row][c.col+1]==0){
		c1.arr[i].row=c.row;   //right
		c1.arr[i].col=c.col+1;  
		ar.arr[c.row][c.col+1]=1;
		i++;
	}
	c1.size=i;
	return c1;
}

struct cellList CL_randomPath(struct cell start, int nb_cells, struct arena ar){
	struct cellList cl=CL_new();
	struct cell c;
	cl=CL_add(cl,start);
	// cl.arr[0]=start;
	int i=1;
	while(i<(nb_cells)){
		struct cell random_following = CL_random(CL_neighbors(cl.arr[i-1],ar));
		//C_print(random_following,"sad");
		cl=CL_add(cl,random_following);
		i++;
	}
	return cl;
}

// struct cellList CL_randomPath(struct cell start, int nb_cells){


	
// 	struct cellList randomList=CL_new();
// 	randomList=CL_add(randomList,start);

// 	for (int i = 1; i < nb_cells; i++)
// 	{
// 		/* code */
// 		struct cell previous=randomList.arr[i-1];
// 		struct cell random_following= CL_random(CL_neighbors(previous)) ;
// 		C_print(random_following,"Random");
// 		randomList=CL_add(randomList,random_following);

// 	}

// 	return randomList;


// }

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



// struct cellList CL_neighbors(struct cell c, struct arena ar){
// 	struct cellList c1;

// 	ar.arr[c.row][c.col]=1;
// 	int i=0;
// 	if((c.row-1)<ar.nb_rows && (c.row-1)>=0 && c1.c.row-1==0 && c1.c.col==0){
// 		c1.arr[i].row=c.row-1;  //upper
// 		c1.arr[i].col=c.col;
// 		c1.c.row-1=1;
// 		c1.c.col=1;
// 		i++;
// 	}

// 	if((c.row+1)<ar.nb_rows && (c.row+1)>=0 && c.row+1==0 && c.col==0){
// 		c1.arr[i].row=c.row+1; //lower
// 		c1.arr[i].col=c.col;
// 		c.row+1=1;
// 		c.col=1;
// 		i++;
// 	}
 
// 	if(c.col-1<ar.nb_cols && (c.col-1)>=0 && c.row==0 && c.col-1==0){
// 		c1.arr[i].row=c.row;   //left
// 		c1.arr[i].col=c.col-1;
// 		c.row=1;
// 		c.col-1=1;
// 		i++;
// 	}

// 	if(c.col+1<ar.nb_cols && (c.col+1)>=0 && c.row==0 && c.col+1==0){
// 		c1.arr[i].row=c.row;   //right
// 		c1.arr[i].col=c.col+1;  
// 		c.row=1;
// 		c.col+1=1;
// 		i++;
// 	}
// 	c1.size=i;
// 	return c1;
// }