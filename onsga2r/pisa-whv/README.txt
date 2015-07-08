WEIGHTED HYPERVOLUME INDICATOR
------------------------------

The package consists of 7 files:

Makefile
hyp_ind.c
hyp_ind_param.txt
premo_wdfs.c
premo_wdfs.h
testFront.txt
README.txt

usage:
1.) compile by calling 'make'
2.) run by calling './hyp_ind [<parameterFile>] <dataFile> <referenceSet> <outFile>', e.g.,
   './hyp_ind hyp_ind_param.txt testFront.txt testFront.txt  outFile.txt'
   where
   <param_file> specifies the name of the parameter file for eps_ind; the
       file has the following format:
 
         dim <integer>
         obj <+|-> <+|-> ...
         method <0|1>
         nadir <real> <real> ...
         ideal <real> <real> ...
         wdf <integer>
         hyp_ind_type <integer>
         reference_point <real> <real> ...
       The first line defines the number of objectives, the second for each
       objective whether it is minimized (-) or maximized, the third
       line determines whether the hypervolume is calculated relative to
       the reference set (1) or not (0). The forth and fifth line gives the
       coordinates of the nadir point, and ideal point respectively. Please
       ensure that they are conform with the minimization/maximization of
       the objectives according to the second line. With the wdf line, one
       chooses the underlying weight distribution function (0: usual
       hypervolume with constant weight distribution function; 1,2,3: weight
       distribution functions as described in zbt2007a.
       In addition, if hyp_ind_type == 0 no scaling is performed. Please ensure
       that all objective values are in [0,1] if you use other wdfs than 0.
       If hyp_ind_type == 1, the usual hypervolume is computed with an added
       term, the integral of an additional weight distribution function
       near the Pareto-optimal front, i.e., in [0,1] x ... x [0,1]
       If hyp_ind_type == 2, the usual hypervolume indicator is computed as
       with hyp_ind_type == 0. Furthermore, line integrals of constant weight
       distribution functions on the axes are added as described in
       zbt2007a (Section and Figure 3).
       The last line of the parameter file contains the coordinates of a
       reference point only used with the third weight distribution function
       (has only an influence iff wdf == 3).
  
       If the parameter file is omitted, the number of objectives is determined
       from the data file and it is assumed that all objectives are to be
       minimized, that the nadir point is (2.1, 2.1, ..., 2.1), the ideal
       point is (0,0,...,0), and that a reference set is given (method=1).
  
     <data_file> specifies a file that contains the output of one or
       several runs of a selector/variator pair; the format corresponds to
       the one defined in the specification of the PISA monitor program.
  
     <reference_set> is the name of a file that contains the reference set
       according to which the indicator values are calculated; the file
       format is the same as for the data file.
  
     <output_file> defines the name of the file to which the computed
       indicator values are written to.
  
   IMPORTANT: In order to make the output of this tool consistent with
     the other indicator tools, for method 0 (no reference set) the
     negative hypervolume is outputted as indicator value. Thus,
     independently of which type of problem (minimization,
     maximization, mixed minimization/maximization) and of which type
     of method (with or without reference set) one considers, a lower
     indicator value corresponds to a better approximation set.



AUTHORS
-------

Johannes Bader, Dimo Brockhoff* and Eckart Zitzler

e-mail: firstname.lastname@tik.ee.ethz.ch

*corresponding author


LICENCE
-------

All algorithms available on this website can be used for academic
purposes without fee. If you publish research results achieved using the following (weighted) hypervolume indicator please remember to
cite the corresponding paper EMO 2007 paper [zbt2007a].
The following copyright notice applies:

Copyright (c) 2002-2007 Swiss Federal Institute of Technology,
Computer Engineering and Networks Laboratory. All rights reserved.

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose, without fee, and without written
agreement is hereby granted, provided that the above copyright notice
and the following two paragraphs appear in all copies of this software.

IN NO EVENT SHALL THE SWISS FEDERAL INSTITUTE OF TECHNOLOGY, COMPUTER
ENGINEERING AND NETWORKS LABORATORY BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
THE SWISS FEDERAL INSTITUTE OF TECHNOLOGY, COMPUTER ENGINEERING AND
NETWORKS LABORATORY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE SWISS FEDERAL INSTITUTE OF TECHNOLOGY, COMPUTER ENGINEERING AND
NETWORKS LABORATORY, SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS
ON AN "AS IS" BASIS, AND THE SWISS FEDERAL INSTITUTE OF TECHNOLOGY,
COMPUTER ENGINEERING AND NETWORKS LABORATORY HAS NO OBLIGATION TO
PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


CHANGELOG
---------
2008/07/30 resolved memory bug with reference point of wdf 3 within
           scaleObjectiveValuesForMaximization function (db)
2007/08/10 first version online on web page
