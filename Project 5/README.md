CSCI 104 HW5: Heaps

Name: Nichil Stewart

Email Address: nichilst@usc.edu


This homework consists of 4 parts:

### Part 1: Heaps Response

This is a response describing a series of operations performed on a string
within a binary minheap graph.

Answers are given in both text answers and diagrams in word file "hw5.txt".


### Part 2: Learning Program

This is a program that using backtracking to evaluate the greatest amount of
learning that is possible from a given class list and maximum workload.

Given an formatted text file of classes containing both the amount of work
possible, the amount of work per class, and the amount of learning per class,
this program uses recursive backtracking to the find the combination of classes
with the highest cumilative learning possible.

The recursive function works by considering all binary permutations of classes,
corresponding to all situations in which each class is either taken or not
taken. It does this by using the max() function to find whether taking or not
taking each class will produce a higher possible total learning, and then
returning the greatest combination of all possibilities.

Program is contained in file "learning.cpp".


### Part 3: Templated MinHeap Implementation

This is an implementation of a minheap that can store any type of variable
through template formatting. It can accomodate any numerical base greater than
two.

Here are brief responses to questions listed on the written prompt:

###### If you put a complete d-ary tree in an array, what is the index of the parent of the node at position i?

You can find the parent of any node at position 'i' in a 0-indexed heap by
calculating i-1 and dividing by the base value. 

Thus the parent is found at (i-1)/(base).

###### In the same scenario as above, what are the indices of the children of the node at position i?

You can find the children of any node at position 'i' in a 0-indexed heap by
calculating i multiplied by the base, and then by adding n+1 which is the 'n'th
child of that parent (starting at 0). 

Thus the child is found at (i)(base)+(n+1).

###### What changes in the heap functions you learned in class when you move to d-ary arrays?

Both the trickleDown() and bubbleUp() functions have to make more comparisons
than before as they havemore children to compare against.

Also note that I have implemented exceptions in my file, and a main function
would need to catch those exceptions to work as intended.

Implementation is contained in file "heap.h".


### Part 4: Doublet 

This is a program that uses the previous minheap implementation to evaluate
the minimum number of steps to transform one word into another via "doublets."
This is done by changing one letter of the word at a time, transforming the
word into another existing word until you arrive at the target word.

I implemented this solution both using functions within my minheap definition
as well as using A* heuristic-based search to find the best possible next word
to choose from.

HEURISTIC: f = g + h , where g is the number of steps taken, h is the heuristic.

RULES FOLLOWED: 

1. Always make the move with smallest f-value, where f = number of steps taken
added to the the heuristic value.

2. If multiple words have the smallest f-value, choose the one with the smallest
h-value (or, equivalently, the largest g-value).

3. If multiple words have the smallest f and h-value, choose the smaller string
according to operator<(str1, str2), where str1 and str2 are fully-capitalized
versions of the original strings.

PRIORITY: f(n+1)+h, where n is the length of the word being transformed. This 
ensured that the smallest f-value was chosen when breaking ties by h-values.

Note the strings are NOT case sensitive. This has been solved by making a 
toUpper() function that transforms all lower-case letters into upper-case
by changing ASCII character values.

As tested the program should be able to handle any combination of strings
without segfaulting, though you may surprise me.

Program is contained in file "doublet.cpp", and uses header file "heap.h".


Thank you for reading!