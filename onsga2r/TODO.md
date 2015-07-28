TODO
====

#### Issue 1:
* ~~fix makefile (changing header does not recompile the source)~~ (done)
* ~~implement rga~~ (done, but taking huge FE to find extremes, hence not considered any more)
* ~~do euclidean dist in crowd_dist (done, slightly better in 3 obj)~~ (not much improvement)
* ~~fix the extreme point update with weak domination (just apply non-dominated sort on E)~~ (done, see scheme 5)

#### Issue 2:
* ~~change rng call to make identical initial pop~~
* replace rga with fmincon
* merge 3 way plots -- onsga2, nsga2-with-extreme, nsga2-std + FE eval to find extremes
* ~~rewrite scripts in python, numpy and matplotlib~~
* change the nsga2r/onsga2r and scripts in such a way that they can be run in parallel
* clean up code, lots of unused functions and also needs some code optimization.
* compare with reference HV measure, to compute the reference HV use the ideal front from ETHZurich's site.

#### Old Issues:

**Note: osy problem is set aside for later**

##### Schemes:
Let's denote the points as --

    - e*: hard-coded extreme found from GA
    - e: current population extreme
    - g: least crowded non-extreme points in the current population (i.e. intermediary gaps). 

Currently total of 3 schemes have been tried:

1. **Scheme1:** Converge to the e* points for some K generations and then address g's.

2. **Scheme2:** Make a pool of 3M points (M = number of obj.), pool = {e* U e U g}. Randomly select M points, find the furthest point in M, and then generate opposite point near it. However, at the later generation, e* and e becomes very close/same. So a modified approach (Scheme3) is implemented.

3. **Scheme3:** Make a pool of 2M points (M = number of obj.), pool = {e* U g}. Randomly select M points, find the furthest point in M, and then generate opposite point near it. This scheme is showing better results in most of the problems.

**Note:** What if the points e* are not on the true PF? In that case, Scheme2 should be better. But this is not tested yet. Therefore, a better way could be like Scheme4 --

**Scheme4:** Compute hypervolume hv_e* from M points in e* and compute hypervolume hv_e from M points in e. If (hv_e* > hv_e) then include e* in the pool (i.e. pool = {e* U g}), otherwise include e in the pool (i.e. pool = {e U g}). Now randomly select M points from the pool and find the furthest one. Now generate opposite point near it. Computing hypervolume will be expensive for many objectives, so what we have done is, instead of computing hypervolume, we computed the volume of the n-simplex built from n+1 points ({e, w} or {e*, w}, where w is the nadir objective vector from the current population) to compare the points in e and e*. This approach makes the algorithm more streamlined and paramterless. The results are similar as before. But the algorithm will work even if the initial ga-run can't find the true PF extreme points. 

##### Results (snapshots, eyeballing):

1. **ZDT set (M = 2):**
    - zdt1 opposition is faster/better
    - zdt2 opposition is faster/better
    - zdt3 opposition is faster/better
    - zdt4 opposition is faster/better
    - zdt6 opposition is faster/better

2. **DTLZ set (M = 3):**
   - dtlz1 (planar)			opposition is faster				     
   - dtlz2 (spherical)			opposition is not strictly faster, but comparable
   - dtlz3 (local optima)		opposition is faster				     
   - dtlz4 (different density)		opposition is not strictly faster, but comparable
   - dtlz5 (3d curved pf, easy)		opposition is faster				     
   - dtlz6 (3d curved pf, local optima)	opposition is faster				     
   - dtlz7 (disconnected surface)	opposition is not strictly faster, but comparable 

Wrap up for the summer
======================

#### What we have so far:
1. zdt1, zdt2, zdt3, zdt4, zdt6, osy, pol results 

#### What we need to have:
1. Test with the probabilistic ranking of the extreme points for 2-obj constrained problems
2. Test with dtlz problems 3,4 obj
4. Test with rotated problems from NSGA-II paper
5. Use GA to find the extreme points, plug-in the GA into the current implementation
6. Show that if the extreme points are weak, still we can fill the gaps and converge faster
7. Performance measure:
  * Function evaluation vs. Hypervolume
      - zdt1, zdt2, zdt3, zdt4, zdt6, dtlz, rotated, wfg
  * Function evaluation vs. Spread
      - zdt1, zdt2, zdt3, zdt4, zdt6, dtlz, rotated, wfg

#### NSGA-III related:

8. Plug this approach to NSGA-III
9. Test with many objective problems with NSGA-III 
10. Apply ASF local search to avoid infeasible/non-existing gaps
11. Do performance measurement pointed in bullet 7 above for many objective NSGA-III

#### Conference paper: 
    bullet 1 - 7
#### Journal paper: 
    bullet 1 - 11

