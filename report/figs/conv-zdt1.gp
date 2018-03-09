#!/usr/local/bin/gnuplot -persist

# You need to run this script after conv-all.gp is done.

# function to find the femin
femin(fname) = system(sprintf("cat %s | head -n 1 | awk -F\" \" '{print $1}'", fname))

# title option: yes/no
showtitle = "no"
# color option: yes/no
coloropt = "no"

# colorcheme and pallettes
if(coloropt eq "no") { seq1 = "5"; seq2 = "7"; seq3 = "8" } else { seq1 = "1"; seq2 = "2"; seq3 = "3" }
# color pallettes
# color sequence for Dark2 1,8,3,1-2,8,3,1
rgbscheme = "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt" 
# color sequence for Greys 8,4,3,5-6,4,3,5
greyscheme = "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt" 

# nsga2r vs. onsga2r, the conv plot for antenna is done at the end.
print sprintf("re-coloring nsga2r vs. onsga2r and also onsga2r hv with extremes.")
# set up file names
prob = "zdt1"
algo1 = sprintf("../results/%s/%s-nsga2r-hv.stat", prob, prob)
algo2 = sprintf("../results/%s/%s-onsga2r-hv.stat", prob, prob)
algo3 = sprintf("../results/%s/%s-onsga2r-hvwe.stat", prob, prob)
if(coloropt eq "no") {
	outfile = sprintf("../results/%s/%s-onsga2r-nsga2r-hvwestatg.pdf", prob, prob)
} else {
	outfile = sprintf("../results/%s/%s-onsga2r-nsga2r-hvwestatc.pdf", prob, prob)
}
titlestr = sprintf("%s: SE vs. HV", prob)
# now do the plot
reset
set term pdf enhanced color
set output outfile
set multiplot
if(showtitle eq "yes") { set title titlestr }
# set key bottom right
unset key
set style fill border
if(coloropt eq "yes") { load rgbscheme } else { load greyscheme }
set xlabel "solution evaluations"
set ylabel "hypervolume"
set format x "%.1s%c"
set xrange[0:13000]
set yrange[0:]
ymin = 0.00
ymax = 4.00
deltay = (ymax - ymin)
deltax = femin(algo2) + 0
print sprintf("\t%s: ymin: %.2f, ymax: %.2f, deltay: %.2f, deltax: %.2f", \
			prob, ymin, ymax, deltay, deltax)
tx = 0.05
ty = 0.50
tthreshx = (deltax * tx)
tthreshy = (deltay * ty)
# horizontal t-bar
set arrow from (0 + tthreshx),tthreshy to \
	(deltax - tthreshx),tthreshy heads size screen 0.005,90 lw 4 
ax = 0.50
ay = 0.01
arrowlen = 0.10
athreshx = (deltax * ax)
athreshy = (deltay * ay) 
# vertical arrow and text
set arrow from 0 + athreshx, tthreshy + (deltay * arrowlen) \
	to 0 + athreshx, tthreshy + athreshy size screen 0.01,45 lw 3
set label 1 "cost to find Z*_b" rotate left at \
	0 + athreshx, athreshy + tthreshy + (deltay * arrowlen)
# arrows for algorithms
set arrow from 4600,1.00 to 9000,1.00 lw 2
set label 2 "Algorithm 3" at 9100,1.00
set label 3 "HV without extreme points" at 8000,0.75
set arrow from 4650,2.15 to 9000,2.00 lw 2
set label 4 "Algorithm 3" at 9100,2.00
set label 5 "HV with extreme points" at 8000,1.75
set arrow from 6750,2.30 to 9000,2.30 lw 2
set label 6 "NSGA-II HV" at 9100,2.30
plot \
	algo1 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq1 lw 3 ti "nsga2r", \
	algo2 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3", \
	algo3 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq3 lw 3 ti "algorithm 3", \
	algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
	algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
	algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
	algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
	algo3 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 ti "median", \
	algo3 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 ti "mean"
# now do the inset
set origin 0.3, 0.20
set size 0.30, 0.60
unset key
unset arrow
unset label
unset xlabel
unset ylabel
set xrange [1400:2250]
set yrange [1:3.75]
set xtics 500
# set bmargin 1
# set tmargin 1
# set lmargin 1
# set rmargin 1
plot \
	algo1 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq1 lw 3 ti "nsga2r", \
	algo2 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq2 lw 3 ti "algorithm 3", \
	algo3 using 1:2:6 with filledcu \
		fs transparent solid 0.75 ls seq3 lw 3 ti "algorithm 3", \
	algo1 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
	algo1 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
	algo2 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
	algo2 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti, \
	algo3 using 1:4 with lp lc rgb "#000000" lw 1 ps 0.5 pt 1 pi 10 noti, \
	algo3 using 1:7 with lp lc rgb "#000000" lw 1 ps 0.5 pt 2 pi 10 noti
unset multiplot
unset output
set term pop
