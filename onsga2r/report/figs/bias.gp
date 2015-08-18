#!/usr/local/bin/gnuplot

reset
set term pdf monochrome
set output "zdt4-bias.pdf"
unset key
set xlabel "f1"
set ylabel "f2"
set arrow from 0.3,50 to 0.025,40 size screen 0.015,30 lw 4 
set label 1 "search trajectory bias" at 0.31,51
set arrow from 0.60,49 to 0.85,10 size screen 0.015,30 lw 4 
plot "./data/zdt4-gen-46.out" pt 7 ps 0.7
