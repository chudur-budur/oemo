#!/usr/local/bin/gnuplot

coloropt = "mono"

if (coloropt eq "color") {
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
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 1 lw 3 title "onsga2r" whiskerbars 0.5, \
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	using 1:7:7:7:7 with candlesticks ls 8 lw 3 title 'mean', \
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
        "../results/zdt4/zdt4-nsga2r-hv.stat"		using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 2 lw 3 title "nsga2r" whiskerbars 0.5, \
	"../results/zdt4/zdt4-nsga2r-hv.stat"   using 1:7:7:7:7 with candlesticks ls 8 lw 3 noti, \
	"../results/zdt4/zdt4-nsga2r-hv.stat"   using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti

set output "dtlz1-weak.pdf"
plot \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 1 lw 3 title "onsga2r" whiskerbars 0.5, \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	using 1:7:7:7:7 with candlesticks ls 8 lw 3 title 'mean', \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
        "../results/dtlz1/dtlz1-nsga2r-hv.stat"		using 1:3:2:6:5 with candlesticks \
		fs transparent solid 0.3 ls 2 lw 3 title "nsga2r" whiskerbars 0.5, \
	"../results/dtlz1/dtlz1-nsga2r-hv.stat"		using 1:7:7:7:7 with candlesticks ls 8 lw 3 noti, \
	"../results/dtlz1/dtlz1-nsga2r-hv.stat"		using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti
} else {
reset
set term pdf monochrome
set output "zdt4-weak.pdf"
set key bottom right
set style fill pattern noborder
set boxwidth 0.5 relative
set xlabel "function evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:]
set yrange[0:]
plot \
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	us 1:3:2:6:5 w candlesticks\
		fs transparent solid 0.1 ls 3 ti "onsga2r" whiskerbars 0.5, \
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	us 1:7:7:7:7 w candlesticks fs solid 1 ti 'mean', \
	"../results/zdt4/zdt4-onsga2rwdom-hv.stat"	us 1:4:4:4:4 w candlesticks fs solid 1 ti 'median', \
        "../results/zdt4/zdt4-nsga2r-hv.stat"		us 1:3:2:6:5 w candlesticks\
		fs pattern 1 ti "nsga2r" whiskerbars 0.5, \
	"../results/zdt4/zdt4-nsga2r-hv.stat"   us 1:7:7:7:7 w candlesticks fs solid 1 noti, \
	"../results/zdt4/zdt4-nsga2r-hv.stat"   us 1:4:4:4:4 w candlesticks fs solid 1 noti

set output "dtlz1-weak.pdf"
plot \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	us 1:3:2:6:5 w candlesticks \
		fs transparent solid 0.1 ls 3 ti "onsga2r" whiskerbars 0.5, \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	us 1:7:7:7:7 w candlesticks fs solid 1 title 'mean', \
	"../results/dtlz1/dtlz1-onsga2rwdom-hv.stat"	us 1:4:4:4:4 w candlesticks fs solid 1 title 'median', \
        "../results/dtlz1/dtlz1-nsga2r-hv.stat"		us 1:3:2:6:5 w candlesticks \
		fs pattern 1 ti "nsga2r" whiskerbars 0.5, \
	"../results/dtlz1/dtlz1-nsga2r-hv.stat"		us 1:7:7:7:7 w candlesticks fs solid 1 noti, \
	"../results/dtlz1/dtlz1-nsga2r-hv.stat"		us 1:4:4:4:4 w candlesticks fs solid 1 noti
}
