issues
======

#### Current Algorithm:

The current algorithm works as follows --

1. use the extreme points as "target" for the first 5/6 generations
2. when generation > 5
    - sort the current population w.r.t crowding distance
    - get the 50% points with highest crowding distance, including those with infinity value
    - replace the infinity crowding distance values by the highest crowding distance values that are not infinity, so that the extreme points and the highest gapped points will have same priority.
    - apply roullette wheel selection to find K "target" points, where K = number of objectives
    - now use the opposition to find new points near those K selected points

#### Result:

1. for the osyzcka's problem, now I can address the extreme points and also can fill up the gaps
2. for zdt problems, the opposition tries to fill up the extreme points most of the time, even if they are weakly dominated, so showing a bit worse performance than the previous method that we have tested
3. it turns out that for some problems, forgetting the extreme points are good (like in zdt problems), but in some case it is not (in osyzcka's problem)

#### Solution Summary:

1. We are fixing the number of "target" points to be equal to the number of objectives, K
2. This is ok for initial generations, since initially we are concerned with the convergence, and by fixing it, we are getting better convergence.
3. but in the later generations, those extreme points are less important since gaps starting to emerge
4. to fill the gap, we ignored the extreme points and we have seen that the algorithms can selectively fill the gaps for zdt problems
5. but for osyzcka's problem, concentrating on the gaps was not enough, because we also need to address the extreme points
6. the new algorithm is trying to make balance between the priorities for the extreme and the largest gap
7. but if the extremes are weakly pareto dominant, the opposition computation getting wasted

#### What we need to do:

1. setting the number of target points to exactly K (number of obj.) over whole generation is not right
2. the number of target points should be = the number of gaps x 2, since each gap has two edge points
3. gaps are not evident until the points come close to the pf, so counting the number of gaps is not a practical idea
4. so what we need to do is to take instead of K target points, we will chose 2K target points, along with the extremes
5. and for each source point, we will randomly pick 2 from the 2K points and apply the opposition
6. I am currently working on this now
7. An extra line.
