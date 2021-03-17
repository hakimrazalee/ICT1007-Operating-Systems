# Task: To implement the following CPU Scheduling algorithm

The K-factor CPU Scheduling Algorithm is an improved SJF (Shortest Job First) algorithm that tackles the issues of process starvation, infinite postponement of longer processes and unfair process selection. The K-factor algorithm minimises said issues by giving bigger processes a chance of executing before smaller processes while having similar average waiting times and turnaround times as SJF. This allocation is done by comparing the life cycle times the K-factor (either K=2 or K increases alternatively) of smaller processes to the life cycle of adjacent bigger processes and the total work done by the CPU. The option of increasing K continuously was not included in the algorithm as doing so will stray the value of average turnaround time and waiting time from the original SJF algorithm. The Pseudocode is as shown in the figure below:


Step 1: Initialization

a. Variable K=2

b. For i = 0 to n
	i. P[i] = Random Number Generator(1,100),
	Where p[i] is the burst time of process i in
	ready queue,
	ii. A[i]=0, where A[i] is the arrival time of
	process i

Step 2: Align the processes in the ascending order of their
burst time in the ready queue.

Step 3: Allocate the CPU to the first process in the ready
queue, P[1] for the time duration of its burst time.

Step 4: Remove the process from the ready queue which has
been allocated the CPU.

Step 5: Select the first two processes in the ready queue, P [1]
and P [2] (where P [1] < P [2]). Now let us assume that CPU
has worked for some time say t, represented in the Gantt chart
then

	a. If, (K* P [1]) > (t + P [2])
Process P [2] gets the CPU
	else
Process P [1] gets the CPU
	
	b. Increase the value of K alternatively.
Step 6: Go to step 4 if there are processes in ready queue else
exit.


# Additional Test Cases

Several additional test cases were also added. These cases include being able to specify manual burst and arrival times, specifying manual process size with random burst times and arrival times being 0 (dynamic allocation of memory or capped at 10 000), input sanitization (with error handling) and process idle time scenarios. The implemented code also allows users to select the algorithm and a test case they desire with an in-console menu. Algorithms can be selected one after the other by placing the program in a while loop. An example test case would be using the manually inputted values shown in the table below and achieving the correct output.
The implemented code limits the number of processes to 10 000 to prevent any accuracy errors due to hardware limitations. An alternative algorithm that allows dynamic allocation of memory is also available in the event that the user’s hardware is able to support it.
