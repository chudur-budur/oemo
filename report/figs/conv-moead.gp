#!/usr/local/bin/gnuplot

# function to find the femin
femin(fname) = system(sprintf("cat %s | head -n 1 | awk -F\" \" '{print $1}'", fname))

# title option: yes/no
showtitle = "no"
# color option: yes/no
coloropt = "yes"

# colorcheme and pallettes
if(coloropt eq "no") { seq1 = "3"; seq2 = "5"; seq3 = "8" } else { seq1 = "1"; seq2 = "2"; seq3 = "3" }
# color pallettes
# color sequence for Dark2 1,8,3,1-2,8,3,1
rgbscheme = "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt" 
# color sequence for Greys 8,4,3,5-6,4,3,5
greyscheme = "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt" 

# onsga2r, moeadexr and moeadr the conv plot.
print sprintf("re-coloring onsga2r vs. moeadexr vs. moeadr")
probs = "zdt4 zdt6 dtlz6 dtlz7"
do for [i = 1:words(probs)] {
	# set up file names
	prob = word(probs, i)
	algo1 = sprintf("../results/%s/%s-moeadexr-hv.stat", prob, prob)
	algo2 = sprintf("../results/%s/%s-moeadr-hv.stat", prob, prob)
	algo3 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
	if(coloropt eq "no") {
		outfile = sprintf("../results/%s/%s-onsga2r-moeadexr-hvstatg.pdf", prob, prob)
	} else {
		outfile = sprintf("../results/%s/%s-onsga2r-moeadexr-hvstatc.pdf", prob, prob)
	}
	titlestr = sprintf("%s: SE vs. HV", prob)
	# now do the plot
	reset
	set term push
	set term unknown
	if(showtitle eq "yes") { set title titlestr }
	set key bottom right
	if(prob eq "dtlz6") { set key top left }
	if(prob eq "zdt4") { set key top left }
	set style fill border
	if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
	set xlabel "solution evaluations"
	set ylabel "hypervolume"
	set format x "%.1s%c"
	set xrange[0:]
	if(prob eq "zdt4") { set xrange[-1250:20000] }
	set yrange[0:]
	plot \
		algo1 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq1 lw 3 ti "moea/d(e)", \
		algo2 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq2 lw 3 ti "moea/d", \
		algo3 using 1:2:6 with filledcu \
			fs transparent solid 0.75 ls seq3 lw 3 ti "algorithm 3", \
		algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
		algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
		algo3 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
		algo3 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
	ymin = GPVAL_Y_MIN
	ymax = GPVAL_Y_MAX
	deltay = (ymax - ymin)
	deltax = femin(algo1) + 0
	print sprintf("\t%s: ymin: %.2f, ymax: %.2f, deltay: %.2f, deltax: %.2f", \
				prob, ymin, ymax, deltay, deltax)
	tx = 0.05
	ty = 0.20
	tthreshx = (deltax * tx)
	tthreshy = (deltay * ty)
	# horizontal t-bar
	set arrow from (0 + tthreshx),tthreshy to \
		(deltax - tthreshx),tthreshy heads size screen 0.005,90 lw 4 
	ax = 0.50
	ay = 0.01
	arrowlen = 0.30
	if(prob eq "zdt4") { arrowlen = 0.05 } 
	if(prob eq "dtlz6") { arrowlen = 0.05 } 
	if(prob eq "dtlz7") { arrowlen = 0.42 } 
	athreshx = (deltax * ax)
	athreshy = (deltay * ay) 
	# vertical arrow
	set arrow from 0 + athreshx, tthreshy + (deltay * arrowlen) \
		to 0 + athreshx, tthreshy + athreshy size screen 0.01,45 lw 3
	# vertical text
	set label 1 "cost to find Z*_b" rotate left at \
		0 + athreshx, athreshy + tthreshy + (deltay * arrowlen) 
	set term pop
	replot
	set term push
	set term pdf enhanced color
	set output outfile
	replot
	unset output
	set term pop
}
