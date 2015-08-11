TODO
=====

#### **Current Algorithm:**

##### **1. Finding the extreme points**

- ~~Use global search, namely GA (but it takes a huge function evaluations)~~

- Instead of GA, we are now using classical methods, after a very extensive painstaking empirical experiments we propose a definitive regimen to find the extreme points using a mixture of Interior point method, and generalized pattern search (namely, Mesh Adaptive Direct Search). The pair of algorithms were run on a single objective once and and AASF version of the same objective function. Now we can find the extreme points in a reasonable amount of FE. For different problems we have found different parameters for the Interior Point Method and MADS algorithm.

- For 3 obj dtlz problems, some times we get 2 extreme points, not the 3rd one.

##### **2. Opposite Point Generation:**
Let's denote the points as --

- e*: hard-coded extreme found from GA
- e: current population extremes
- g: least crowded non-extreme points in the current population (i.e. intermediary gaps).

##### *Algorithm:*
- make a set with S = {e U e*}
- apply non-domiated sorting on S
- now partition them into two sets, S = {S1, S2}; where S1 has all the points on front 1 and crowding distance of infinity, and rest of the points goes into S2.
- now if there is any point in S2 that is weakly dominated by any point in the S1, then discard the weakly dominating point from S1 and include the dominated point from S2, we are doing this to maintain a large spread on the true PF.

#### **Results:**

Set of algorithms: 

- onsga2: opposition based nsga2
- nsga2e: nsga2 with extreme points injection
- nsga2: standard nsga2 with FE compensated for extreme point computation. 
- x >> y: means algorithm x is strictly better than algorithm y
- x ~ y: means algorithm x is comparable to algorithm y
- x > y: means algorithm x is better in a sense that it is more robust than y
- *: means the problem is converted to harder version (i.e. variable length is increased by some N factors)

1. **ZDT set (M = 2):**
    - zdt1: onsga2 >> nsga2, onsga2 > nsga2e 
    - zdt2: onsga2 >> nsga2, onsga2 > nsga2e 
    - zdt3: onsga2 >> nsga2, onsga2 > nsga2e 
    - zdt4: onsga2 << nsga2, onsga2 < nsga2e *(not good)*
    - zdt6: onsga2 >> nsga2, onsga2 > nsga2e 

2. **DTLZ set (M = 3):**
   - dtlz1* (planar): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz2* (spherical): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz3* (local optima): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz4 (different density): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz5 (3d curved pf, easy): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz6 (3d curved pf, local optima): onsga2 >> nsga2, onsga2 > nsga2e
   - dtlz7 (disconnected surface): onsga2 >> nsga2, onsga2 > nsga2e
 
3. **Constrained Problem:**
   - OSY: ???
   - DTLZ8: ???

TODO's
=======

#### **Issue 1:**
* ~~fix makefile (changing header does not recompile the source)~~
* ~~implement rga~~
* ~~do euclidean dist in crowd_dist (done, slightly better in 3 obj)~~
* ~~fix the extreme point update with weak domination (just apply non-dominated sort on E)~~

#### **Issue 2:**
* ~~change rng call to make identical initial pop~~ (done)
* ~~replace rga with fmincon~~
* ~~merge 3 way plots -- onsga2, nsga2-with-extreme, nsga2-std + FE eval to find extremes~~
* ~~rewrite scripts in python, numpy and matplotlib~~
* ~~change the nsga2r/onsga2r and scripts in such a way that they can be run in parallel~~
* ~~compare with reference HV measure, to compute the reference HV use the ideal front from [ETH-Zurich](http://people.ee.ethz.ch/~sop/download/supplementary/testproblems/zdt1/index.php) site,~~ **-- this may not be necessary since the current plotting clearly distinguishes the difference in performance.**
* ~~implement another algorithm that does mutation near the extreme and internal gap points, see which one is better~~ **-- this is test is done, this is actually analogous to nsga2 with extreme point injection.**
* ~~write a report.~~
* ~~**clean up code, lots of unused functions and also needs some code optimization.**~~

Wrap up for the summer
====================

#### What we need to have:
1. ~~Test with the probabilistic selection of the extreme points and update with non-domination ranking.~~
2. ~~Test with dtlz problems 3,4 obj~~
4. Test with rotated problems from NSGA-II paper
5. ~~Use GA to find the extreme points, plug-in the GA into the current implementation.~~
6. ~~Use fmincon() instead of GA~~ (does not work well with dtlz problems)
7. ~~Show that if the extreme points are weak, still we can fill the gaps and converge faster~~ **-- yes, in many cases the classical methods can't find the true PF extreme, they are weak; but still we are doing better.**
8. Performance measure:
	* Function evaluation vs. Hypervolume:
		- ~~zdt-set~~, ~~dtlz-set~~.
	* ~~Function evaluation to reach %n of ideal HV:~~ **(not required any more)**
9. We have found an interesting observation, for easier problems like dtlz1, dtlz2 and dtlz3, the onsga2 does to perform well on small variable, but if it's increased, the performance boost becomes interestingly noticeable -- we need to show this result.

NSGA-III related (work in progress)
=============================

1. Plug this approach to NSGA-III
2. Test with many objective problems with NSGA-III 
3. Apply ASF local search to avoid infeasible/non-existing gaps
4. Do performance measurement pointed in bullet 7 above for many objective NSGA-III

#### **Conference paper:**
- bullet 1 - 7

#### **Journal paper:**
- bullet 1 - 11
