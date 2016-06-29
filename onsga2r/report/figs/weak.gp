#!/usr/local/bin/gnuplot

# find the femin
femin(fname) = system(sprintf("cat %s | head -n 1 | awk -F\" \" '{print $1}'", fname))

zdt4file1 = "../results/zdt4/zdt4-onsga2rwdom-hv.stat"
zdt4file2 = "../results/zdt4/zdt4-nsga2r-hv.stat"
zdt4file3 = "../results/zdt4/zdt4-onsga2r-hv.stat"
dtlz1file1 = "../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"
dtlz1file2 = "../results/dtlz1/dtlz1-nsga2r-hv.stat"
dtlz1file3 = "../results/dtlz1/dtlz1-onsga2r-hv.stat"

coloropt = "nocolor"

reset
if (coloropt eq "color") {
	# 1,8,3,3-2,8,3,3
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
} else {
	# 8,4,3,5-6,4,3,5
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
}

#
set key bottom right
set boxwidth 0.5 relative
set style fill noborder
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:]
set yrange[0:]
plot \
	zdt4file1 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3(weak)" whiskerbars 0.5, \
	zdt4file1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
	zdt4file1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
	zdt4file1 using 1:4 with lines ls 5 lw 1 noti, \
	\
        zdt4file2 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
	zdt4file2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	zdt4file2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	zdt4file2 using 1:4 with lines ls 5 lw 1 noti, \
	\
        zdt4file3 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 4 lw 3 title "algorithm 3" whiskerbars 0.5, \
	zdt4file3 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	zdt4file3 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	zdt4file3 using 1:4 with lines ls 5 lw 1 noti

ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
# print "ydiff: ", ydiff
ymin = GPVAL_Y_MIN
# print "ymin: ", ymin
liney = ymin + (ydiff * 0.5)
# print "liney: ", liney
txtstart = liney + (ydiff * 0.1)
# print "txtstart: ", txtstart
xthresh = 50
minfe = femin(zdt4file3)
print sprintf("%s, minfe: %s", "zdt4", minfe)
set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find Z*_b" rotate left at (minfe+xthresh)/2,txtstart
set arrow from (minfe+xthresh)/2,txtstart-(ydiff * 0.01) \
	to (minfe+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
#
set term push
set term pdf enhanced color
set output "zdt4-weak.pdf"
replot
unset output
set term pop
#

reset
if (coloropt eq "color") {
	# 1,8,3,3-2,8,3,3
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
} else {
	# 8,4,3,5-6,4,3,5
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
}
set key bottom right
set boxwidth 0.5 relative
set style fill noborder
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:]
set yrange[0:]
plot \
	dtlz1file1 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3(weak)" whiskerbars 0.5, \
	dtlz1file1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
	dtlz1file1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
	dtlz1file1 using 1:4 with lines ls 5 lw 1 noti, \
	\
        dtlz1file2 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
	dtlz1file2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	dtlz1file2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	dtlz1file2 using 1:4 with lines ls 5 lw 1 noti, \
	\
        dtlz1file3 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 4 lw 3 title "algorithm 3" whiskerbars 0.5, \
	dtlz1file3 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	dtlz1file3 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	dtlz1file3 using 1:4 with lines ls 5 lw 1 noti

ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
print "ydiff: ", ydiff
ymin = GPVAL_Y_MIN
print "ymin: ", ymin
liney = ymin + (ydiff * 0.1)
print "liney: ", liney
txtstart = liney + (ydiff * 0.1)
print "txtstart: ", txtstart
xthresh = 50
minfe = femin(dtlz1file3)
print sprintf("%s, minfe: %s", "dtlz1", minfe)
set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
set label 1 "cost to find Z*_b" rotate left at (minfe+6000)/2,txtstart
set arrow from (minfe+6000)/2,txtstart-(ydiff * 0.01) \
	to (minfe+6000)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
#
set term push
set term pdf enhanced color
set output "dtlz1-weak.pdf"
replot
unset output
set term pop
