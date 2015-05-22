issues
======

### Current Algorithm:

The current algorithm works as follows --

1. use the extreme points as "target" for the first 5/6 generations
2. when generation > 5
    - sort the current population w.r.t crowding distance
    - get the 50% points with highest crowding distance, including those with infinity value
    - replace the infinity crowding distance values by the highest crowding distance values that are not infinity
    - apply roullette wheel selection to find K "target" points, where K = number of objectives
    - now use the opposition to find new points near those K selected points

the result I am getting --

1. for the osyzcka's problem, now I can address the extreme points and also can fill up the gaps
2. for zdt problems, the opposition tries to fill up the extreme points most of the time, even if they are weakly dominated, so showing a bit worse performance than the previous method that we have tested
3. it turns out that for some problems, forgetting the extreme points are good (like in zdt problems), but in some case it is not (in osyzcka's problem)


