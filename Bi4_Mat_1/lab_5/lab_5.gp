set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'lab_5.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo
plot "lab_5/Coordinates_new.txt" using 1:2 with line lc rgb "black", "lab_5/Coordinates.txt" using 1:2 with line lc rgb "red"
