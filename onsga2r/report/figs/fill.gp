#!/usr/local/bin/gnuplot

reset
# set term pdf monochrome
set term pdf enhanced color
set output "zdt3-gen-9.pdf"
set style fill transparent solid 0.75 noborder
load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
set style circle radius screen 0.01
unset key
# set key top right
set xlabel "f1"
set ylabel "f2"
set arrow from 0.015,0.73 to 0.018,0.83 size screen 0.015,30 lw 4
set label 1 "deterministically" at 0.005,0.71
set label 2 "generated solutions" at 0.005,0.69
set arrow from 0.07,0.9 to 0.001,0.995 size screen 0.015,30 lw 4
set arrow from 0.07,0.9 to 0.082,0.685 size screen 0.015,30 lw 4
set label 3 "extreme solutions" at 0.07,0.91
plot \
	"./data/zdt3-pop-gen-9.out" using 1:2 w circles ls 1 ti "all solutions", \
	"./data/zdt3-child-gen-9.out" using 1:2 w circles ls 2 ti "child solutions", \
	"./data/zdt3-extreme-gen-9.out" using 1:2 w circles ls 3 ti "extremes",\
	"./data/zdt3-survived-gen-9.out" using 1:2 w circles ls 4 ti "survived solutions"
#
unset arrow
unset label
set output "zdt3-gen-22.pdf"
set arrow from 0.18,0.42 to 0.24,0.24 size screen 0.015,30 lw 4
set arrow from 0.18,0.42 to 0.19,0.57 size screen 0.015,30 lw 4
set label 1 "deterministically" at 0.1,0.4
set label 2 "generated solutions" at 0.1,0.36
set arrow from 0.25,0.8 to 0.01,0.98 size screen 0.015,30 lw 4
set arrow from 0.25,0.8 to 0.27,0.3 size screen 0.015,30 lw 4
set label 3 "extreme solutions" at 0.25,0.82
set arrow from 0.05,0.53 to 0.04,0.7 size screen 0.015,30 lw 4
set label 4 "completed front" at 0.025,0.5
plot \
	"./data/zdt3-pop-gen-22.out" using 1:2 w circles ls 1 ti "all solutions", \
	"./data/zdt3-child-gen-22.out" using 1:2 w circles ls 2 ti "child solutions", \
	"./data/zdt3-extreme-gen-22.out" using 1:2 w circles ls 3 ti "extremes",\
	"./data/zdt3-survived-gen-22.out" using 1:2 w circles ls 4 ti "survived solutions"
#
unset arrow
unset label
set output "zdt3-gen-44.pdf"
set arrow from 0.37,0.0 to 0.41,-0.03 size screen 0.015,30 lw 4
set label 1 "deterministically" at 0.2,0.06
set label 2 "generated solutions" at 0.2,0.0
set arrow from 0.4,0.9 to 0.01,0.98 size screen 0.015,30 lw 4
set arrow from 0.4,0.9 to 0.45,-0.05 size screen 0.015,30 lw 4
set label 3 "extreme solutions" at 0.41,0.92
set arrow from 0.17,0.5 to 0.2,0.42 size screen 0.015,30 lw 4
set arrow from 0.05,0.53 to 0.04,0.7 size screen 0.015,30 lw 4
set label 4 "completed fronts" at 0.025,0.5
plot \
	"./data/zdt3-pop-gen-44.out" using 1:2 w circles ls 1 ti "all solutions", \
	"./data/zdt3-child-gen-44.out" using 1:2 w circles ls 2 ti "child solutions", \
	"./data/zdt3-extreme-gen-44.out" using 1:2 w circles ls 3 ti "extremes",\
	"./data/zdt3-survived-gen-44.out" using 1:2 w circles ls 4 ti "survived solutions"
#
unset arrow
unset label
set output "zdt3-gen-45.pdf"
set arrow from 0.37,0.0 to 0.41,-0.03 size screen 0.015,30 lw 4
set arrow from 0.37,0.0 to 0.4,0.2 size screen 0.015,30 lw 4
set label 1 "deterministically" at 0.2,0.06
set label 2 "generated solutions" at 0.2,0.0
set arrow from 0.4,0.9 to 0.01,0.98 size screen 0.015,30 lw 4
set arrow from 0.4,0.9 to 0.46,-0.05 size screen 0.015,30 lw 4
set label 3 "extreme solutions" at 0.41,0.92
set arrow from 0.17,0.5 to 0.2,0.42 size screen 0.015,30 lw 4
set arrow from 0.05,0.53 to 0.04,0.7 size screen 0.015,30 lw 4
set label 4 "completed fronts" at 0.025,0.5
plot \
	"./data/zdt3-pop-gen-45.out" using 1:2 w circles ls 1 ti "all solutions", \
	"./data/zdt3-child-gen-45.out" using 1:2 w circles ls 2 ti "child solutions", \
	"./data/zdt3-extreme-gen-45.out" using 1:2 w circles ls 3 ti "extremes",\
	"./data/zdt3-survived-gen-45.out" using 1:2 w circles ls 4 ti "survived solutions"
#
unset arrow
unset label
set output "zdt4-gen-6.pdf"
set arrow from 0.5,4.0 to 0.52,1 size screen 0.015,30 lw 4
set arrow from 0.5,4.0 to 0.22,0.95 size screen 0.015,30 lw 4
set arrow from 0.5,4.0 to 0.78,0.8 size screen 0.015,30 lw 4
set label 1 "deterministically" at 0.4,6
set label 2 "generated solutions" at 0.4,5.1
set arrow from 0.37,11 to 0.1,4.0 size screen 0.015,30 lw 4
set arrow from 0.37,11 to 0.9,2.0 size screen 0.015,30 lw 4
set label 3 "bias correction" at 0.3,12
plot \
	"./data/zdt4-pop-gen-6.out" using 1:2 w circles ls 1 ti "all solutions", \
	"./data/zdt4-survived-gen-6.out" using 1:2 w circles ls 4 ti "survived solutions"
