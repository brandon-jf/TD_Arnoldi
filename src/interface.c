#include<stdio.h>
#include<stdlib.h>
#include"interface.h"
#include"matrice.h"
#include<errno.h>
#include<time.h>

double* LectureMatrice(int nb_ligne, int nb_colonne, double* matrice,char *name){
  FILE* fp=NULL;
  int ij = 0;
  int seed = clock();

  if(matrice==NULL){
    matrice = malloc(sizeof(double*)*nb_ligne*nb_colonne);
  }
  fp = fopen(name,"r");
  if(!(fp)) {
    perror("Il ne trouve pas matrice.mat pour la lecture");
    matrice = Create_rand_mat(nb_ligne,matrice);
  }else{
    for(int i=0; i<nb_ligne; i++){
      for(int j=0; j<nb_colonne; j++){
        ij = i*nb_colonne + j;
        fscanf(fp,"%lf\t",&matrice[ij]);
      }
    }
    fclose(fp);
  }

    return matrice;
}
void Affichage_Matrice(int nb_ligne, int nb_colonne, double* matrice){
  int ij =0;
  if(matrice == NULL){
    printf("Erreur : Matrice inexistane !");

  }
  for(int i=0; i < nb_ligne; i++){
    for(int j=0; j < nb_colonne; j++){
      ij = i*nb_colonne + j;
      printf("%lf\t",matrice[ij]);
    }
    printf("\n");
  }
}
