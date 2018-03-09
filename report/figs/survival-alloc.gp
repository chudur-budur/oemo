#!/usr/local/bin/gnuplot

coloropt = "nocolor"

zdt4file10 = "../results/zdt4-0.10/zdt4-0.10-onsga2r-survival.stat"
zdt4file25 = "../results/zdt4-0.25/zdt4-0.25-onsga2r-survival.stat"
zdt4file50 = "../results/zdt4-0.50/zdt4-0.50-onsga2r-survival.stat"
zdt4file75 = "../results/zdt4-0.75/zdt4-0.75-onsga2r-survival.stat"
zdt4file90 = "../results/zdt4-0.90/zdt4-0.90-onsga2r-survival.stat"
#
zdt6file10 = "../results/zdt6-0.10/zdt6-0.10-onsga2r-survival.stat"
zdt6file25 = "../results/zdt6-0.25/zdt6-0.25-onsga2r-survival.stat"
zdt6file50 = "../results/zdt6-0.50/zdt6-0.50-onsga2r-survival.stat"
zdt6file75 = "../results/zdt6-0.75/zdt6-0.75-onsga2r-survival.stat"
zdt6file90 = "../results/zdt6-0.90/zdt6-0.90-onsga2r-survival.stat"
#
dtlz3file10 = "../results/dtlz3-0.10/dtlz3-0.10-onsga2r-survival.stat"
dtlz3file25 = "../results/dtlz3-0.25/dtlz3-0.25-onsga2r-survival.stat"
dtlz3file50 = "../results/dtlz3-0.50/dtlz3-0.50-onsga2r-survival.stat"
dtlz3file75 = "../results/dtlz3-0.75/dtlz3-0.75-onsga2r-survival.stat"
dtlz3file90 = "../results/dtlz3-0.90/dtlz3-0.90-onsga2r-survival.stat"

reset 
if (coloropt eq "color") {
	print "doing color plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/YlOrRd.plt"
} else {
	print "doing monochrome plot"
	load "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"
}
set term pdf enhanced color dashed
set output "zdt4-survival-trend.pdf"
set key top right
set xlabel "generations"
set ylabel "mean survival rate"
set ytics 0,5,100
yval = real(system(sprintf("./lastnmean.py %s 1 50", zdt4file10)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", zdt4file25)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", zdt4file50)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", zdt4file75)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", zdt4file90)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
plot \
	zdt4file10	w l ls 8 lw 5 ti "ratio = 10%", \
	zdt4file25	w l ls 7 lw 5 ti "ratio = 25%", \
	zdt4file50	w l ls 6 lw 5 ti "ratio = 50%", \
	zdt4file75	w l ls 5 lw 5 ti "ratio = 75%", \
	zdt4file90	w l ls 4 lw 5 ti "ratio = 90%"
#
unset arrow
set term pdf enhanced color dashed
set output "zdt6-survival-trend.pdf"
set key top right
set xlabel "generations"
set ylabel "mean survival rate"
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file10)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file25)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file50)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file75)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file90)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
plot \
	zdt6file10	w l ls 8 lw 5 ti "ratio = 10%", \
	zdt6file25	w l ls 7 lw 5 ti "ratio = 25%", \
	zdt6file50	w l ls 6 lw 5 ti "ratio = 50%", \
	zdt6file75	w l ls 5 lw 5 ti "ratio = 75%", \
	zdt6file90	w l ls 4 lw 5 ti "ratio = 90%"
#
unset arrow
set term pdf enhanced color dashed
set output "dtlz3-survival-trend.pdf"
set key top right
set xlabel "generations"
set ylabel "mean survival rate"
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file10)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file25)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file50)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file75)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
yval = real(system(sprintf("./lastnmean.py %s 1 50", dtlz3file90)))
set arrow from 0,yval to 200,yval nohead lt 3 lw 3
plot \
	dtlz3file10	w l ls 8 lw 5 ti "ratio = 10%", \
	dtlz3file25	w l ls 7 lw 5 ti "ratio = 25%", \
	dtlz3file50	w l ls 6 lw 5 ti "ratio = 50%", \
	dtlz3file75	w l ls 5 lw 5 ti "ratio = 75%", \
	dtlz3file90	w l ls 4 lw 5 ti "ratio = 90%"