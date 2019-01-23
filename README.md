# Operating_System
This contains my college OS lab Problem Solutions

Experiment No 1.  Operating System

In this experiment, you work with the fork(), wait() and the exec*() family of functions in order to find the maximum in an array of integers. 


Part 1 :
Write a C program  parmax.c  that creates a tree of processes in order to recursively compute the maximum in an array of integers. The process at the root of the tree reads the count  n  of integers in the array as a command-line parameter. An array  A  of size  n  is then populated with randomly generated integers of small values (in the range 0–127). The initially unsorted array is printed by the root process. 
Any process in the tree handles a chunk of the array  A . The chunk is delimited by two indices  L  and  R . For the root process,  L  = 0 and  R  =  n  – 1. Any process  P  in the tree (including the root) first counts the number of integers in the chunk it has got. If that count is less than 10, the process  P itself computes the maximum element in its chunk, prints it, and exits. If the chunk size of  P  is 10 or more, then  P  creates two child processes  PL  and  PR  which handle  the chunks [ L ,  M ]  and [ M  + 1,  R ] in  A  respectively , where  M  = ( L  +  R ) / 2.  P  waits until the two child processes  PL  and  PR  exit. It then computes the maximum of the two maximum values computed by  PL  and  PR , prints this maximum, and exits. 
Every non-root process returns to its parent (via the exit status) the maximum value for its chunk. During the printing of the maximum computed by a process  P , the PID and the parent PID of  P  are also printed. 
For  n  = 50, the ranges of the chunks handled by different processes in the tree are shown below.
We expect your code to handle values of n  in the range 50 – 100. Compile your code, and generate an executable file with the name parmax.


Part 2:
Write a separate C code  wrapper.c which opens an xterm with appropriate command-line parameters so as to run the executable parmax  created in Part 1. When parmax exits, your wrapper function should also exit.


--->NOTE:
//Full coding is done in ubuntu terminal
/*
  For Part 2 xterm is used ... which is 'xTerminal Emulator'
  if Not already present in your machine (To check just xterm in terminal you'll get a pop up kind of window and if such things doesnt happen it simply means you dont have it installed on your machine)
  Follow Steps:<type these in terminal>
  1) sudo apt-get update -y
  2) sudo apt-get install -y xterm
  
  NOTE:
  '-y' flag simpy means to install silently without asking questions in most cases.

*/

/*
  Commands For Part1 Code:
  (Type in terminal)
  step 1)To Compile the code and generate object file of name 'parmax' :
          gcc parmax.c -o parmax
  step 2)To run the code :
          ./parmax 50 //Any number you may pass ,AS THIS WILL CREATE AN ARRAY OF THAT SIZE AND POPULATE IT WITH RANDOM INTEGERS BETWEEN 0 to 127
  
  Commands For Part2 Code:
  (Type in terminal)
  step 1)To Compile the code and generate object file of name 'wrapper' :
          gcc wrapper.c -o wrapper
  step 2)To run the code :
          ./wrapper 50 //Any number you may pass ,AS THIS WILL CREATE AN ARRAY OF THAT SIZE AND POPULATE IT WITH RANDOM INTEGERS BETWEEN 0 to 127 
          
  NOTE :
  Dont forget to create both the files in same directory.
*/
