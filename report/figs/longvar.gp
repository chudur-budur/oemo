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
f1 = "dtlz4-nsga2r-hv.stat"
f2 = "dtlz4-onsga2r-hv.stat"
set output "dtlz4-longvar.pdf"
set key bottom right
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[1:50000]
# set yrange[4:]
plot \
	sprintf("../results/dtlz4-12/%s", f1) u 1:6 w lp ps 0.75 pt 4  pi 10 lw 2 ti "nsga2r, n = 12", \
	sprintf("../results/dtlz4-36/%s", f1) u 1:6 w lp ps 0.75 pt 6  pi 10 lw 2 ti "nsga2r, n = 36", \
	sprintf("../results/dtlz4-72/%s", f1) u 1:6 w lp ps 0.75 pt 8  pi 10 lw 2 ti "nsga2r, n = 72", \
	sprintf("../results/dtlz4-96/%s", f1) u 1:6 w lp ps 0.75 pt 10 pi 10 lw 2 ti "nsga2r, n = 96", \
	sprintf("../results/dtlz4-12/%s", f2) u 1:6 w lp ps 0.75 pt 5  pi 10 lw 2 ti "algorithm 3, n = 12", \
	sprintf("../results/dtlz4-36/%s", f2) u 1:6 w lp ps 0.75 pt 7  pi 10 lw 2 ti "algorithm 3, n = 36", \
	sprintf("../results/dtlz4-72/%s", f2) u 1:6 w lp ps 0.75 pt 9  pi 10 lw 2 ti "algorithm 3, n = 72", \
	sprintf("../results/dtlz4-96/%s", f2) u 1:6 w lp ps 0.75 pt 11 pi 10 lw 2 ti "algorithm 3, n = 96", \

	
# sprintf("../results/dtlz4-24/%s", f1)  u 1:6 w lp ps 0.5 pt 6 pi 10 lw 2 ti "nsga2r, n = 24", \
# sprintf("../results/dtlz4-48/%s", f1)  u 1:6 w lp ps 0.5 pt 10 pi 10 lw 2 ti "nsga2r, n = 48", \
# sprintf("../results/dtlz4-60/%s", f1)  u 1:6 w lp ps 0.5 pt 12 pi 10 lw 2 ti "nsga2r, n = 60", \
# sprintf("../results/dtlz4-84/%s", f1)  u 1:6 w lp ps 0.5 pt 16 pi 10 lw 2 ti "nsga2r, n = 84", \
# sprintf("../results/dtlz4-48/%s", f2)  u 1:6 w lp ps 0.5 pt 11 pi 10 lw 2 ti "algorithm 3, n = 48", \
# sprintf("../results/dtlz4-24/%s", f2)  u 1:6 w lp ps 0.5 pt 7 pi 10 lw 2 ti "algorithm 3, n = 24", \
# sprintf("../results/dtlz4-60/%s", f2)  u 1:6 w lp ps 0.5 pt 13 pi 10 lw 2 ti "algorithm 3, n = 60", \
# sprintf("../results/dtlz4-84/%s", f2)  u 1:6 w lp ps 0.5 pt 17 pi 10 lw 2 ti "algorithm 3, n = 84", \
