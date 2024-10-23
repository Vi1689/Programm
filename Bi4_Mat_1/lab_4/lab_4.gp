set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'lab_4.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo
plot "lab_4/Coordinates_new.txt" using 1:2 title "Новый график" with line lc rgb "black", "lab_4/Coordinates.txt" using 1:2 title "Первый график" with line lc rgb "red"
