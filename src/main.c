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
  unsigned long duree_ns[100]; //Tableau de durée d'execution
  unsigned long duree_ms[100]; //tableau  de durée d'execution
  double duree_mean_ns,duree_mean_ms; //temps d'executions moyenne clock_gettime, clock
  double variance_ns, variance_ms;  // Variance des temps d'executions en nano et µs
  double ecart_type_ns, ecart_type_ms; // Ecart-tpes en ns et µs
  double min_ms,min_ns,max_ms,max_ns;
  struct timespec t1,t2;
  clock_t a,b;
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
  duree_mean_ns = 0.0;
  duree_mean_ms = 0.0;
  variance_ns = 0;
  variance_ms = 0;
  for(int c = 0; c < 100; c ++){
      a = clock();
      start = clock_gettime(CLOCK_REALTIME, &t1);
      Vm = ArnoldiProjection ( n, m, v, matrice);
      end = clock_gettime(CLOCK_REALTIME, &t2);
      b = clock();
      if ((t2.tv_nsec-t1.tv_nsec)<0)
      {
        duree_ns[c] = 1000000000+t2.tv_nsec-t1.tv_nsec;
        duree_mean_ns = duree_mean_ns + duree_ns[c];
      }
      else
      {
        duree_ns[c] = t2.tv_nsec-t1.tv_nsec;
        duree_mean_ns = duree_mean_ns + duree_ns[c];
      }
      duree_ms[c] = (b-a);
      duree_mean_ms = duree_mean_ms + (double) duree_ms[c];
    //  variance = duree_ns[c]*duree_ns[c] + variance;
  }

  duree_mean_ns = duree_mean_ns/100;
  duree_mean_ms = duree_mean_ms/100.0;
  for(int c = 0; c < 100; c ++){
    variance_ns = variance_ns + (duree_ns[c]-duree_mean_ns)*(duree_ns[c]-duree_mean_ns);
      variance_ms = variance_ms + (duree_ms[c]-duree_mean_ms)*(duree_ms[c]-duree_mean_ms);
  //  printf("variance %ld\n",variance);
  }
  variance_ns = variance_ns/100.0;
  variance_ms = variance_ms/100.0;
  ecart_type_ms = sqrt(variance_ms);
  ecart_type_ns = sqrt(variance_ns);
//  duree_ns = (double)(t2.tv_sec-t1.tv_sec)/100 + (t2.tv_nsec-t1.tv_nsec)/(double)BILLION;
  min_ms = duree_mean_ms - 3*ecart_type_ms;
  min_ns = duree_mean_ns -3*ecart_type_ns;
  max_ms = duree_mean_ms + 3*ecart_type_ms;
  max_ns = duree_mean_ns + 3*ecart_type_ns;


  fprintf(fp,"%d\t%lf\t%lf\t%lf\n",n, duree_mean_ns,min_ns,max_ns );
  printf("Durée d'execution moyenne clock_gettime sur 100 boucle : %lf ns +/- %lf \n", duree_mean_ns, ecart_type_ns);
  printf("Durée d'execution boyenne  clock sur 100 boucle : %lf ns +/- %lf \n", duree_mean_ms, ecart_type_ms);
//  free(v);
//  free(Vm);
//  free(matrice);
  fclose(fp);


  return EXIT_SUCCESS;
}
