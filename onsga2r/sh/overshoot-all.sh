#!/bin/bash
#comments: 

shopt -s extglob
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

echo "overshoot stat zdt1" ;
./sh/overshootstat.py experiments/ zdt1 ;
echo "overshoot stat zdt2" ;
./sh/overshootstat.py experiments/ zdt2 ;
echo "overshoot stat zdt3" ;
./sh/overshootstat.py experiments/ zdt3 ;
echo "overshoot stat zdt4" ;
./sh/overshootstat.py experiments/ zdt4 ;
echo "overshoot stat zdt6" ;
./sh/overshootstat.py experiments/ zdt6 ;
echo "overshoot stat dtlz1" ;
./sh/overshootstat.py experiments/ dtlz1 ;
echo "overshoot stat dtlz2" ;
./sh/overshootstat.py experiments/ dtlz2 ;
echo "overshoot stat dtlz3" ;
./sh/overshootstat.py experiments/ dtlz3 ;
echo "overshoot stat dtlz4" ;
./sh/overshootstat.py experiments/ dtlz4 ;
echo "overshoot stat dtlz5" ;
./sh/overshootstat.py experiments/ dtlz5 ;
echo "overshoot stat dtlz6" ;
./sh/overshootstat.py experiments/ dtlz6 ;
echo "overshoot stat dtlz7" ;
./sh/overshootstat.py experiments/ dtlz7 ;
