#!/usr/local/bin/gnuplot

# plots 6 snapshots of CRASH problem

g1 = "#1d1d1d"
g2 = "#313131"
g3 = "#484848"
g4 = "#616161"
g5 = "#7b7b7b"
g6 = "#959595"
g7 = "#afafaf"

gens = "1 2 4 6 8 20"
do for [i = 1:words(gens)] {	
	g = word(gens, i)
	nsga2r_all 		= sprintf("data/crash/nsga2r-gen-%s.out", g)
	onsga2r_extreme 	= sprintf("data/crash/onsga2r-extreme-gen-%s.out", g)
	onsga2r_child 		= sprintf("data/crash/onsga2r-child-gen-%s.out", g)
	onsga2r_survived 	= sprintf("data/crash/onsga2r-survived-gen-%s.out", g)
	onsga2r_all 		= sprintf("data/crash/onsga2r-gen-%s.out", g)
	outfile			= sprintf("crash-g%s.pdf", g)
	
	print sprintf("doing monochrome plot: gen %s", g)

	reset
	# unset key 
	set key outside bottom horizontal nobox
	set xlabel "f1"
	set ylabel "f2"
	set zlabel "f3"
	if (g eq "1") { set xtics 1660,10,1705 }
	if (g eq "2" || g eq "4" || g eq "6") { set xtics 1660,10,1695 }
	if (g eq "8" || g eq "20") { set xtics 1660,5,1695 }
	if (g eq "4") { set xtics 1660,5,1690 }
	if (g eq "4" || g eq "6" || g eq "8" || g eq "20") { set ytics 6,1,11 }
	set view 69, 133

	set term push
	set term pdf enhanced monochrome
	set output outfile
	splot \
		nsga2r_all		u 1:2:3 w p pt 06 ps 0.75 lw 2 lc rgb g7 ti "nsga2", \
		onsga2r_all		u 1:2:3 w p pt 07 ps 0.50 lw 1 lc rgb g2 ti "algorithm 3", \
		onsga2r_extreme		u 1:2:3 w p pt 12 ps 1.50 lw 4 lc rgb g3 ti "Z*_b", \

	unset output
	set term pop
}
# onsga2r_child		u 1:2:3 w p pt 01 ps 0.50 lw 1 lc rgb g4 ti "x_c", \
# onsga2r_survived	u 1:2:3 w p pt 02 ps 0.50 lw 1 lc rgb g5 ti "survived"