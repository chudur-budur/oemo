#!/bin/bash
#comments: 

shopt -s extglob
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

echo "plotting zdt1"
./sh/plothv.py experiments/ zdt1 150 ;
echo "plotting zdt2"
./sh/plothv.py experiments/ zdt2 150 ;
echo "plotting zdt3"
./sh/plothv.py experiments/ zdt3 150 ;
echo "plotting zdt4"
./sh/plothv.py experiments/ zdt4 150 ;
echo "plotting zdt6"
./sh/plothv.py experiments/ zdt6 150 ;

echo "plotting dtlz1"
./sh/plothv.py experiments/ dtlz1 150 ;
echo "plotting dtlz2"
./sh/plothv.py experiments/ dtlz2 150 ;
echo "plotting dtlz3"
./sh/plothv.py experiments/ dtlz3 150 ;
echo "plotting dtlz4"
./sh/plothv.py experiments/ dtlz4 150 ;
echo "plotting dtlz5"
./sh/plothv.py experiments/ dtlz5 150 ;
echo "plotting dtlz6"
./sh/plothv.py experiments/ dtlz6 150 ;
echo "plotting dtlz7"
./sh/plothv.py experiments/ dtlz7 150 ;
