#!/usr/local/bin/gnuplot

coloropt = "nocolor"

reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
	set term pdf enhanced color
} else {
	print "doing monochrome plot"
	set term pdf monochrome dashed
}
set output "dtlz4-longvar.pdf"
set key bottom right
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[1:30000]
set yrange[4:]
plot \
	"../results/dtlz4-12/dtlz4-nsga2r-hv.stat"  u 1:6 w lp ps 0.5 pt 1 pi -2 lw 2 ti "nsga2r, n = 12", \
	"../results/dtlz4-60/dtlz4-nsga2r-hv.stat"  u 1:6 w lp ps 0.5 pt 4 pi -2 lw 2 ti "nsga2r, n = 60", \
	"../results/dtlz4-96/dtlz4-nsga2r-hv.stat"  u 1:6 w lp ps 0.5 pt 6 pi -2 lw 2 ti "nsga2r, n = 96", \
	"../results/dtlz4-12/dtlz4-onsga2r-hv.stat" u 1:2 w lp ps 0.5 pt 2 pi -2 lw 2 ti "algorithm 3, n = 12", \
	"../results/dtlz4-60/dtlz4-onsga2r-hv.stat" u 1:2 w lp ps 0.5 pt 5 pi -2 lw 2 ti "algorithm 3, n = 60", \
	"../results/dtlz4-96/dtlz4-onsga2r-hv.stat" u 1:2 w lp ps 0.5 pt 7 pi -2 lw 2 ti "algorithm 3, n = 96"
# plot \
# 	"../results/dtlz4-12/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 1 lw 6 ti "nsga2r, n = 12", \
# 	"../results/dtlz4-60/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 3 lw 6 ti "nsga2r, n = 60", \
# 	"../results/dtlz4-96/dtlz4-nsga2r-hv.stat"	u 1:6 w l ls 5 lw 6 ti "nsga2r, n = 96", \
# 	"../results/dtlz4-12/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 2 lw 6 ti "algorithm 3, n = 12", \
# 	"../results/dtlz4-60/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 4 lw 6 ti "algorithm 3, n = 60", \
# 	"../results/dtlz4-96/dtlz4-onsga2r-hv.stat"	u 1:2 w l ls 6 lw 6 ti "algorithm 3, n = 96"

