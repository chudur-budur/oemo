#!/usr/local/bin/gnuplot -persist

# common settings
set xlabel "f1"
set ylabel "f2"
set zlabel "f3"
set xrange[0:1.15]
set yrange[0:1.15]
set zrange[0:1.15]
set xtics 0,0.2,1.15
set ytics 0,0.2,1.15
set ztics 0,0.2,1.15
set grid xtics lt 0 lw 1 lc rgb "black"
set grid ytics lt 0 lw 1 lc rgb "black"
set view equal xyz
set view 60,15
set xyplane at 0
set isosamples 15
set hidden3d
unset key

# plot the spherical PF
set term wxt 0
set parametric
set urange[0:0.5 * pi]
set vrange[0:0.5 * pi]
r = 1
fx(v,u) = r * cos(v) * cos(u)
fy(v,u) = r * sin(u) * cos(v)
fz(v) = r * sin(v)
set label 1 "C" font "Arial, 15" front at 0.525, 0.000, 0.750 
set label 2 "A" font "Arial, 15" front at 0.050, 0.000, 0.900
set label 3 "B" font "Arial, 15" front at 1.050, 0.105, 0.000
splot fx(u,v), fy(u,v), fz(u), \
	"< echo '0.000 0.000 1.000'" with points pt 7 lc rgb 'black', \
	"< echo '1.000 0.000 0.000'" with points pt 7 lc rgb 'black', \
	"< echo '0.525 0.000 0.851'" with points pt 7 lc rgb 'black'
set term push
set term pdf enhanced mono
set output "b1.pdf"
replot
unset output
set term pop
system(sprintf("%s", "pdfcrop b1.pdf b1.pdf"))

unset pm3d
unset hidden3d
unset isosamples
unset parametric
unset label
set term wxt 1
set view 57, 64
set xyplane at 0
# set grid ztics lt 0 lw 1 lc rgb "black"
set border 4095 lt 0 lw 1 lc rgb "black"
set object 1 polygon from 1,0,1 to 0,1,1 to 1,1,0 to 1,0,1 \
	fillstyle transparent solid 0.33 lw 1
set label 1 "C" font "Arial, 15" front at 1.100, 0.000, 1.100 
set label 2 "A" font "Arial, 15" front at 0.000, 1.050, 1.050
set label 3 "B" font "Arial, 15" front at 1.050, 1.050, 0.000
splot 1/0 notitle, \
	"< echo '1.000 0.000 1.000'" with points pt 7 lc rgb 'black', \
 	"< echo '0.000 1.000 1.000'" with points pt 7 lc rgb 'black', \
 	"< echo '1.000 1.000 0.000'" with points pt 7 lc rgb 'black'
set term push
set term pdf enhanced mono
set output "b2.pdf"
replot
unset output
set term pop
system(sprintf("%s", "pdfcrop b2.pdf b2.pdf"))
