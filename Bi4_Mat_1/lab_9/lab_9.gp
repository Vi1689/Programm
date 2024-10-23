set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'lab_9.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo
plot "lab_9/output.txt" using 1:2 with line lc rgb "black"
