#!/usr/local/bin/gnuplot

coloropt = "nocolor"

zdt4file10 = "../results/zdt4-0.10/zdt4-onsga2r-hv.stat"
zdt4file25 = "../results/zdt4-0.25/zdt4-onsga2r-hv.stat"
zdt4file50 = "../results/zdt4-0.50/zdt4-onsga2r-hv.stat"
zdt4file75 = "../results/zdt4-0.75/zdt4-onsga2r-hv.stat"
zdt4file90 = "../results/zdt4-0.90/zdt4-onsga2r-hv.stat"
zdt4nsga2r = "../results/zdt4/zdt4-nsga2r-hv.stat"
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
set output "zdt4-hv-trend.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set yrange[1.5:]
set xrange[3000:14000]
plot \
	zdt4file10	us 1:7 w l ls 7 lw 5 ti "ratio = 10% (mean-hv)", \
	zdt4file25	us 1:7 w l ls 6 lw 5 ti "ratio = 25% (mean-hv)", \
	zdt4file50	us 1:7 w l ls 5 lw 5 ti "ratio = 50% (mean-hv)", \
	zdt4file75	us 1:7 w l ls 4 lw 5 ti "ratio = 75% (mean-hv)", \
	zdt4file90	us 1:7 w l ls 3 lw 5 ti "ratio = 90% (mean-hv)", \
	zdt4nsga2r	us 1:6 w l ls 8 lw 5 ti "nsga2r (max-hv)"
#
unset xrange
unset yrange
set yrange[2400:]
set xrange[10000:40000]
set term pdf enhanced color
set output "dtlz3-hv-trend.pdf"
plot \
	dtlz3file10	us 1:7 w l ls 7 lw 5 ti "ratio = 10% (mean-hv)", \
	dtlz3file25	us 1:7 w l ls 6 lw 5 ti "ratio = 25% (mean-hv)", \
	dtlz3file50	us 1:7 w l ls 5 lw 5 ti "ratio = 50% (mean-hv)", \
	dtlz3file75	us 1:7 w l ls 4 lw 5 ti "ratio = 75% (mean-hv)", \
	dtlz3file90	us 1:7 w l ls 3 lw 5 ti "ratio = 90% (mean-hv)", \
	dtlz3nsga2r	us 1:6 w l ls 8 lw 5 ti "ratio = 90% (max-hv)"
