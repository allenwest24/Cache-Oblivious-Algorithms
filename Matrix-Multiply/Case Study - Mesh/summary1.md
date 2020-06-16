# Summary

1. Write a few sentence summary of the overall problem the research is trying to solve.

Unmodified C/C++ programs are prone to fragmentation. Fragmentation is essentially discontinuous or insequential storage of data 
in memory pages by an application or program. This can happen for quite a few reasons, but the main one is that unlike languages
with automatic memory organization or garbage collectors like Python, C/C++ rely on the code written to dictate used and unused 
data. Because of this, data can be broken up, or fragmented within memory pages and cuase more time to access. Current memory 
allocators for C/C++ can perform fast, but are highly innefficient with the amount of memory they consume. 

2. Write a few sentences describing the technique used by the paper to solve the problem.

Mesh is a memory alllocator for C/C++ that uses compaction without relocation. It does this by not even changing the memory 
addresses of memory so that it can be used on any given application. Through meshing, it searches for the most compatible set of 
memory pages and meshes them together utlizing randomization in the process. Then, it essentially remaps virtual and actual 
pages of memory to fit better.

3. Do you believe the work was successful and why? (i.e. Do you believe the results, and do the results back up the research?)

Yes, I do believe this was successful. While keeping up closely comparative speeds to state of the art allocators, MESH uses way 
less memory to complete its tasks. As the goal was supposed to be to make a C/C++ allocator that better manages it memory and 
uses it more efficiently, It certainly does the job. Not only this, but prior to this project, this task was seen as largely 
impossible, so while not only achieving the task the set out to do, they proved that it was possible and practical. In  addition
to this, MESh broke the Robinson Bounds with high probability, which is a significant feat and speaks to its success.

4. How would you extend this work if you had a semester to take the project further? If there is nothing to extend, justify why.

As they stated in the paper, another good idea moving forward would be to make Mesh usable in similair languages like Go and 
Rust. From there, you could also try to further decrease the probability of fragmentation. Lastly, it would be nice to show the 
user the accuracy of each individual memory allocation so that they can become more intimately familiar with Mesh. Creating a 
feature like this to present the data and benefits could stand to be beneficial.
