#!/bin/bash
#comments: 

shopt -s extglob ;
cpath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd ) ;
echo "$cpath" ;

$cpath/survivalstat.py experiments/ zdt1 ;
$cpath/survivalstat.py experiments/ zdt2 ;
$cpath/survivalstat.py experiments/ zdt3 ;
$cpath/survivalstat.py experiments/ zdt4 ;
$cpath/survivalstat.py experiments/ zdt4-0.10 ;
$cpath/survivalstat.py experiments/ zdt4-0.25 ;
$cpath/survivalstat.py experiments/ zdt4-0.50 ;
$cpath/survivalstat.py experiments/ zdt4-0.75 ;
$cpath/survivalstat.py experiments/ zdt4-0.90 ;
$cpath/survivalstat.py experiments/ zdt6 ;
$cpath/survivalstat.py experiments/ zdt6-0.10 ;
$cpath/survivalstat.py experiments/ zdt6-0.25 ;
$cpath/survivalstat.py experiments/ zdt6-0.50 ;
$cpath/survivalstat.py experiments/ zdt6-0.75 ;
$cpath/survivalstat.py experiments/ zdt6-0.90 ;
$cpath/survivalstat.py experiments/ dtlz1 ;
$cpath/survivalstat.py experiments/ dtlz2 ;
$cpath/survivalstat.py experiments/ dtlz3 ;
$cpath/survivalstat.py experiments/ dtlz3-0.10 ;
$cpath/survivalstat.py experiments/ dtlz3-0.25 ;
$cpath/survivalstat.py experiments/ dtlz3-0.50 ;
$cpath/survivalstat.py experiments/ dtlz3-0.75 ;
$cpath/survivalstat.py experiments/ dtlz3-0.90 ;
$cpath/survivalstat.py experiments/ dtlz4 ;
$cpath/survivalstat.py experiments/ dtlz4-12 ;
$cpath/survivalstat.py experiments/ dtlz4-24 ;
$cpath/survivalstat.py experiments/ dtlz4-36 ;
$cpath/survivalstat.py experiments/ dtlz4-48 ;
$cpath/survivalstat.py experiments/ dtlz4-60 ;
$cpath/survivalstat.py experiments/ dtlz4-72 ;
$cpath/survivalstat.py experiments/ dtlz4-84 ;
$cpath/survivalstat.py experiments/ dtlz4-96 ;
$cpath/survivalstat.py experiments/ dtlz5 ;
$cpath/survivalstat.py experiments/ dtlz6 ;
$cpath/survivalstat.py experiments/ dtlz7 ;
$cpath/survivalstat.py experiments/ c1dtlz1 ;
$cpath/survivalstat.py experiments/ c1dtlz3 ;
$cpath/survivalstat.py experiments/ c2dtlz2 ;
$cpath/survivalstat.py experiments/ c3dtlz1 ;
$cpath/survivalstat.py experiments/ antenna ;
$cpath/survivalstat.py experiments/ crash ;
$cpath/survivalstat.py experiments/ osy ;

