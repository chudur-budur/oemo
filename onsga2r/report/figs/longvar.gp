#!/usr/local/bin/gnuplot

coloropt = "mono"

if (coloropt eq "color") {
reset 
print "doing color plot"
load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
set term pdf enhanced color
set output "dtlz4-longvar.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[1:30000]
set yrange[4:]
plot \
	"../results/dtlz4-12/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 1 lw 6 ti "nsga2r, n = 12", \
	"../results/dtlz4-60/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 3 lw 6 ti "nsga2r, n = 60", \
	"../results/dtlz4-96/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 5 lw 6 ti "nsga2r, n = 96", \
	"../results/dtlz4-12/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 2 lw 6 ti "onsga2r, n = 12", \
	"../results/dtlz4-60/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 4 lw 6 ti "onsga2r, n = 60", \
	"../results/dtlz4-96/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 6 lw 6 ti "onsga2r, n = 96"
} else {
reset
print "doing monochrome plot"
set term pdf monochrome dashed
set output "dtlz4-longvar.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[1:30000]
set yrange[4:]
plot \
	"../results/dtlz4-12/dtlz4-nsga2r-hv.stat"	u 1:6 w lp lt 1 lw 1 ps 0.4 ti "nsga2r, n = 12", \
	"../results/dtlz4-60/dtlz4-nsga2r-hv.stat"	u 1:6 w lp lt 2 lw 1 ps 0.4 ti "nsga2r, n = 60", \
	"../results/dtlz4-96/dtlz4-nsga2r-hv.stat"	u 1:6 w lp lt 3 lw 1 ps 0.4 ti "nsga2r, n = 96", \
	"../results/dtlz4-12/dtlz4-onsga2r-hv.stat"	u 1:2 w l lt 1 lw 6 ti "onsga2r, n = 12", \
	"../results/dtlz4-60/dtlz4-onsga2r-hv.stat"	u 1:2 w l lt 2 lw 6 ti "onsga2r, n = 60", \
	"../results/dtlz4-96/dtlz4-onsga2r-hv.stat"	u 1:2 w l lt 3 lw 6 ti "onsga2r, n = 96"
}
