#!/usr/local/bin/gnuplot

coloropt = "nocolor"
titleopt = "false"

reset
set term pdf enhanced color
if (coloropt eq "color") {
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
	ptype = " 1 2 3 4 5 6 7 8 "
} else {
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
	ptype = " 4 5 6 7 8 1 2 3 "
}
if (titleopt eq "true") { set title "zdt3, generation: 3" }
set output "zdt3-gen-3.pdf"
set style fill transparent solid 0.75 noborder
set style circle radius screen 0.01
unset key
# set key top right
set xlabel "f1"
set ylabel "f2"
set arrow from 0.34,-0.1 to 0.25,0.8 size screen 0.015,30 lw 4
set arrow from 0.51,-0.2 to 0.61,-0.2 size screen 0.015,30 lw 4
set label 1 "linearly" at 0.35,0.0
set label 2 "translated solutions" at 0.35,-0.5
set arrow from 0.44,6.0 to 0.02,5.5 size screen 0.015,30 lw 4
set arrow from 0.60,5.7 to 0.65,0.0 size screen 0.015,30 lw 4
set label 3 "extreme solutions" at 0.45,6.0
plot \
	"./data/zdt3-pop-gen-3.out" using 1:2 w circles ls 5 ti "all solutions", \
	"./data/zdt3-child-gen-3.out" using 1:2 w circles ls 6 ti "child solutions", \
	"./data/zdt3-extreme-gen-3.out" using 1:2 w circles ls 7 ti "extremes",\
	"./data/zdt3-survived-gen-3.out" using 1:2 w circles ls 8 ti "survived solutions"
#
unset arrow
unset label

if (titleopt eq "true") { set title "zdt3, generation: 18" }
set output "zdt3-gen-18.pdf"
set arrow from 0.6,1.25 to 0.45,0.3 size screen 0.015,30 lw 4
set label 1 "front being constructed" at 0.5,1.65
set label 2 "using the linearly" at 0.5,1.5
set label 3 "translated solutions" at 0.5,1.35
set arrow from 0.63,1.0 to 0.02,1.57 size screen 0.015,30 lw 4
set arrow from 0.68,0.8 to 0.66,-0.35 size screen 0.015,30 lw 4
set label 4 "extreme solutions" at 0.65,1.0
set arrow from 0.2,-0.1 to 0.22,0.13 size screen 0.015,30 lw 4
set arrow from 0.1,-0.1 to 0.06,0.6 size screen 0.015,30 lw 4
set label 5 "completed fronts" at 0.05,-0.25
plot \
	"./data/zdt3-pop-gen-18.out" using 1:2 w circles ls 5 ti "all solutions", \
	"./data/zdt3-child-gen-18.out" using 1:2 w circles ls 6 ti "child solutions", \
	"./data/zdt3-extreme-gen-18.out" using 1:2 w circles ls 7 ti "extremes",\
	"./data/zdt3-survived-gen-18.out" using 1:2 w circles ls 8 ti "survived solutions"
#
unset arrow
unset label

if (titleopt eq "true") { set title "zdt3, generation: 27" }
set output "zdt3-gen-27.pdf"
set arrow from 0.52,-0.35 to 0.62,-0.35 size screen 0.015,30 lw 4
set label 1 "refining fronts using" at 0.35,-0.25
set label 2 "linearly" at 0.35,-0.35
set label 3 "translated solutions" at 0.35,-0.45
set arrow from 0.57,1.1 to 0.655,-0.4 size screen 0.015,30 lw 4
set arrow from 0.49,1.2 to 0.02,1.2 size screen 0.015,30 lw 4
set label 4 "extreme solutions" at 0.5,1.2
set arrow from 0.12,-0.31 to 0.04,0.65 size screen 0.015,30 lw 4
set arrow from 0.17,-0.31 to 0.2,0.42 size screen 0.015,30 lw 4
set arrow from 0.22,-0.31 to 0.4,0.0 size screen 0.015,30 lw 4
set label 5 "completed fronts" at 0.1,-0.4
plot \
	"./data/zdt3-pop-gen-27.out" using 1:2 w circles ls 5 ti "all solutions", \
	"./data/zdt3-child-gen-27.out" using 1:2 w circles ls 6 ti "child solutions", \
	"./data/zdt3-extreme-gen-27.out" using 1:2 w circles ls 7 ti "extremes",\
	"./data/zdt3-survived-gen-27.out" using 1:2 w circles ls 8 ti "survived solutions"
#
unset arrow
unset label
# set term pdf enhanced color

if (titleopt eq "true") { set title "zdt4, generation: 21" }
set output "zdt4-gen-21.pdf"
set arrow from 0.2,32.0 to 0.02,5.0 size screen 0.015,30 lw 4
set arrow from 0.3,32.0 to 0.55,5.0 size screen 0.015,30 lw 4
set arrow from 0.2,43.0 to 0.02,71.0 size screen 0.015,30 lw 4
set label 1 "linearly" at 0.1,40
set label 2 "translated solutions" at 0.1,36
set arrow from 0.55,57 to 0.8,5.0 size screen 0.015,30 lw 4
set arrow from 0.45,57 to 0.3,5.0 size screen 0.015,30 lw 4
set label 3 "bias correction" at 0.4,60
plot \
	"./data/zdt4-pop-gen-21.out" using 1:2 w circles ls 5 ti "all solutions", \
	"./data/zdt4-survived-gen-21.out" using 1:2 w circles ls 8 ti "survived solutions"