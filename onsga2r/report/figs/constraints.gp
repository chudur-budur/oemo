#!/usr/local/bin/gnuplot

c1dtlz1_nsga2r = "../results/c1dtlz1/c1dtlz1-nsga2r-hv.stat"
c1dtlz1_onsga2r = "../results/c1dtlz1/c1dtlz1-onsga2r-hv.stat"
c1dtlz3_nsga2r = "../results/c1dtlz3/c1dtlz3-nsga2r-hv.stat"
c1dtlz3_onsga2r = "../results/c1dtlz3/c1dtlz3-onsga2r-hv.stat"

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
	c1dtlz1_nsga2r		u 1:7 w l ls 1 lw 6 ti "nsga2r-mean", \
	c1dtlz1_onsga2r		u 1:7 w l ls 2 lw 6 ti "onsga2r-mean", \
	c1dtlz1_nsga2r		u 1:4 w l ls 3 lw 6 ti "nsga2r-median", \
	c1dtlz1_onsga2r		u 1:4 w l ls 4 lw 6 ti "onsga2r-median", \
	c1dtlz1_nsga2r		u 1:6 w l ls 7 lw 6 ti "nsga2r-max", \
	c1dtlz1_onsga2r		u 1:6 w l ls 8 lw 6 ti "onsga2r-max"
if (coloropt eq "color") {
	set term pdf enhanced color
} else {
	set term pdf monochrome dashed
}
set output "../results/c1dtlz1/c1dtlz1-nobox.pdf"
xval = real(system(sprintf("cat %s | head -n 1 | awk -F\" \" \'{print $1}\'", c1dtlz1_onsga2r)))
ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
ymin = GPVAL_Y_MIN
liney = ymin + (ydiff * 0.5)
txtstart = liney + (ydiff * 0.1)
xthresh = 50
set arrow from 0+xthresh,liney to xval-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find E*" rotate left at (xval+xthresh)/2,txtstart
set arrow from (xval+xthresh)/2,txtstart-(ydiff * 0.01) to (xval+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
replot

unset output
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
	c1dtlz3_nsga2r		u 1:7 w l ls 1 lw 6 ti "nsga2r-mean", \
	c1dtlz3_onsga2r		u 1:7 w l ls 2 lw 6 ti "onsga2r-mean", \
	c1dtlz3_nsga2r		u 1:4 w l ls 3 lw 6 ti "nsga2r-median", \
	c1dtlz3_onsga2r		u 1:4 w l ls 4 lw 6 ti "onsga2r-median", \
	c1dtlz3_nsga2r		u 1:6 w l ls 7 lw 6 ti "nsga2r-max", \
	c1dtlz3_onsga2r		u 1:6 w l ls 8 lw 6 ti "onsga2r-max"
if (coloropt eq "color") {
	set term pdf enhanced color
} else {
	set term pdf monochrome dashed
}
set output "../results/c1dtlz3/c1dtlz3-nobox.pdf"
xval = real(system(sprintf("cat %s | head -n 1 | awk -F\" \" \'{print $1}\'", c1dtlz3_onsga2r)))
ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
ymin = GPVAL_Y_MIN
liney = ymin + (ydiff * 0.5)
txtstart = liney + (ydiff * 0.1)
xthresh = 50
set arrow from 0+xthresh,liney to xval-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find E*" rotate left at (xval+xthresh)/2,txtstart
set arrow from (xval+xthresh)/2,txtstart-(ydiff * 0.01) to (xval+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
replot
