#!/usr/local/bin/gnuplot

# plots all antenna related stuffs from the actual data

# antenna convergenece plot
hv_nsga2r = "../results/antenna/antenna-nsga2r-hv.stat"
hv_onsga2r = "../results/antenna/antenna-onsga2r-hv.stat"

coloropt = "color"

reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
	set term push
	set terminal unknown
} else {
	print "doing monochrome plot"
	set term push
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
set term pop


# the antenna pf plot
print "doing monochrome plot"
reset
unset output
set term push
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

# plot 6 snapshots
set term pop
reset
unset output
set ztics 0, 0.5, 2.0
set view 35, 311
# set key outside bottom horizontal nobox
set key at -15,350,3
set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
gens = "3 20 90 200"
do for [i = 1:words(gens)] {
	g = word(gens, i)
	nsga2r		= sprintf("data/antenna/nsga2r-gen-%s.out", g)
	extreme		= sprintf("data/antenna/extreme-gen-%s.out", g)
	child		= sprintf("data/antenna/child-gen-%s.out", g)
	survived	= sprintf("data/antenna/survived-gen-%s.out", g)
	onsga2r		= sprintf("data/antenna/onsga2r-gen-%s.out", g)
	mcf		= "data/antenna/antenna_mcf-c.out"
	outfile		= sprintf("antenna-g%s.pdf", g)
	
	print sprintf("doing monochrome plot, gen = %s", g)
	
	set term push
	set term pdf enhanced color
	set output outfile
	splot \
		mcf			u 1:2:3 w p pt 6 ps 0.5 lc rgb "navy" 	ti "samples", \
		nsga2r			u 1:2:3 w p pt 6 ps 0.5 lc rgb "grey" 	ti "nsga2", \
		onsga2r			u 1:2:3 w p pt 6 ps 0.5 lc rgb "black"	ti "onsga2r", \
		extreme			u 1:2:3 w p pt 6 ps 0.5 lc rgb "red"	ti "extreme pts.", \
		child			u 1:2:3 w p pt 6 ps 0.5 lc rgb "green"	ti "child", \
		survived		u 1:2:3 w p pt 6 ps 0.5 lc rgb "orange"	ti "survived"

	unset output
	set term pop
}
