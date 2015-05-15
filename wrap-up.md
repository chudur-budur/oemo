Wrap up for the summer
----------------------

#### What we have so far:
1. zdt1, zdt2, zdt3, zdt4, osy, pol results 

#### What we need to have:
1. Test with the probabilistic ranking of the extreme points for 2-obj constrained problems
2. Test with dtlz problems 3,4 obj
3. Test with WFG problems
4. Test with rotated problems from NSGA-II paper
5. Use GA to find the extreme points, plug-in the GA into the current implementation
6. Show that if the extreme points are weak, still we can fill the gaps and converge faster
7. Performance measure:
  * Function evaluation vs. Hypervolume
  * Function evaluation vs. Spread
  * Come up with a measure for counting gaps --
      - sort the points in one obj direction
      - find all the extreme points (points with highest crowding dist)
      - count the gaps
      - address how the new algorithm reduces the number of gaps over generation and the NSGA-III can't
8. Plug this approach to NSGA-III
9. Test with many objective problems with NSGA-III 
10. Apply ASF local search to avoid infeasible/non-existing gaps
11. Do performance measurement pointed in bullet 7 above for many objective NSGA-III

#### Conference paper: 
    bullet 1 - 7
#### Journal paper: 
    bullet 1 - 11
