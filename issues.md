issues
======

### Note: osy problem is set aside for later

### Schemes:
Let's denote the points as --
    - e*: hard-coded extreme found from GA
    - e: current population extreme
    - g: least crowded non-extreme points in the current population (i.e. intermediary gaps). 

Currently total of 3 schemes have been tried:

1. **Scheme1:** Converge to the e* points for some K generations and then address g's.

2. **Scheme2:** Make a pool of 3M points (M = number of obj.), pool = {e* U e U g}, and find the furthest point, and then generate opposite point near it. However, at the later generation, e* and e becomes very close/same. So a modified approach (Scheme3) is implemented.

3. **Scheme3:** Make a pool of 2M points (M = number of obj.), pool = {e* U g}, and find the furthest point, and then generate opposite point near it. This scheme is showing better results in most of the problems.

### Results (snapshots, eyeballing):

1. **ZDT set (M = 2):**
    - zdt1 opposition is faster/better
    - zdt2 opposition is faster/better
    - zdt3 opposition is faster/better
    - zdt4 opposition is faster/better
    - zdt6 opposition is faster/better

2. **DTLZ set (M = 3):**

   | dtlz1| (planar)			 | opposition is faster				    | 
   | dtlz2| (spherical)			 | opposition is not strictly faster, but comparable| 
   | dtlz3| (local optima)		 | opposition is faster				    | 
   | dtlz4| (different density)		 | opposition is not strictly faster, but comparable|
   | dtlz5| (3d curved pf, easy)	 | opposition is faster				    | 
   | dtlz6| (3d curved pf, local optima) | opposition is faster				    | 
   | dtlz7| (disconnected surface) 	 | opposition is not strictly faster, but comparable|  

