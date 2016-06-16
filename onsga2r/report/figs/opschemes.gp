#!/usr/local/bin/gnuplot

coloropt = "nocolor"

zdt4  = "../results/zdt4/zdt4-onsga2r-hv.stat"
zdt4i = "../results/zdt4/zdt4-onsga2rdi-hv.stat"
zdt4r = "../results/zdt4/zdt4-onsga2rdr-hv.stat"
#
zdt6  = "../results/zdt6/zdt6-onsga2r-hv.stat"
zdt6i = "../results/zdt6/zdt6-onsga2rdi-hv.stat"
zdt6r = "../results/zdt6/zdt6-onsga2rdr-hv.stat"
#
dtlz6  = "../results/dtlz6/dtlz6-onsga2r-hv.stat"
dtlz6i = "../results/dtlz6/dtlz6-onsga2rdi-hv.stat"
dtlz6r = "../results/dtlz6/dtlz6-onsga2rdr-hv.stat"


reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Set1.plt"
} else {
	print "doing monochrome plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
}
set term pdf enhanced color
set output "zdt4-hv-opschemes.pdf"
set key bottom right
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set yrange[1.5:]
set xrange[:7000]
plot \
	zdt4	us 1:7 w l ls 1 lw 5 ti "opposite", \
	zdt4i	us 1:7 w l ls 2 lw 5 ti "inverse-opposite", \
	zdt4r	us 1:7 w l ls 3 lw 5 ti "random"
#
set yrange[8:]
set xrange[:4000]
set term pdf enhanced color
set output "zdt6-hv-opschemes.pdf"
plot \
	zdt6	us 1:7 w l ls 1 lw 5 ti "opposite", \
	zdt6i	us 1:7 w l ls 2 lw 5 ti "inverse-opposite", \
	zdt6r	us 1:7 w l ls 3 lw 5 ti "random"
#
set noautoscale x
set noautoscale y
set yrange[20:60]
set xrange[10000:50000]
set term pdf enhanced color
set output "dtlz6-hv-opschemes.pdf"
plot \
	dtlz6	us 1:7 w l ls 1 lw 5 ti "opposite", \
	dtlz6i	us 1:7 w l ls 2 lw 5 ti "inverse-opposite", \
	dtlz6r	us 1:7 w l ls 3 lw 5 ti "random"
