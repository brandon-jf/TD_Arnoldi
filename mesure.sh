#!/bin/bash
#######################
#Brandon JEAN-FRANCOIS#
#M2 CHPS              #
#TD MPNA Arnoldi      #
#######################

taille=20
for i in {1..10};
do
  dim=$(($i*100))&&
  m=10&&
  echo "Mesure du temps d'execution  n=" $dim " m=" $m&&
  ./bin/arnoldi $dim $m "matrice.mat" "./data/mesure3.dat"
done
