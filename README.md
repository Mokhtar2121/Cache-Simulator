Introduction about Cache:

Cache is a copy of a subset of main memory that stores the recently visited data. Cache
memory (SRAM) is used to speed up the application performance and increase its efficiency as
it is faster than main memory (DRAM), consumes less access time as compared to main
memory and It stores the program that can be executed within a short period of time. There are
three types of cache. First is direct mapped cache which has each block mapped to exactly one
cache memory location, then Fully associative cache mapping, it is similar to direct mapping in
structure but allows a memory block to be mapped to any cache location and Set associative
cache mapping which can be viewed as a compromise between both direct mapping and fully
associative mapping in which each block is mapped to a subset of cache locations.


What is done in this project:

In this project, the main objective is to be familiar with how caches work, or to be more specific
how to simulate the cache and how it performs the set-associative cache type. We used six
different functions which are a set of memory reference generators which generate random
addresses in different ranges. To start off the experiment we first had to make the fixed cache
size of 64 kb, after that we defined the address by creating the index, word offset as well as the
number of blocks. The purpose of the experiment is to see how the cache performs by changing
different characteristics of the cache itself. We had 2 different experiments assigned to us to test
the performance. The First experiment we alternated the line size using 16, 32, 64 and 128
bytes. This is where the first requirement comes into play, which is analyzing the relationship
between the varying line size and the hit rate for the fixed number of ways 4. As for the second
requirement we would also measure the hit ratio against every possible number of ways with the
line size of 16 bytes. Generally the main goal of the experiments mentioned above is to
measure the hit ratios of the cache while varying the cache parameters. The submitted zip file
contains the code that for each test case in every setup, we created a loop of 1000000 iterations
in each of which we use the given memory reference generators to create random addresses.
The results are collected in an excel file which we used to graph out results to see the relation
between varying the variables and the hit ratio. In other words, to test the cache performance.
We included screenshots of the graphs we obtained from the excel file and recorded our
observations and conclusions from each graph.
