#include"matrice.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


double* Create_rand_mat(int dim,double* matrice){
  int seed = clock();
  srand(seed);
  int ij;
  if(dim == 0){
    printf("dimension nulle\n ");
    return matrice;
  }
  //Si la matrice n'est pas encore alloué , alouant le a la bonne taille
  if(matrice == NULL) matrice = malloc(sizeof(double*)*dim);

  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      ij = i*dim + j;
      matrice[ij] = (double) rand()/RAND_MAX;
      if(i==j) matrice[ij]=matrice[ij]*10;
    }
  }
  return matrice;
}

void Write_mat(int m, int n,double* mat, char* name){
  FILE* fp =NULL;
  int ij;
  if(name != NULL){
    fp = fopen(name,"w+");
  }else{
    printf("Aucun nom a données\n");
  }

  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      ij = i*n + j;
      fprintf(fp,"%lf\t",mat[ij]);
    }
    printf("\n");
  }
  fclose(fp);
}

void init_vect(int dim, double* vect){
	srand(time(NULL));
	for(int i = 0; i < dim; i++){
		vect[i]= rand()*10.0/(double)RAND_MAX;
	}
}
