#include"my_seq_blas2.h"
#include"my_seq_blas1.h"
#include<stdio.h>
#include<stdlib.h>
//Fonction sequentiel qui realise y = A*x+b*y
//Arguments:
//	les entiers m,n: les dimension de la matrice A et des vecteurs x,y
//	un réel beta: coefficient b de type double
//	les vecteurs x,y: pointeur de tableau de type double
//  la matrice A: pointeurs sur le tableau de type double de dimension m*n
//Y_i = A_i(1:n)*X(1:n) + b*Y_i = Sum(A_ij*X_j) +bY_i
void seq_d_Axpby(int m, int n, double alpha, double* A, double *X, double beta, double *Y){
  int ij = 0;
  double save;
  double sum;
  double *dotprod;
  dotprod  = calloc(sizeof(double*), m);
  for(int i = 0; i < m; i++){
    for(int j = 0; j< n; j++){
      ij = i*n+j;
      dotprod[i] =  A[ij]*alpha*X[j] + dotprod[i];
    }
	}
  seq_d_axpy( m, beta,  Y, dotprod);
  free(dotprod);
}

//Fonction sequentiel qui realise y = A^(t)*x+b*y
//Arguments:
//	les entiers m,n: les dimension de la matrice A et des vecteurs x,y
//	un réel beta: coefficient b de type double
//	les vecteurs x,y: pointeur de tableau de type double
//  la matrice A: pointeurs sur le tableau de type double de dimension m*n
void seq_d_tAxpby(int m, int n, double alpha, double* A, double *X, double beta, double *Y){
  int ji = 0;
  double sum;
  for(int i = 0; i < m; i++){
    sum = 0.0;
    for(int j = 0; j< n; j++){
      ji = j*m+i;
      sum =  A[ji]*alpha*X[j] + beta*Y[i] + sum ;
    }
    Y[i] = sum;
  }
}

//Fonction sequentiel qui realise A = A + a*x^(t)*y
//Arguments:
//	les entiers m,n: les dimension de la matrice A et des vecteurs x,y
//	un réel beta: coefficient b de type double
//	les vecteurs x,y: pointeur de tableau de type double
//  la matrice A: pointeurs sur le tableau de type double de dimension m*n
void seq_d_Apxty(int m, int n, double* A, double alpha, double* X, double* Y){
  int ij = 0;
  for(int i = 0; i < m; i++){
    for(int j = 0; j< n; j++){
      ij = i*n+j;
      A[ij] = A[ij]+alpha*X[i]*Y[j];
    }
  }
}
