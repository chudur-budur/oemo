#!/usr/local/bin/gnuplot

c1dtlz1_nsga2r = "../results/c1dtlz1/c1dtlz1-nsga2r-hv.stat"
c1dtlz1_onsga2r = "../results/c1dtlz1/c1dtlz1-onsga2r-hv.stat"
c1dtlz3_nsga2r = "../results/c1dtlz3/c1dtlz3-nsga2r-hv.stat"
c1dtlz3_onsga2r = "../results/c1dtlz3/c1dtlz3-onsga2r-hv.stat"

coloropt = "nocolor"


set key bottom right
set style fill noborder
set boxwidth 0.5 relative
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
} else {
	print "doing monochrome plot"
}
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
plot \
	c1dtlz1_nsga2r		u 1:7 w lp ps 0.5 pt 1 pi -2 lw 2 ti "nsga2r-mean", \
	c1dtlz1_onsga2r		u 1:7 w lp ps 0.5 pt 4 pi -2 lw 2 ti "algorithm3-mean", \
	c1dtlz1_nsga2r		u 1:4 w lp ps 0.5 pt 6 pi -2 lw 2 ti "nsga2r-median", \
	c1dtlz1_onsga2r		u 1:4 w lp ps 0.5 pt 2 pi -2 lw 2 ti "algorithm3-median", \
	c1dtlz1_nsga2r		u 1:6 w lp ps 0.5 pt 5 pi -2 lw 2 ti "nsga2r-max", \
	c1dtlz1_onsga2r		u 1:6 w lp ps 0.5 pt 7 pi -2 lw 2 ti "algorithm3-max"
xval = real(system(sprintf("cat %s | head -n 1 | awk -F\" \" \'{print $1}\'", c1dtlz1_onsga2r)))
ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
ymin = GPVAL_Y_MIN
liney = ymin + (ydiff * 0.5)
txtstart = liney + (ydiff * 0.1)
xthresh = 50
set arrow from 0+xthresh,liney to xval-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find Z*_b" rotate left at (xval+xthresh)/2,txtstart
set arrow from (xval+xthresh)/2,txtstart-(ydiff * 0.01) to (xval+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
set term push
if (coloropt eq "color") {
	set term pdf enhanced color
} else {
	set term pdf enhanced monochrome dashed
}
set output "../results/c1dtlz1/c1dtlz1-nobox.pdf"
replot
unset output
set term pop

reset
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
plot \
	c1dtlz3_nsga2r		u 1:7 w lp ps 0.5 pt 1 pi -2 lw 2 ti "nsga2r-mean", \
	c1dtlz3_onsga2r		u 1:7 w lp ps 0.5 pt 4 pi -2 lw 2 ti "algorithm3-mean", \
	c1dtlz3_nsga2r		u 1:4 w lp ps 0.5 pt 6 pi -2 lw 2 ti "nsga2r-median", \
	c1dtlz3_onsga2r		u 1:4 w lp ps 0.5 pt 2 pi -2 lw 2 ti "algorithm3-median", \
	c1dtlz3_nsga2r		u 1:6 w lp ps 0.5 pt 5 pi -2 lw 2 ti "nsga2r-max", \
	c1dtlz3_onsga2r		u 1:6 w lp ps 0.5 pt 7 pi -2 lw 2 ti "algorithm3-max"
xval = real(system(sprintf("cat %s | head -n 1 | awk -F\" \" \'{print $1}\'", c1dtlz3_onsga2r)))
ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
ymin = GPVAL_Y_MIN
liney = ymin + (ydiff * 0.5)
txtstart = liney + (ydiff * 0.1)
xthresh = 50
set arrow from 0+xthresh,liney to xval-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find Z*_b" rotate left at (xval+xthresh)/2,txtstart
set arrow from (xval+xthresh)/2,txtstart-(ydiff * 0.01) to (xval+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
set term push
if (coloropt eq "color") {
	set term pdf enhanced color
} else {
	set term pdf enhanced monochrome dashed
}
set output "../results/c1dtlz3/c1dtlz3-nobox.pdf"
replot
unset output
set term pop
