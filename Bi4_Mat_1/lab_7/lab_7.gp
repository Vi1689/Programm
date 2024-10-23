set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'lab_6.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo
plot "lab_6/Coordinates_new.txt" using 1:2 with line lc rgb "black", "lab_6/Coordinates.txt" using 1:2 with line lc rgb "red"
