#include<stdio.h>
#include<stdlib.h>
#include"interface.h"
#include"arnoldi.h"
#include<string.h>
#include<time.h>


int main(int argc, char** argv){
  int m,n,dim;
  double* matrice; // matrice a donné a l'algo
  char nom_matrice[50]; //nom du fichier qui contient la matrice
  char first[30];
  double* v; // Vecteur initial
  double* Vm; //vecteur caculer par arnoldi
  int start, end;
  unsigned long duree_ns;
  int duree_ipc;
  struct timespec t1,t2;
  FILE* fp;
  if(argc == 4){
   m = atoi(argv[1]);
    n = atoi(argv[2]);
    memcpy(argv[3],nom_matrice,sizeof(double)*50);
    /*printf("Erreur : arnoldi [n] [m] [p] \n"
    "-dimention de la matrice [n]\n"
    "-dimension du sous-espace de Krylov [m]\n"
    "-l'adresse vers le fichie de la matrice[path]\n"
    "Generation :matrice aleatoire 5x5 et sous espace de krylov de dim =5\n");*/
  }
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  v = malloc(sizeof(double*)*m*m);

  init_vect(m,v);
  matrice = malloc(sizeof(double*)*n*n);
  printf("Mesure du temps d'éxecution de la reduction d'arnodli \n");
  fp =fopen("./data/mesure.dat","a");
  fscanf(fp,"%s\n",first);
  if((strcmp(first,"# dimension\tdurée"))==0){
    fprintf(fp,"# dimension\tduree\n");
  }
  start = clock_gettime(CLOCK_REALTIME, &t1);
  for(int c = 0; c < 100; c ++){
      Vm = ArnoldiProjection ( n, m, v, matrice);
  }
  end = clock_gettime(CLOCK_REALTIME, &t2);

  if ((t2.tv_nsec-t1.tv_nsec)<0)
  {
    duree_ns = 1000000000+t2.tv_nsec-t1.tv_nsec;
    duree_ns = duree_ns/100;
  }
  else
  {
    duree_ns = t2.tv_nsec-t1.tv_nsec;
    duree_ns = duree_ns/100;
    }

  fprintf(fp,"%d\t%ld\n",n,duree_ns);
  duree_ipc = (end - start)/100;
  printf("Durée d'execution moyenne sur 1000 boucle : %ld ns \n", duree_ns);
//  free(v);
  //free(Vm);
//  free(matrice);
  fclose(fp);


  return EXIT_SUCCESS;
}
