#!/usr/local/bin/gnuplot

# the title option
titleopt = "false" 
# find the femin
femin(fname) = system(sprintf("cat %s | head -n 1 | awk -F\" \" '{print $1}'", fname))
# color palette
# color sequence for Dark2 1,8,3,1-2,8,3,1
# colorscheme = "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt" 
# color sequence for Greys 8,4,3,5-6,4,3,5
colorscheme = "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt" 

# onsga2r vs. nsga2r
probs = "zdt1 zdt2 zdt3 zdt4 zdt6 dtlz1 dtlz2 dtlz3 dtlz5 dtlz6 dtlz7 crash osy"
do for [i = 1:words(probs)] {
	prob = word(probs,i)
	algo1 = sprintf("results/%s/%s-nsga2r-hv.stat", prob, prob)
	algo2 = sprintf("results/%s/%s-onsga2r-hv.stat", prob, prob)
	outfile = sprintf("results/%s/%s-onsga2r-nsga2r-hvstatc.pdf", prob, prob)
	titlestr = sprintf("%s: SE vs. HV", prob)

	reset
	if(titleopt eq "true") { set title titlestr }
	set key bottom right
	set style fill noborder
	set boxwidth 0.5 relative
	load colorscheme
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	if(prob eq "dtlz5") { set xrange[0:5000] }
	if(prob eq "crash") { set xrange[0:8000]}
	if(prob eq "osy") { set xrange[0:30000] }
	set yrange[0:]
	plot \
		algo2 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3" whiskerbars 0.5, \
		algo2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
		algo2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
		algo2 using 1:4 with lines ls 5 lw 1 noti, \
		algo1 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
		algo1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
		algo1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
		algo1 using 1:4 with lines ls 5 lw 1 noti
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	liney = ymin + (ydiff * 0.075)
	# print "liney: ", liney
	txtstart = liney + (ydiff * 0.1)
	# print "txtstart: ", txtstart
	xthresh = 50
	minfe = femin(algo2)
	print sprintf("%s, minfe: %s", prob, minfe)
	set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
	set label 1 "cost to find Z*_b" rotate left at (minfe+xthresh)/2,txtstart
	set arrow from (minfe+xthresh)/2,txtstart-(ydiff * 0.01) \
		to (minfe+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	set term pop
}

# onsga2r vs. nsga2re
probs = "zdt1 zdt4 dtlz3 dtlz6 dtlz7"
do for [i = 1:words(probs)] {
	prob = word(probs,i)
	algo1 = sprintf("results/%s/%s-nsga2re-hv.stat", prob, prob)
	algo2 = sprintf("results/%s/%s-onsga2r-hv.stat", prob, prob)
	outfile = sprintf("results/%s/%s-onsga2r-nsga2re-hvstatc.pdf", prob, prob)
	titlestr = sprintf("%s: SE vs. HV", prob)

	reset
	if(titleopt eq "true") { set title titlestr }
	set key bottom right
	set style fill noborder
	set boxwidth 0.5 relative
	load colorscheme
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	set yrange[0:]
	plot \
		algo2 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3" whiskerbars 0.5, \
		algo2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
		algo2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
		algo2 using 1:4 with lines ls 3 lw 5 noti, \
		algo1 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 6 lw 3 title "nsga2re" whiskerbars 0.5, \
		algo1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
		algo1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
		algo1 using 1:4 with lines ls 5 lw 1 noti
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	liney = ymin + (ydiff * 0.5)
	# print "liney: ", liney
	txtstart = liney + (ydiff * 0.1)
	# print "txtstart: ", txtstart
	xthresh = 50
	minfe = femin(algo2)
	print sprintf("%s, minfe: %s", prob, minfe)
	set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
	set label 1 "cost to find Z*_b" rotate left at (minfe+xthresh)/2,txtstart
	set arrow from (minfe+xthresh)/2,txtstart-(ydiff * 0.01) \
		to (minfe+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	set term pop
}

# onsga2r vs. onsga2rw
probs = "dtlz3 dtlz6 zdt2 zdt3 zdt4"
do for [i = 1:words(probs)] {
	prob = word(probs,i)
	algo1 = sprintf("results/%s/%s-onsga2r-hv.stat", prob, prob)
	algo2 = sprintf("results/%s/%s-onsga2rw-hv.stat", prob, prob)
	outfile = sprintf("results/%s/%s-onsga2r-onsga2rw-hvstatc.pdf", prob, prob)
	titlestr = sprintf("%s: SE vs. HV", prob)

	reset
	if(titleopt eq "true") { set title titlestr }
	set key bottom right
	set style fill noborder
	set boxwidth 0.5 relative
	load colorscheme
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	if(prob eq "zdt2") { set xrange[0:6000] }
	if(prob eq "zdt4") { set xrange[0:12000] }
	if(prob eq "zdt3") { set xrange[0:10000] }
	set yrange[0:]
	plot \
		algo2 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 8 lw 3 title "algorithm 3(weighted)" whiskerbars 0.5, \
		algo2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
		algo2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
		algo2 using 1:4 with lines ls 3 lw 5 noti, \
		algo1 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 6 lw 3 title "algorithm 3" whiskerbars 0.5, \
		algo1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
		algo1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
		algo1 using 1:4 with lines ls 5 lw 1 noti
	minfe = femin(algo2)
	print sprintf("%s, minfe: %s", prob, minfe)
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	set term pop
}

# onsga2rwdom vs. nsga2r
probs = "zdt4 dtlz1"
do for [i = 1:words(probs)] {
	prob = word(probs,i)
	algo1 = sprintf("results/%s/%s-nsga2r-hv.stat", prob, prob)
	algo2 = sprintf("results/%s/%s-onsga2rwdom-hv.stat", prob, prob)
	outfile = sprintf("results/%s/%s-onsga2rwdom-nsga2r-hvstatc.pdf", prob, prob)
	titlestr = sprintf("%s: SE vs. HV", prob)

	reset
	if(titleopt eq "true") { set title titlestr }
	set key bottom right
	set style fill noborder
	set boxwidth 0.5 relative
	load colorscheme
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "zdt4") { set xrange[0:16000] }
	if(prob eq "dtlz1") { set xrange[0:30000] }
	set yrange[0:]
	plot \
		algo2 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 8 lw 3 title "onsga2r-wdom" whiskerbars 0.5, \
		algo2 using 1:7:7:7:7 with candlesticks ls 4 lw 3 title 'mean', \
		algo2 using 1:4:4:4:4 with candlesticks ls 3 lw 3 title 'median', \
		algo2 using 1:4 with lines ls 5 lw 1 noti, \
		algo1 using 1:3:2:6:5 with candlesticks \
				fs transparent solid 0.3 ls 6 lw 3 title "nsga2r" whiskerbars 0.5, \
		algo1 using 1:7:7:7:7 with candlesticks ls 4 lw 3 noti, \
		algo1 using 1:4:4:4:4 with candlesticks ls 3 lw 3 noti, \
		algo1 using 1:4 with lines ls 5 lw 1 noti
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	liney = ymin + (ydiff * 0.5)
	# print "liney: ", liney
	txtstart = liney + (ydiff * 0.1)
	# print "txtstart: ", txtstart
	xthresh = 50
	minfe = femin(algo2)
	print sprintf("%s, minfe: %s", prob, minfe)
	# set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
	# set label 1 "cost to find Z*_b" rotate left at (minfe+xthresh)/2,txtstart
	# set arrow from (minfe+xthresh)/2,txtstart-(ydiff * 0.01) \
	# 	to (minfe+xthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	set term pop
}
