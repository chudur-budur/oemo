#!/usr/local/bin/gnuplot

reset
set term pdf enhanced color
set output "zdt4-gap.pdf"
set style fill transparent solid 0.75 noborder
load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
set style circle radius screen 0.01
unset key
set xlabel "f1"
set ylabel "f2"
set arrow from 0.65,0.8 to 0.50,0.34 size screen 0.015,30 lw 4 
set arrow from 0.65,0.8 to 0.61,0.25 size screen 0.015,30 lw 4 
set label 1 "trade-off gaps" at 0.57,0.85
plot "./data/zdt4-gen-146.out" us 1:2 w circles ls 8
