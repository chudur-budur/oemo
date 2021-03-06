#!/bin/bash
# runs n instances of a command in background on the localhost

shopt -s extglob ;
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd ) ;

setseed=0 ;
setindex=0 ;
cmd="" ;

_usage()
{
	# example: ./maprun -s -i -n 30 -c "ls -al"
	# example: ./maprun -s -i -n 30 -c "./sh/run MoeadExr dtlz7 experiments/"
	printf '%s\n\n' "Usage: ./maprun [-s] [-i] -n [n-instances] -c [any bash/unix command]" ;
	1>&2; exit 1 ;
}

while getopts "sin:c:" o; do
	case "${o}" in
		s)
			setseed=1; # echo "hit -r setseed: $setseed";
			;;
		i)
			setindex=1; # echo "hit -i setindex: $setindex";
			;;
		n)
			maxn=${OPTARG}; # echo "hit -n maxn: $maxn" ;
			;;
		c)
			cmd=${OPTARG}; # echo "hit -c cmd: $cmd" ;
			;;
		*)
			echo "error: some of the parameters are missing, hence exiting ...";
			_usage
			;;
	esac
done
shift $((OPTIND-1))

re='^[0-9]+$' ;
if [[ -z "${maxn}" ]] || ! [[ $maxn =~ $re ]] || [[ -z "${cmd}" ]]; then
	echo "error: some of the parameters are missing, hence exiting ...";
	_usage
fi

if [[ $setseed -eq 1 ]]; then
	if [ -f "${cpath}"/rseeds.in ]; then
		seeds=`cat "${cpath}"/rseeds.in` ;
		readarray -t rseed <<<"${seeds}" ;
	else
		echo "error: '${cpath}/rseeds.in' not found, hence exitting ...";
		_usage
	fi
fi

uid=$(uuidgen) ;
# outfile="/dev/null" ;
outfile="/tmp/log-run-$uid.out" ;
echo "" > "$outfile" ;

for (( i=1; i<=maxn; i++ ))
do
	j=$(( i - 1 )) ;
	printf '%s' "run ${i}: ";
        if [[ $setindex -eq 1 ]] && [[ $setseed -eq 1 ]]; then
		printf '%s\n' "nohup ${cmd[*]} ${i} ${rseed[j]} >>$outfile 2>&1 &" ;	
       		nohup ${cmd[@]} ${i} ${rseed[j]} >>$outfile 2>&1 &
	elif [[ $setindex -eq 1 ]] && [[ $setseed -eq 0 ]]; then
		printf '%s\n' "nohup ${cmd[*]} $i 0.12345 >>$outfile 2>&1 &" ;
       		nohup ${cmd[@]} ${i} 0.12345 >>$outfile 2>&1 &
	elif [[ $setindex -eq 0 ]] && [[ $setseed -eq 1 ]]; then
		printf '%s\n' "nohup ${cmd[*]} 1 ${rseed[j]} >>$outfile 2&1 &" ;
       		nohup ${cmd[@]} 1 ${rseed[j]} >>$outfile 2>&1 &
	else
		printf '%s\n' "nohup ${cmd[*]} >>$outfile 2>&1 &" ;
       		nohup ${cmd[@]} >> $outfile 2>&1 &
	fi
done
