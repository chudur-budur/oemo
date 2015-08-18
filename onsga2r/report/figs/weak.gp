#!/usr/local/bin/gnuplot

reset
set term pdf enhanced color
set output "zdt4-weak.pdf"
set key bottom right
set style fill noborder
set boxwidth 0.5 relative
load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:]
set yrange[0:]
plot \
	"./data/zdt4-onsga2r-hv-weak.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 1 lw 3 title "onsga2r" whiskerbars 0.5, \
	"./data/zdt4-onsga2r-hv-weak.stat"	using 1:7:7:7:7 with candlesticks ls 8 lw 3 title 'mean', \
	"./data/zdt4-onsga2r-hv-weak.stat"	using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
        "./data/zdt4-nsga2r-hv-weak.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 2 lw 3 title "nsga2r" whiskerbars 0.5, \
	"./data/zdt4-nsga2r-hv-weak.stat"   using 1:7:7:7:7 with candlesticks ls 8 lw 3 noti, \
	"./data/zdt4-nsga2r-hv-weak.stat"   using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti

set output "dtlz1-weak.pdf"
plot \
	"./data/dtlz1-onsga2r-hv-weak.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 1 lw 3 title "onsga2r" whiskerbars 0.5, \
	"./data/dtlz1-onsga2r-hv-weak.stat"	using 1:7:7:7:7 with candlesticks ls 8 lw 3 title 'mean', \
	"./data/dtlz1-onsga2r-hv-weak.stat"	using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
        "./data/dtlz1-nsga2r-hv-weak.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 2 lw 3 title "nsga2r" whiskerbars 0.5, \
	"./data/dtlz1-nsga2r-hv-weak.stat"   using 1:7:7:7:7 with candlesticks ls 8 lw 3 noti, \
	"./data/dtlz1-nsga2r-hv-weak.stat"   using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti
