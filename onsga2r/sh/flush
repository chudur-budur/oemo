#!/bin/bash
#comments: 

shopt -s extglob
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

algorithm=$1
problem=$2

_usage()
{
	# example: ./flush nsga2r zdt1
	printf '%s\n\n' "Usage: ./flush [algorithm] [problem]" ;
	1>&2; exit 1 ;
}

if [[ -z $algorithm || -z $problem ]]; then
	echo "error: some of the parameters are missing, hence exiting ...";
	_usage ;
fi

echo "rm -rf experiments/$algorithm/$problem/*" ;
rm -rf experiments/$algorithm/$problem/* ;
