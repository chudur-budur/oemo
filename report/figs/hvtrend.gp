#!/usr/local/bin/gnuplot

coloropt = "nocolor"

zdt4file10 = "../results/zdt4-0.10/zdt4-onsga2r-hv.stat"
zdt4file25 = "../results/zdt4-0.25/zdt4-onsga2r-hv.stat"
zdt4file50 = "../results/zdt4-0.50/zdt4-onsga2r-hv.stat"
zdt4file75 = "../results/zdt4-0.75/zdt4-onsga2r-hv.stat"
zdt4file90 = "../results/zdt4-0.90/zdt4-onsga2r-hv.stat"
zdt4nsga2r = "../results/zdt4/zdt4-nsga2r-hv.stat"
#
zdt6file10 = "../results/zdt6-0.10/zdt6-onsga2r-hv.stat"
zdt6file25 = "../results/zdt6-0.25/zdt6-onsga2r-hv.stat"
zdt6file50 = "../results/zdt6-0.50/zdt6-onsga2r-hv.stat"
zdt6file75 = "../results/zdt6-0.75/zdt6-onsga2r-hv.stat"
zdt6file90 = "../results/zdt6-0.90/zdt6-onsga2r-hv.stat"
zdt6nsga2r = "../results/zdt6/zdt6-nsga2r-hv.stat"
#
dtlz3file10 = "../results/dtlz3-0.10/dtlz3-onsga2r-hv.stat"
dtlz3file25 = "../results/dtlz3-0.25/dtlz3-onsga2r-hv.stat"
dtlz3file50 = "../results/dtlz3-0.50/dtlz3-onsga2r-hv.stat"
dtlz3file75 = "../results/dtlz3-0.75/dtlz3-onsga2r-hv.stat"
dtlz3file90 = "../results/dtlz3-0.90/dtlz3-onsga2r-hv.stat"
dtlz3nsga2r = "../results/dtlz3/dtlz3-nsga2r-hv.stat"

reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/YlOrRd.plt"
}
else {
	print "doing monochrome plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
}
set term pdf enhanced color
set output "zdt6-hv-trend.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set yrange[3:]
# set xrange[2000:10000]
plot \
	zdt6file10	us 1:7 w l  ls 8 lw 5 ti "ratio = 10% (mean-hv)", \
	zdt6file25	us 1:7 w l  ls 7 lw 5 ti "ratio = 25% (mean-hv)", \
	zdt6file50	us 1:7 w l  ls 6 lw 5 ti "ratio = 50% (mean-hv)", \
	zdt6file75	us 1:7 w l  ls 5 lw 5 ti "ratio = 75% (mean-hv)", \
	zdt6file90	us 1:7 w l  ls 4 lw 5 ti "ratio = 90% (mean-hv)", \
	zdt6nsga2r	us 1:6 w lp ls 8 lw 5 pt 1 pi 10 ti "nsga2r (max-hv)"
#
unset xrange
unset yrange
set yrange[2400:]
set xrange[10000:40000]
set term pdf enhanced color
set output "dtlz3-hv-trend.pdf"
plot \
	dtlz3file10	us 1:7 w l  ls 8 lw 5 ti "ratio = 10% (mean-hv)", \
	dtlz3file25	us 1:7 w l  ls 7 lw 5 ti "ratio = 25% (mean-hv)", \
	dtlz3file50	us 1:7 w l  ls 6 lw 5 ti "ratio = 50% (mean-hv)", \
	dtlz3file75	us 1:7 w l  ls 5 lw 5 ti "ratio = 75% (mean-hv)", \
	dtlz3file90	us 1:7 w l  ls 4 lw 5 ti "ratio = 90% (mean-hv)", \
	dtlz3nsga2r	us 1:6 w lp ls 8 lw 5 pt 1 pi 10 ti "nsga2r (max-hv)"
#
unset xrange
unset yrange
set yrange[2400:]
set xrange[10000:40000]
set term pdf enhanced color
set output "dtlz3-hv-trend.pdf"
plot \
	dtlz3file10	us 1:7 w l  ls 8 lw 5 ti "ratio = 10% (mean-hv)", \
	dtlz3file25	us 1:7 w l  ls 7 lw 5 ti "ratio = 25% (mean-hv)", \
	dtlz3file50	us 1:7 w l  ls 6 lw 5 ti "ratio = 50% (mean-hv)", \
	dtlz3file75	us 1:7 w l  ls 5 lw 5 ti "ratio = 75% (mean-hv)", \
	dtlz3file90	us 1:7 w l  ls 4 lw 5 ti "ratio = 90% (mean-hv)", \
	dtlz3nsga2r	us 1:6 w lp ls 8 lw 5 pt 1 pi 10 ti "nsga2r (max-hv)"
