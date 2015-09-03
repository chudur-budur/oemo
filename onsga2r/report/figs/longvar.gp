#!/usr/local/bin/gnuplot

reset
load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
# load "~/gnuplot-utils/gnuplot-colorbrewer/diverging/Spectral.plt"
# load "~/gnuplot-utils/gnuplot-colorbrewer/diverging/RdBu.plt"
set term pdf enhanced color
set output "dtlz2-longvar.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[1:30000]
set yrange[4:]
plot \
	"./data/dtlz2-nsga2r-hv-12.stat"	u 1:6 w l ls 1 lw 6 ti "nsga2r, n = 12", \
	"./data/dtlz2-nsga2r-hv-60.stat"	u 1:6 w l ls 3 lw 6 ti "nsga2r, n = 60", \
	"./data/dtlz2-nsga2r-hv-96.stat"	u 1:6 w l ls 5 lw 6 ti "nsga2r, n = 96", \
	"./data/dtlz2-onsga2r-hv-12.stat"	u 1:2 w l ls 2 lw 6 ti "onsga2r, n = 12", \
	"./data/dtlz2-onsga2r-hv-60.stat"	u 1:2 w l ls 4 lw 6 ti "onsga2r, n = 60", \
	"./data/dtlz2-onsga2r-hv-96.stat"	u 1:2 w l ls 6 lw 6 ti "onsga2r, n = 96"

