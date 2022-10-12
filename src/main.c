#include<stdio.h>
#include<stdlib.h>
#include"interface.h"
#include"arnoldi.h"
#include<string.h>
#include<time.h>
#define BILLION 1E9


int main(int argc, char** argv){
  int m,n,dim;
  double* matrice; // matrice a donné a l'algo
  char nom_matrice[50]; //nom du fichier qui contient la matrice
  char first[50];
  char name_file[50];
  double* v; // Vecteur initial
  double* Vm; //vecteur caculer par arnoldi
  int start, end;
  unsigned long duree_ns[1000];
  double duree_mean, variance;
  int duree_ipc;
  struct timespec t1,t2;
  FILE* fp;
  if(argc == 4){
   m = atoi(argv[1]);
    n = atoi(argv[2]);
    memcpy(argv[3],nom_matrice,sizeof(char*)*50);
    strncpy(name_file,argv[4],50);

    /*printf("Erreur : arnoldi [n] [m] [p] \n"
    "-dimention de la matrice [n]\n"
    "-dimension du sous-espace de Krylov [m]\n"
    "-l'adresse vers le fichie de la matrice[path]\n"
    "Generation :matrice aleatoire 5x5 et sous espace de krylov de dim =5\n");*/
  }
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  strncpy(name_file,argv[4],50);
  v = malloc(sizeof(double*)*m*m);
  printf("Dim matrice %d | dim espace Krylov %d |Fichier mesure est : %s\n",n,m,argv[4]);

  init_vect(m,v);
  matrice = malloc(sizeof(double*)*n*n);
  printf("Mesure du temps d'éxecution de la reduction d'arnodli \n");
  fp =fopen(name_file,"a");
  //fscanf(fp,"%s\n",first);
//  if((strcmp(first,"# dimension\tdurée"))==0){
//    fprintf(fp,"# dimension\tduree\n");
//  }
  duree_mean = 0;
  variance = 0;
  for(int c = 0; c < 1000; c ++){
      start = clock_gettime(CLOCK_REALTIME, &t1);
      Vm = ArnoldiProjection ( n, m, v, matrice);
      end = clock_gettime(CLOCK_REALTIME, &t2);
      if ((t2.tv_nsec-t1.tv_nsec)<0)
      {
        duree_ns[c] = 1000000000+t2.tv_nsec-t1.tv_nsec;
        duree_mean = duree_mean+duree_ns[c];
      }
      else
      {
        duree_ns[c] = t2.tv_nsec-t1.tv_nsec;
        duree_mean = duree_mean+duree_ns[c];
      }
    //  variance = duree_ns[c]*duree_ns[c] + variance;
  }
  duree_mean = duree_mean/1000;
  for(int c = 0; c < 1000; c ++){
    variance = variance + (duree_ns[c]-duree_mean)*(duree_ns[c]-duree_mean);
    printf("variance %ld\n",variance);
  }
  variance = variance/1000;
//  duree_ns = (double)(t2.tv_sec-t1.tv_sec)/100 + (t2.tv_nsec-t1.tv_nsec)/(double)BILLION;


  fprintf(fp,"%d\t%ld\t%ld\n",n, duree_mean, variance);
  duree_ipc = (end - start)/100;
  printf("Durée d'execution moyenne sur 1000 boucle : %ld ns \n", duree_mean);
  printf("variance de la Durée d'execution  sur 1000 boucle : %ld ns \n", variance);
//  free(v);
//  free(Vm);
//  free(matrice);
  fclose(fp);


  return EXIT_SUCCESS;
}
