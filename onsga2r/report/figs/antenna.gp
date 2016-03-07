#!/usr/local/bin/gnuplot

# plots all antenna related stuffs from the actual data

hv_nsga2r = "../results/antenna/antenna-nsga2r-hv.stat"
hv_onsga2r = "../results/antenna/antenna-onsga2r-hv.stat"

coloropt = "color"

reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
	set terminal unknown
} else {
	print "doing monochrome plot"
	set terminal unknwon
}

set key bottom right
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
plot \
	hv_nsga2r	u 1:7 w l ls 1 lw 6 ti "nsga2r-mean", \
	hv_onsga2r	u 1:7 w l ls 2 lw 6 ti "onsga2r-mean", \
	hv_nsga2r	u 1:4 w l ls 3 lw 6 ti "nsga2r-median", \
	hv_onsga2r	u 1:4 w l ls 4 lw 6 ti "onsga2r-median", \
	hv_nsga2r	u 1:6 w l ls 7 lw 6 ti "nsga2r-max", \
	hv_onsga2r	u 1:6 w l ls 8 lw 6 ti "onsga2r-max"
if (coloropt eq "color") {
	set term pdf enhanced color
} else {
	set term pdf monochrome dashed
}
set output "../results/antenna/antenna-nobox.pdf"
xval = real(system(sprintf("cat %s | head -n 1 | awk -F\" \" \'{print $1}\'", hv_onsga2r)))
ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
ymin = GPVAL_Y_MIN
liney = ymin + (ydiff * 0.3)
txtstart = liney + (ydiff * 0.1)
xthresh = 50
set arrow from 0!+xthresh,liney to xval-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find E*" rotate left at (xval+xthresh)/2,txtstart
set arrow from (xval+xthresh)/2,txtstart-(ydiff * 0.01) to (xval+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
replot


# the antenna pf plot
print "doing monochrome plot"
reset
unset output
set term pdf enhanced color
set output "antenna-pf.pdf"

nsga2r = "data/antenna/nsga2r-gen-200.out"
mcf = "data/antenna/antenna_mcf-c.out"
pivots = "data/antenna/pivots-sosolver.out"

set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
set ztics 0, 0.5, 2.0
set view 35, 311
set key at -10,350,2

splot nsga2r u 1:2:3 w p pt 6 ps 0.5 lc rgb "black" ti "Pareto-front (NSGA-II)", \
	mcf u 1:2:3 w p pt 6 ps 0.5 lc rgb "navy" ti "random solutions (5000)", \
	pivots u 1:2:3 w p pt 6 ps 0.5 lc rgb "red" ti "extreme points (approx.)", \
