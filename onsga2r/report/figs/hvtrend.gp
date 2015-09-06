#!/usr/local/bin/gnuplot

coloropt = "mono"

zdt4file10 = "../results/zdt4-0.10/zdt4-onsga2r-hv.stat"
zdt4file25 = "../results/zdt4-0.25/zdt4-onsga2r-hv.stat"
zdt4file50 = "../results/zdt4-0.50/zdt4-onsga2r-hv.stat"
zdt4file75 = "../results/zdt4-0.75/zdt4-onsga2r-hv.stat"
zdt4file90 = "../results/zdt4-0.90/zdt4-onsga2r-hv.stat"
#
dtlz3file10 = "../results/dtlz3-0.10/dtlz3-onsga2r-hv.stat"
dtlz3file25 = "../results/dtlz3-0.25/dtlz3-onsga2r-hv.stat"
dtlz3file50 = "../results/dtlz3-0.50/dtlz3-onsga2r-hv.stat"
dtlz3file75 = "../results/dtlz3-0.75/dtlz3-onsga2r-hv.stat"
dtlz3file90 = "../results/dtlz3-0.90/dtlz3-onsga2r-hv.stat"

if (coloropt eq "color") {
reset 
print "doing color plot"
load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/YlOrRd.plt"
set term pdf enhanced color
set output "zdt4-hv-trend.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set yrange[1.5:]
set xrange[3000:14000]
plot \
	zdt4file10	us 1:7 w l ls 8 lw 5 ti "ratio = 10%", \
	zdt4file25	us 1:7 w l ls 7 lw 5 ti "ratio = 25%", \
	zdt4file50	us 1:7 w l ls 6 lw 5 ti "ratio = 50%", \
	zdt4file75	us 1:7 w l ls 5 lw 5 ti "ratio = 75%", \
	zdt4file90	us 1:7 w l ls 4 lw 5 ti "ratio = 90%" \
#
unset xrange
unset yrange
set yrange[2400:]
set xrange[10000:40000]
set output "dtlz3-hv-trend.pdf"
plot \
	dtlz3file10	us 1:7 w l ls 8 lw 5 ti "ratio = 10%", \
	dtlz3file25	us 1:7 w l ls 7 lw 5 ti "ratio = 25%", \
	dtlz3file50	us 1:7 w l ls 6 lw 5 ti "ratio = 50%", \
	dtlz3file75	us 1:7 w l ls 5 lw 5 ti "ratio = 75%", \
	dtlz3file90	us 1:7 w l ls 4 lw 5 ti "ratio = 90%"
} else {
reset 
print "doing monochrome plot"
load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
set term pdf enhanced color
set output "zdt4-hv-trend.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set yrange[1.5:]
set xrange[3000:14000]
plot \
	zdt4file10	us 1:7 w l ls 8 lw 5 ti "ratio = 10%", \
	zdt4file25	us 1:7 w l ls 7 lw 5 ti "ratio = 25%", \
	zdt4file50	us 1:7 w l ls 6 lw 5 ti "ratio = 50%", \
	zdt4file75	us 1:7 w l ls 5 lw 5 ti "ratio = 75%", \
	zdt4file90	us 1:7 w l ls 4 lw 5 ti "ratio = 90%" \
#
unset xrange
unset yrange
set output "dtlz3-hv-trend.pdf"
set yrange[2400:]
set xrange[10000:40000]
plot \
	dtlz3file10	us 1:7 w l ls 8 lw 5 ti "ratio = 10%", \
	dtlz3file25	us 1:7 w l ls 7 lw 5 ti "ratio = 25%", \
	dtlz3file50	us 1:7 w l ls 6 lw 5 ti "ratio = 50%", \
	dtlz3file75	us 1:7 w l ls 5 lw 5 ti "ratio = 75%", \
	dtlz3file90	us 1:7 w l ls 4 lw 5 ti "ratio = 90%"
}
