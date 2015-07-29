TODO
=====

#### **Current Algorithm:**

##### **1. Finding the extreme points**

- Use global search, namely GA (but it takes a huge function evaluations)

- For 3 obj dtlz problems, we can only find 2 extreme points, not the 3rd one.

##### **2. Opposite Point Generation:**
Let's denote the points as --

- e*: hard-coded extreme found from GA
- e: current population extremes
- g: least crowded non-extreme points in the current population (i.e. intermediary gaps).

##### *Algorithm:*
- make a set with S = {e U e*}
- apply non-domiated sorting on S
- now partition them into two sets, S = {S1, S2}; where S1 has all the points on front 1 and crowding distance of infinity
- now if there is any point in S2 that weakly dominates any point in the S1, then discard the weakly dominated point from S1 and include the dominating point from S2.

#### **Results:**

Set of algorithms: 

- onsga2: opposition based nsga2
- nsga2e: nsga2 with extreme points injection
- nsga2: standard nsga2 with FE compensated for extreme point computation. 

1. **ZDT set (M = 2):**
    - zdt1
    - zdt2
    - zdt3
    - zdt4
    - zdt6

2. **DTLZ set (M = 3):**
   - dtlz1 (planar)
   - dtlz2 (spherical)   
   - dtlz3 (local optima)
   - dtlz4 (different density)
   - dtlz5 (3d curved pf, easy)
   - dtlz6 (3d curved pf, local optima)
   - dtlz7 (disconnected surface)


TODO's
=======

#### **Issue 1:**
* ~~fix makefile (changing header does not recompile the source)~~
* ~~implement rga~~
* ~~do euclidean dist in crowd_dist (done, slightly better in 3 obj)~~
* ~~fix the extreme point update with weak domination (just apply non-dominated sort on E)~~

#### **Issue 2:**
* ~~change rng call to make identical initial pop~~ (done)
* replace rga with fmincon
* merge 3 way plots -- onsga2, nsga2-with-extreme, nsga2-std + FE eval to find extremes
* ~~rewrite scripts in python, numpy and matplotlib~~
* change the nsga2r/onsga2r and scripts in such a way that they can be run in parallel
* compare with reference HV measure, to compute the reference HV use the ideal front from [ETH-Zurich](http://people.ee.ethz.ch/~sop/download/supplementary/testproblems/zdt1/index.php) site.
* implement another algorithm that does mutation near the extreme and internal gap points, see which one is better.
* write a report.
* **clean up code, lots of unused functions and also needs some code optimization.**

Wrap up for the summer
====================

#### What we need to have:
1. ~~Test with the probabilistic selection of the extreme points and update with non-domination ranking.~~
2. ~~Test with dtlz problems 3,4 obj~~
4. Test with rotated problems from NSGA-II paper
5. ~~Use GA to find the extreme points, plug-in the GA into the current implementation.~~
6. ~~Use fmincon() instead of GA~~ (does not work well with dtlz problems)
7. Show that if the extreme points are weak, still we can fill the gaps and converge faster
8. Performance measure:
	* Function evaluation vs. Hypervolume:
		- zdt-set, dtlz-set, rotated.
	* Function evaluation to reach %n of ideal HV:
		- zdt-set, dtlz-set, rotated.   

NSGA-III related
=============

1. Plug this approach to NSGA-III
2. Test with many objective problems with NSGA-III 
3. Apply ASF local search to avoid infeasible/non-existing gaps
4. Do performance measurement pointed in bullet 7 above for many objective NSGA-III

#### **Conference paper:**
- bullet 1 - 7

#### **Journal paper:**
- bullet 1 - 11
