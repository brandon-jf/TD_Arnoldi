#include"my_seq_blas1.h"
#include"my_seq_blas2.h"
#include"arnoldi.h"
#include<string.h>
#include"interface.h"
//Declaration des fonctions utilisée pour l'algorithme d'ARNOLDI_H

double DotProd(double* x, double* y, int taille){
  if(!x) {
    printf("x est non initialisé");
    return 0.0;
  }
  if(!y) {
    printf("y est non initialisé");
    return 0.0;
  }
  if(!taille) {
    printf("Erreur sur la taille= %d",taille);
    return 0.0;
  }
  double dotprod =0.0;
  for(int i = 0 ; i< taille ; i++){
    dotprod=+ x[i]*y[i];
  }
  return dotprod;
}
double Norme(double* x, int taille){
  if(!taille) {
    printf("Erreur sur la taille = %d\n",taille);
    return 0.0;
  }
  if(!x) {
    printf("Erreur sur x = %p",x);
    return 0.0;
  }
  return sqrt(DotProd(x, x, taille));

}
double Norme_fro(int nb_ligne ,int nb_colonne, double* matrice){
  double sum= 0.0;
  int ij;
  double norm_fro =0.0;

  for(int i = 0; i< nb_ligne; i++){
    for(int j = 0; j<nb_colonne; j++){
        ij = i*nb_colonne+j;

        sum = matrice[ij]*matrice[ij] +sum;

    }
  }
  norm_fro = sqrt(sum);

  return norm_fro;
}

double* ArnoldiProjection (int n, int m, double* v, double* A){
  double hij,alpha; // Scalaire de la matrice Hm
  double* Vm; //Ensembles de vecteurs qui forme l'espace de Krylov
  int ij,kl; // Indice de parcours de matrice
  double *_Vm; //vecteur Vm temporaire pour V(j+1)=Av(j)

  //Initialisation : normalaisation de Vm(1)
  Vm = malloc(sizeof(double*)*m*n);
  alpha = Norme(v,n);
  alpha = 1/alpha;
  seq_d_axpy(n,alpha,v,Vm);
  _Vm  = calloc(sizeof(double*), n);

  for(int j = 0; j<m ; j++){
    //1er phase: Calcul du 1 er vecteur du sous espace de kyrlov
    //Vm(:,j+1) ← A*Vm(:,j)
    for(int k = 0; k<n ; k++){
        _Vm[k]  = 0.0; //reinitialise _Vm a chaque iteration
      }
      // Y <- AX+by
    for(int k = 0; k < n; k++){
      for(int l = 0; l< n; l++){
        kl= k*n+l; //calcul l'indice de A(k,l)
        _Vm[k] =  A[kl]*Vm[j*n+l] + _Vm[k]; // Calcul un produit scalaire
      }
    }
    for(int _i = 0; _i < n; _i++){
      Vm[(j+1)*n+_i] = _Vm[_i] + Vm[(j+1)*n+_i]; //On actalise les valeurs du vecteur
    }

      //Fin de la premiere phase
      //2nd Phase:
      for(int i =0; i<j ; i++){
      //Calucl de ij ieme element de la matrice Hm
      //Hm(i,j) ← (Vm(j+1) , Vm(i) )
        for(int k = 0 ; k< n ; k++){
        hij=+ Vm[(j+1)*n+k]*Vm[j*n+k];
      }
      //Projection de v(j+i)
      //Vm(:,j+1) ← Vm(:,j+1) − Vm(:,i) × Hm(i,j)
        for(int k = 0; k< n; k++){
        Vm[(j+1)*n+k] = Vm[(j+1)*n+k] -hij*Vm[i*n+k];
      }

    //Hm( j+1,j) ← ||Vm(:; j+1) ||
      for(int ii = 0; ii < n; ii++){
      hij = Vm[(j+1)*n+ii]*Vm[(j+1)*n+ii]+ hij ;
    }
      hij =sqrt(hij);

    //v(j+1) ← v(j+1)/h (j+1)
    //seq_d_axpy(n,1/Hm[(j+1)*m+j],&Vm[(j+1)*n],&Vm[(j+1)]);
      for(int ii = 0; ii < m; ii++){
      Vm[(j+1)*n+ii] = (1/hij)*Vm[(j+1)*n+ii];
    }
    }
  }
  return Vm;
}
