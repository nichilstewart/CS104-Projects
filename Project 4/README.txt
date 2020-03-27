CSCI 104 HW4: Basic Interpreter Programming Assignment 
Name: Nichil Stewart
Email Address: nichilst@usc.edu


This is a program for an interpreter that can: 

1) Parse and interpret basic text files line by line
2) Create a parse tree using interheritance class objects
3) Place the contents of each line within a chronologically ordered vector array
4) Output the formatted contents of the original input text file
5) Run a basic program by emulating a series of basic commands
6) Output the results of a basic program 
7) Use a catch-throw exception system to handle all errors and terminate


Commenting approach:

I favored commenting changes relevant to HW4, while keeping HW2 comments as
they were. All files contain extensive explanations and observations about the
program and its functionality. 

Further description of specific functions and variables below.


Description of additional functions/utilities within this program:

interpreter/vector<Command*> command_vector:
Implemented a vector class to hold all the command objects created during the
parse function. This allows any command to be accessed chronologically, both
allowing for easier output as well as memory deallocation.

interpreter/map<string, int*> variable_map: 
Implemented a map to store all the integer variable names (as keys) that map to
int* pointers of each variable's value (as values). Thus all variables with the
same name will have access to the same value pointer and will be updated 
simulataneously. 

interpreter/map<string, map<int, int>*> array_map:
Implemented a map to store all the array variable names (as keys) that map to
map* pointers (as values). These map pointers link array indicies to array
index values, so all array variables of the same name will have their map
values updated simultaneously. I am essentially using the map as a pseudo-array
that has both negative and positive indicies.

interpreter/bool skip_line and int newline variables: 
Used two interpreter-class variables to handle line skip requests throughout
the interpret command functions. 

interpreter/map<size_t, size_t> linenumber_map: 
Implemented a map that stores all command linenumbers as keys mapped to that
command's position in a vector array of all commands. 

interpreter/stack<size_t> gosub_stack: 
Implemented a stack to store all GOSUB linenumbers so they can be accessed in
order of recency by a RETURN command.

all/getValue() functions:
Implemented a recursive, virtual getValue() function that can evaluate any 
numerical or boolean expression by recursively traversing a parse tree in
multiple contexts.


Thank you for reading!
