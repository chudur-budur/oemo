#!/bin/bash
# runs a single test

shopt -s extglob ;
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd ) ;

executable=$1 ;
problemname=$2 ;
outdir=$3 ;
run=$4 ;
seed=$5 ;

_usage()
{
	# example: ./run MoeadExr zdt1 experiments/ 1 1234567890123
	printf '%s\n\t%s\n' "Usage: ./run [executable] [problem] [out-dir] [run-id] [seed]";
	1>&2; exit 1;
}

if [[ -z $executable ]] || [[ -z $problemname ]] || [[ -z $outdir ]]; then
	echo "error: some of the parameters are missing, hence exiting ...";
	_usage ;
fi

if [[ -z $run ]]; then
	run="1" ;
fi
if [[ -z $seed ]]; then
	seed="1234567890123" ;
fi

# get the executable name
execdir=`echo "${executable}" | awk '{print tolower($0)}'`;
# the target directory is experiments/nsga2r/zdt1 etc.
targetdir="${outdir}${execdir}/${problemname}" ;

# check outdir, i.e. experiments/
if [[ ! -e "${outdir}" ]]; then
	mkdir "${outdir}" ;
fi
# check exec dir, i.e. experiments/nsga2r
if [[ ! -e "${outdir}${execdir}" ]]; then
	mkdir "${outdir}${execdir}" ;
fi
# check problem dir, i.e. experiments/nsga2r/zdt1
if [[ ! -e "${outdir}${execdir}/${problemname}" ]]; then
	mkdir "${outdir}${execdir}/${problemname}" ;
fi

cpval=".:./libs/*:./bin/";
uid=$(uuidgen) ;
echo "********** START: run ${run} with seed: ${seed}, UUID: ${uid}." ;
java -cp "${cpval}" "${executable}" "${problemname}" "${seed}" "${uid}" ;

if [ -f "all_pop-${uid}.out" ]; then
	mv "all_pop-${uid}.out" "${targetdir}/all_pop-${run}.out" ;
fi
if [ -f "all_op_parent-${uid}.out" ]; then
	mv "all_op_parent-${uid}.out" "${targetdir}/all_op_parent-${run}.out" ;
fi
if [ -f "all_op_child-${uid}.out" ]; then
	mv "all_op_child-${uid}.out" "${targetdir}/all_op_child-${run}.out" ;
fi
if [ -f "all_survived-${uid}.out" ]; then
	mv "all_survived-${uid}.out" "${targetdir}/all_survived-${run}.out" ;
fi
if [ -f "all_extreme-${uid}.out" ]; then
	mv "all_extreme-${uid}.out" "${targetdir}/all_extreme-${run}.out" ;
fi
if [ -f "all_survival_stat-${uid}.out" ]; then
	mv "all_survival_stat-${uid}.out" "${targetdir}/all_survival_stat-${run}.out" ;
fi
if [ -f "all_overshoot_stat-${uid}.out" ]; then
	mv "all_overshoot_stat-${uid}.out" "${targetdir}/all_overshoot_stat-${run}.out" ;
fi
if [ -f "best_pop-${uid}.out" ]; then
	mv "best_pop-${uid}.out" "${targetdir}/best_pop-${run}.out" ;
fi
if [ -f "final_pop-${uid}.out" ]; then
	mv "final_pop-${uid}.out" "${targetdir}/final_pop-${run}.out" ;
fi
if [ -f "initial_pop-${uid}.out" ]; then
	mv "initial_pop-${uid}.out" "${targetdir}/initial_pop-${run}.out" ;
fi
if [ -f "params-${uid}.out" ]; then
	mv "params-${uid}.out" "${targetdir}/params-${run}.out" ;
fi

echo "********** END: run ${run} with seed: ${seed}, UUID: ${uid}" ;
