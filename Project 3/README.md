CSCI 104 HW3: Linked Lists, Queues, and Stacks
Name: Nichil Stewart
Email Address: nichilst@usc.edu


This homework consists of six parts:

Parts 1-3 are answers/responses to 3 sets of problems on data structure
implementation, linked list output, and run time analysis. They are all
included in a single text document.

Problem 4 is a recursive permutation function for a string input. It is written
in a single c++ file.

Problem 5 is a distance calculator for a cave problem that runs 0(n) time.
It is written in a single c++ file and includes an accompanying makefile.

Problem 6 is a program that handles merge and split requests of various 
student companies. It consists of both a c++ file and a header file.


Notes for part 1: Abstract Data Types

-I changed The Rani's subject order from {1 to n} to {0 to n-1} to be consistent
with the original subject array. The answers are nonetheless identical.

-All further justifications are written in paragraph form within the document.


Notes for part 2: Linked Lists, Recursion

-Paragraph answers, step-by-step instruction, and diagrams are used to simulate
the execution of the linked-list program.


Notes for part 3: Runtime Analysis

-Each of the answers are taken in theta (Θ) run time.

-Multiple lines in constant run time are considered together as Θ(1).

-When possible, run times are expressed first in more precise summation form.

-This includes the use of the summation character (Σ). While this might flag
the submission system, it shouldn't create issues reading the document.


Notes for part 4: Recursion

-The main permutations() function has a total of 3 helper functions:
	
	1. void permutationsHelper(): which takes in the input string, length of 
	input string, an empty "current" string, a vector to store valid combos,
	and a vector to store the locations of where each character in the 
	permutation was copied from the original string. 
	
	2. void vector_copy(): which copies the values of one vector into another.
	
	3. bool distinctCheck(): which is used to see if all the locations from
	which a permutation copied from the original string are distinct.

-The recursive function loops through all characters in the initial string and
sends a recursive call for each one. Before it makes the call, it also creates
a new vector containing all the 'i_values' or locations in the initial string
that the given permutation has copied from. 

-The recursive call then loops through every character in the first string, and
appends it to the updated string while updating its i_values vector of string
locations. It will continue to recurse until its exit condition is met.

-The exit condition of the function is when the permutation string has the same
length as the original string. As every string will increase in length after
each recursive call, the function will not recurse indefinitely. A permutation
will then be checked if it is distinct before it is entered into the 'combo'
vector array.

-Instead of checking if a permutation string is distinct (which is never true
if the input is 'CSC' for example), checking the locations of the original
string means the function can distinguish between the first and last 'C' in
'CSC'. Thus the program can evaluate any string regardless of its contents. 

-Finally, the original permutations() function outputs all the values in the
final 'combos' vector containing all valid permutations of the initial string.

-Note that strings of length greater than 7/8 can take longer completion time.


Notes for part 5: Cave Exploration

-The structure of the cave program is largely based off the structure from the
'The Rani' project in hw1. Thus I have opted to use a similar class structure
and main() function to read in inputs to a "Cave" class.

-The program utilizes an STL-stack container to store all moves that are not in
the opposite direction to the move before it. If two consecutive moves are in
opposite directions, the container will pop the previous direction and subtract
from the distance counter (thus reeling in string). Otherwise, it will simply
push back the newest move and increment the distance counter.

-The program runs in Θ(n) with each input taking a maximum constant time. It has
been testing near the proposed limit (2,000,000 lines).

-As the input limit has been set to 2,000,000 lines, the maximum size of the
distance counting variable is also 2,000,000. Thus an 'int' type has been used.

-The function both outputs the final distance to the terminal and also returns
it as the value in the main function.


Notes for part 6: Startup Companies

-All given functions have been implemted as per guidelines and tested for
correctness and memory-leaks.

-The program has an additional 4 private helper functions:
	
	1. Comapany* findParent(): which finds the highest parent company for a
	given integer corresponding to a student in the companies array.

	2. bool invalidInput() (1st implementation): checks if a single input is
	within the bounds of the companies array.
	
	3. bool invalidInput() (2nd implementation): checks if two inputs are 
	within the bounds of the companies array and if the inputs are distinct.

	4. void DeleteHelper(): helps deallocate memory by finding the parent 
	company of each entry in the parents array, copying the locations of both
	its merged companies, deleting the parent node, and then recursively passing
	in both the merged companies. It will further set all parent pointers to void
	to avoid deleting same memory location multiple times. 

-All functions run in Θ(n), though time increases as number of merges occur.


Thank you for reading!