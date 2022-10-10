#ifndef ARNOLDI_FUNC_H
#define ARNOLDI_FUNC_H

#include"my_seq_blas1.h"

//Prototype des fonctions utilisée pour l'algorithme d'ARNOLDI_H

double DotProd(double* x, double* y, int taille);
double Norme(double* x, int taille);
double Norme_fro(int nb_ligne, int nb_colonne, double* matrice);
double* ArnoldiProjection (int n, int m, double* v, double* A);

#endif
