#!/bin/bash
#######################
#Brandon JEAN-FRANCOIS#
#M2 CHPS              #
#TD MPNA Arnoldi      #
#######################

taille=20
for i in {1..20};
do
  dim=$(($i*100))&&
  m=10&&
  echo "Mesure du temps d'execution  n=" $dim " m=" $m&&
  ./bin/arnoldi $dim $m;
done
