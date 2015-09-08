#!/usr/local/bin/gnuplot

coloropt = "mono"

zdt4gen6 = "./data/zdt4-onsga2rw-gen-6.out"
zdt4gen15 = "./data/zdt4-onsga2rw-gen-15.out"
zdt4gen36 = "./data/zdt4-onsga2rw-gen-36.out"
colorfile = "~/gnuplot-utils/gnuplot-colorbrewer/qualitative/Dark2.plt"
greyfile = "~/gnuplot-utils/gnuplot-colorbrewer/sequential/Greys.plt"

if (coloropt eq "color") {
	reset
	set term pdf enhanced color
	set style fill transparent solid 0.75 noborder
	load colorfile
	set style circle radius screen 0.01
	unset key
	set xlabel "f1"
	set ylabel "f2"
	set yrange[0:100]
	set xrange[0:1]
	set label 1 "hit the pivot solution" at 0.33,52
	set arrow from 0.32,50 to 0.32,5.0 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-6.pdf"
	plot zdt4gen6 us 1:2 w circles ls 1 noti
	unset arrow
	unset label
	#
	set yrange[0:10]
	set label 2 "spread upward" at 0.2,2.5
	set arrow from 0.3,1 to 0.05,3.7 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-15.pdf"
	plot zdt4gen15 us 1:2 w circles ls 1 noti
	unset arrow
	unset label
	#
	set yrange[0:2]
	set label 3 "spread downward" at 0.45,0.75
	set arrow from 0.3,0.75 to 0.6,0.45 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-36.pdf"
	plot zdt4gen36 us 1:2 w circles ls 1 noti
} else {
	reset
	set term pdf enhanced color
	set style fill transparent solid 0.75 noborder
	load greyfile
	set style circle radius screen 0.01
	unset key
	set xlabel "f1"
	set ylabel "f2"
	set yrange[0:100]
	set xrange[0:1]
	set label 1 "hit the pivot solution" at 0.33,52
	set arrow from 0.32,50 to 0.32,5.0 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-6.pdf"
	plot zdt4gen6 us 1:2 w circles ls 7 noti
	unset arrow
	unset label
	#
	set yrange[0:10]
	set label 2 "spread upward" at 0.2,2.5
	set arrow from 0.3,1 to 0.05,3.7 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-15.pdf"
	plot zdt4gen15 us 1:2 w circles ls 7 noti
	unset arrow
	unset label
	#
	set yrange[0:2]
	set label 3 "spread downward" at 0.45,0.75
	set arrow from 0.3,0.75 to 0.6,0.45 size screen 0.015,30 lw 4
	set output "zdt4-hns-gen-36.pdf"
	plot zdt4gen36 us 1:2 w circles ls 7 noti
}
