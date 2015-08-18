#!/usr/local/bin/gnuplot

reset
set term pdf monochrome
set output "zdt4-gap.pdf"
unset key
set xlabel "f1"
set ylabel "f2"
set arrow from 0.65,0.8 to 0.50,0.34 size screen 0.015,30 lw 4 
set arrow from 0.65,0.8 to 0.61,0.25 size screen 0.015,30 lw 4 
set label 1 "trade-off gaps" at 0.57,0.85
plot "./data/zdt4-gen-146.out" pt 7 ps 0.7
