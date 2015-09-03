#!/usr/local/bin/gnuplot

reset
set term pdf enhanced color dashed
set output "zdt1-corrupted.pdf"
set xlabel "generation"
set ylabel "% of individuals with corrupted genes"
set grid
set arrow from 0,10.82 to 200,10.82 nohead lw 4 lt 3
set arrow from 0,51.42 to 200,51.42 nohead lw 4 lt 3
plot \
	"./data/zdt1-corrupted.stat" using 1:5 with lines lt 1 lc rgb 'red' lw 3 ti "all genes corrupted", \
	"./data/zdt1-corrupted.stat" using 1:6 with lines lt 1 lc rgb 'green' lw 3 ti "0 genes corrupted"
