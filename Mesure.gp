set terminal png
set output "data/mesure.png"
set xlabel "Dimension matrice A"
set ylabel "Durée d'execution ns"
set title " Temps d'exécution moyens en fonction de la dimension de la matrice"
plot "./data/mesure3.dat" using 1:2:3:4 with errorbars

