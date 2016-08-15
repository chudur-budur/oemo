#!/usr/local/bin/gnuplot

# plots the radiation pattern from the radiation data
# you need to invoke this script like 
#	gnuplot -e "filename='foo.data'" radiation.gp

len = strlen(filename)
outfile = sprintf("%s.pdf", filename[1:len-4])
print(outfile)

reset
set size square
set angles degrees
set polar
set grid polar 15.
unset border
unset param
set xlabel "Azimuth (theta)"
set ylabel "Gain (dB)"
set style data line
set rrange[-100:0]
set trange[*:*]
set xrange[-100:100]
set yrange[-100:100]
unset xtics
set term push
set term pdf size 3.5,3.5 enhanced color
set output outfile
print sprintf("saving %s ...", outfile)
plot filename u 1:2 w l lw 4 lc rgb "black" noti
set term pop
