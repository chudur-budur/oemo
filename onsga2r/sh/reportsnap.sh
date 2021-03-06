#!/bin/bash
# this script generates a pdf report

shopt -s extglob ;
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd ) ;

rootpath=$1 ;
mingen=$2 ;
maxgen=$3 ;
skip=$4 ;
plotpp=$5 ;
zoom=$6 ;
problem=$7 ;
run=$8 ;
uid=`uuidgen`

_usage()
{
	#example 1: ./reportsnap ../experiments 1 100 5 8 0.4 zdt1 [run] 
	printf '%s\n\t\t   %s\n\n' "Usage: ./reportsnap [root path] [mingen] [maxgen]" \
		"[skip] [plot/page] [zoom] [problem] [run]";
	1>&2; exit 1;
}

if [[ -z $rootpath ]] || [[ -z $mingen ]] || [[ -z $maxgen ]] || [[ -z $skip ]] || 
	[[ -z $plotpp ]] || [[ -z $zoom ]] || [[ -z $problem ]]; then
	echo "error: some of the parameters are missing, hence exiting ...";
	_usage ;
fi

bs="\x5C" ;
tex=/tmp/plot-"$uid".tex ;

if [ -z "$run" ]; then
	run="1" ;
fi

"$cpath"/plotburst.py "$rootpath" "$problem" "$run" ;
plotdir="$rootpath"results/"$problem"/snaps-run-"$run" ;
if [ ! -d "$plotdir" ]; then
	echo "error: '$plotdir' not found, hence exiting ..." ;
	1>&2; exit 1;
fi

cat "$cpath"/header.tex > "$tex" ;
row=1;
for (( i=mingen; i<=maxgen; i=i+skip ))
do
	if [[ $row = 1 ]]; then
		printf "\t%cbegin{figure}[H]\n" "$bs" >> "$tex";
		printf "\t\t%ccentering\n" "$bs" >> "$tex";
	fi
	printf "\t\t%csubfigure[generation = ${i}]{\n" "$bs" >> "$tex" ;
	printf "\t\t\t%cincludegraphics[width=$zoom${bs}textwidth]" "$bs" >> "$tex" ;
	printf "{%s/gen-%d.pdf}}\n" "$plotdir" "$i" >> "$tex" ;
	row=$(( row+1 ));
	g=$(( plotpp+1 ));
	if [[ $(( row%g )) = 0 ]]; then
		printf "\t%cend{figure}\n" "$bs" >> "$tex";
		printf "\t%cvfill${bs}eject\n" "$bs" >> "$tex" ;
		row=1;
	elif [[ $(( i+skip )) -gt $maxgen ]]; then
		printf "\t%cend{figure}\n" "$bs" >> "$tex";
	fi
done
printf "%cend{document}\n" "$bs" >> "$tex";

if [ -f "$tex" ]; then
	pubtex "$tex" --pdl;
	rm -f "$tex" ;
	mv plot-"$uid".pdf "$rootpath"results/"$problem"/plot-run-"$run".pdf
else
	echo "error: '$tex' not found, could not compile to pdf." ;
	1>&2; exit 1;
fi

