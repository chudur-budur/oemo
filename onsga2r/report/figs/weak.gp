#!/usr/local/bin/gnuplot

zdt4file1 = "../results/zdt4/zdt4-onsga2rwdom-hv.stat"
zdt4file2 = "../results/zdt4/zdt4-nsga2r-hv.stat"
dtlz1file1 = "../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"
dtlz1file2 = "../results/dtlz1/dtlz1-nsga2r-hv.stat"

coloropt = "nocolor"

reset
if (coloropt eq "color") {
	# 1,8,3,3-2,8,3,3
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
	set term pdf enhanced color
	set style fill noborder
} else {
	# 8,4,3,5-6,4,3,5
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
	set term pdf enhanced color
	set style fill noborder
}
set output "zdt4-weak.pdf"
set key bottom right
set boxwidth 0.5 relative
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:]
set yrange[0:]
plot \
	zdt4file1 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3" whiskerbars 0.5, \
	zdt4file1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
	zdt4file1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
	zdt4file1 using 1:4 with lines ls 5 lw 1 noti, \
        zdt4file2 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
	zdt4file2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	zdt4file2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	zdt4file2 using 1:4 with lines ls 5 lw 1 noti
#
set output "dtlz1-weak.pdf"
plot \
	dtlz1file1 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3" whiskerbars 0.5, \
	dtlz1file1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
	dtlz1file1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
	dtlz1file1 using 1:4 with lines ls 5 lw 1 noti, \
        dtlz1file2 using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
	dtlz1file2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
	dtlz1file2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
	dtlz1file2 using 1:4 with lines ls 5 lw 1 noti

