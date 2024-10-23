set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'kursach.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo
set xlabel "Дни" font 'Calibri,16'
set ylabel "Инфицированные" font 'Calibri,16'
plot "kursach/test.txt" using 1:4 title "Инфицированные с симптомами" with line lc rgb "red"
