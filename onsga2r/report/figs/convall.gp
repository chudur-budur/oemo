#!/usr/local/bin/gnuplot

# function to find the femin
femin(fname) = system(sprintf("cat %s | head -n 1 | awk -F\" \" '{print $1}'", fname))

# title option: yes/no
showtitle = "no"
# color option: yes/no
coloropt = "yes"

# colorcheme and pallettes
if(coloropt eq "no") { seq1 = "5"; seq2 = "7"; seq3 = "8" } else { seq1 = "1"; seq2 = "2"; seq3 = "3" }
# color pallettes
# color sequence for Dark2 1,8,3,1-2,8,3,1
rgbscheme = "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt" 
# color sequence for Greys 8,4,3,5-6,4,3,5
greyscheme = "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt" 

# nsga2r vs. onsga2r
print sprintf("re-coloring nsga2r vs. onsga2r")
probs = "zdt1 zdt2 zdt3 zdt4 zdt6 dtlz1 dtlz2 dtlz3 dtlz4 dtlz5 dtlz6 dtlz7 crash antenna osy"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-nsga2r-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-onsga2r-nsga2r-hvstat.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-onsga2r-nsga2r-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	# set macros
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	if(prob eq "dtlz5") { set xrange[0:5000]  }
	if(prob eq "crash") { set xrange[0:8000]  }
	if(prob eq "osy")   { set xrange[0:30000] }
	set yrange[0:]
	plot \
		algo1 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq1 lw 3 ti "nsga2r", \
		algo2 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	# where to put t-bar, default 0.075
	ydiffr = 0.075
	if(prob eq "zdt3") { ydiffr = 0.50 }
	liney = ymin + (ydiff * ydiffr)
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
	# unset macros
	set term pop
}

# nsga2re vs. onsga2r
print sprintf("re-coloring nsga2re vs. onsga2r")
probs = "zdt1 zdt4 dtlz3 dtlz6 dtlz7"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-nsga2re-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-onsga2r-nsga2re-hvstat.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-onsga2r-nsga2re-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	# set macros
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	set yrange[0:]
	plot \
		algo1 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq1 lw 3 ti "nsga2re", \
		algo2 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
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
	# unset macros
	set term pop
}

# onsga2r vs. onsga2rw
print sprintf("re-coloring onsga2r vs. onsga2rw")
probs = "dtlz3 dtlz6 zdt2 zdt3 zdt4"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-onsga2rw-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-onsga2r-onsga2rw-hvstat.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-onsga2r-onsga2rw-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	# set macros
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "dtlz6") { set xrange[0:40000] }
	if(prob eq "zdt2")  { set xrange[0:6000]  }
	if(prob eq "zdt4")  { set xrange[0:12000] }
	if(prob eq "zdt3")  { set xrange[0:10000] }
	set yrange[0:]
	plot \
		algo1 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq1 lw 3 ti "algorithm 3 (< m)", \
		algo2 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
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
	# unset macros
	set term pop
}

# nsga2r vs. onsga2rwdom
print sprintf("re-coloring nsga2r vs. onsga2rwdom")
probs = "zdt4 dtlz1"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-nsga2r-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-onsga2rwdom-hv.stat", prob, prob)
	algo3 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-nsga2r-onsga2rwdom-hvstat.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-nsga2r-onsga2rwdom-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	# set macros
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "zdt4")  { set xrange[0:16000] }
	if(prob eq "dtlz1") { set xrange[0:30000] }
	set yrange[0:]
	plot \
		algo1 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq1 lw 3 ti "nsga2", \
		algo2 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3 (weak)", \
		algo3 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq3 lw 3 ti "algorithm 3", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo3 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
		algo3 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	# default ydiffr
	ydiffr = 0.075
	if(prob eq "zdt4")  { ydiffr = 0.5 }
	if(prob eq "dtlz1") { ydiffr = 0.075 }
	liney = ymin + (ydiff * ydiffr)
	# print "liney: ", liney
	txtstart = liney + (ydiff * 0.1)
	# print "txtstart: ", txtstart
	# default xtresh
	xthresh = 50
	minfe = femin(algo3)
	print sprintf("%s, minfe: %s", prob, minfe)
	# horizontal t-bar
	set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
	txtthresh = 50
	if(prob eq "dtlz1") { txtthresh = 5000 }
	set label 1 "cost to find Z*_b" rotate left at (minfe+txtthresh)/2,txtstart
	# vertical arrow
	set arrow from (minfe+txtthresh)/2,txtstart-(ydiff * 0.01) \
		to (minfe+txtthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	# unset macros
	set term pop
}

# nsga2r vs. onsga2r on constrained problems
print sprintf("re-coloring nsga2r vs. onsga2r for constrained problems")
probs = "c1dtlz1 c1dtlz3"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-nsga2r-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-nsga2r-onsga2r-hvstat.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-nsga2r-onsga2r-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	# set macros
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	set yrange[0:]
	plot \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.75 pt 4 pi 10 ti "nsga2 (mean)", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.75 pt 6 pi 10 ti "nsga2 (median)", \
		algo1 using 1:6 with lp lc rgb "#000000" lw 1 ps 0.75 pt 8 pi 10 ti "nsga2 (max)", \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.75 pt 5 pi 10 ti "algorithm 3 (mean)", \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.75 pt 7 pi 10 ti "algorithm (median)", \
		algo2 using 1:6 with lp lc rgb "#000000" lw 1 ps 0.75 pt 9 pi 10 ti "algorithm (max)", \
	ydiff = (GPVAL_Y_MAX - GPVAL_X_MIN)
	# print "ydiff: ", ydiff
	ymin = GPVAL_Y_MIN
	# print "ymin: ", ymin
	# default ydiffr
	ydiffr = 0.25
	liney = ymin + (ydiff * ydiffr)
	# print "liney: ", liney
	txtstart = liney + (ydiff * ydiffr)
	# print "txtstart: ", txtstart
	# default xtresh
	xthresh = 50
	minfe = femin(algo3)
	print sprintf("%s, minfe: %s", prob, minfe)
	# horizontal t-bar
	set arrow from 0+xthresh,liney to minfe-xthresh,liney heads size screen 0.005,90 lw 4 
	txtthresh = 50
	set label 1 "cost to find Z*_b" rotate left at (minfe+txtthresh)/2,txtstart
	# vertical arrow
	set arrow from (minfe+txtthresh)/2,txtstart-(ydiff * 0.01) \
		to (minfe+txtthresh)/2,liney+(ydiff * 0.01) size screen 0.01,45 lw 3
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	# unset macros
	set term pop
}
