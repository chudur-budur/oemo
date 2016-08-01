#!/usr/local/bin/gnuplot

g1 = "#1d1d1d"
g2 = "#313131"
g3 = "#484848"
g4 = "#616161"
g5 = "#7b7b7b"
g6 = "#959595"
g7 = "#afafaf"

# plots all antenna related stuffs from the actual data
#

# title option
titleopt = "false"

# the antenna pf plot
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Paired.plt"
} else {
	print "doing monochrome plot"
}
reset
unset output
set term push
set term pdf enhanced color
set output "antenna-pf.pdf"

nsga2r = "data/antenna/nsga2r-gen-200.out"
mcf = "data/antenna/antenna_mcf-c.out"
pivots = "data/antenna/pivots-sosolver.out"

set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
set ztics 0, 0.5, 2.0
set view 35, 311
set key at -10,350,2
if (titleopt eq "true") { set title "ANTENNNA: search space"}
splot \
	nsga2r	u 1:2:3 w p pt 06 ps 0.75 lw 1 lc rgb g2 ti "Pareto-front (NSGA-II)", \
	mcf	u 1:2:3 w p pt 06 ps 0.75 lw 1 lc rgb g7 ti "random solutions (5000)", \
	pivots	u 1:2:3 w p pt 12 ps 1.50 lw 4 lc rgb g4 ti "Z*_b", \


# plot 6 snapshots
set term pop
reset
unset output
set ztics 0, 0.5, 2.0
set view 35, 311
# set key outside bottom horizontal nobox
set key at -15,350,3
set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
gens = "3 20 90 200"
do for [i = 1:words(gens)] {
	g = word(gens, i)
	nsga2r		= sprintf("data/antenna/nsga2r-gen-%s.out", g)
	extreme		= sprintf("data/antenna/extreme-gen-%s.out", g)
	child		= sprintf("data/antenna/child-gen-%s.out", g)
	survived	= sprintf("data/antenna/survived-gen-%s.out", g)
	onsga2r		= sprintf("data/antenna/onsga2r-gen-%s.out", g)
	mcf		= "data/antenna/antenna_mcf-c.out"
	outfile		= sprintf("antenna-g%s.pdf", g)
	titlestr	= sprintf("generation: %s", g)
	
	print sprintf("doing monochrome plot, gen = %s", g)
	
	if (titleopt eq "true") { set title titlestr}
	set term push
	set term pdf enhanced color
	set output outfile
	splot \
		mcf		u 1:2:3 w p pt 06 ps 0.50 lw 1 lc rgb g7  ti "samples", \
		nsga2r		u 1:2:3 w p pt 06 ps 1.00 lw 4 lc rgb g4  ti "nsga2", \
		onsga2r		u 1:2:3 w p pt 07 ps 0.50 lw 1 lc rgb g3  ti "algorithm3", \
		extreme		u 1:2:3 w p pt 12 ps 1.50 lw 4 lc rgb g2  ti "Z*_b"

	unset output
	set term pop
}
# child		u 1:2:3 w p pt 06 ps 0.5 lc rgb g5  ti "x_c", \
# survived	u 1:2:3 w p pt 06 ps 0.5 lc rgb g6  ti "survived"
