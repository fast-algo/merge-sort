# merge-sort
This is my merge-sort algorithm in C. On my machine it's actually turning out to be 2X faster than the mergesort included in the C standard library. On another machine it's about 50% faster so I guess it depends on hardware components and memory bus speeds etc.

It's still O(nlog(n)) but pre-allocation of memory outside of the main execution loop makes it much faster than the standard library version.

I tried a few versions where I replaced while() loops for copying data with a single memcpy() call. I would have assumed a single memcpy() call would be faster than a while() loop. Memcpy is faster when you compile with no optimisations. However, when you compile with optimisations, a single memcpy() call turns out to be slower on average than the while() loop implementation. Surprising.

All benchmarks are on:
* 2-core 3GHz i7 Mac Laptop
* 16 GB RAM
* N = 11,000,000 randomly generated integers
* All figures are the average of 10 runs.

The performance boost is measured relative to the C stdlib mergesort implementation.

| Approach | Total Time | Performance Boost |
| :------- | :------:  | :---------------: |
| StdLib    | 2.00 sec | 1X               |
| Fast-Algo  | 0.951 sec   | 2X           |

Both stdlib and this version use the typical divide & conquer mergesort algorithm but pre-allocating memory gives a huge boost over the stdlib version. 


