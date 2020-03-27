CSCI 104 HW2: Basic Interpreter Programming Assignment 
Name: Nichil Stewart
Email Address: nichilst@usc.edu


This is a program for an interpreter that can: 

1) Input and scan basic text files line by line
2) Create a parse tree using interheritance class objects
3) Place the contents of each line within a chronologically ordered vector array
4) Output the formatted contents of the original input text file  


Commenting approach:

Nearly every line of interpreter.cpp features comments about parse logic, bug 
detection, and object construction. Additional comments about function use or
class members can be found below.

I favored commenting in .cpp files over .h files unless there was a significant
decision in how a class member was decefined/inherited/utilized. For similar 
class types, constructors/destructors/format() is best detailed in base case, 
while only variations/changes are explained.


Description of additional functions/utilities within this program:

interpreter/vector<Command*> command_vector:
Implemented a vector class to hold all the command objects created during the
parse function. This allows any command to be accessed chronologically, both
allowing for easier output as well as memory deallocation.

interpreter/position variable:
Used a class variable for position to be incremented throughout parsing. 

interpreter/set_position():
Created a function to search for and return the position of the last letter 
within the command name. Would set the position location one space in front 
of the last letter.

interpreter/skip_whitespace():
Created a function that would search for whitespace (' ' and '\t') as well as 
useless characters (')' and ']') and increment the position variable, thus 
skipping them. Further allows a special character to be included in the function 
argument to also be skipped.

interpreter/pseudo-exceptions:
Implemented the return of a 'nullfile' if the parser was unsuccessful. This 
guarantees the conditional parsing logic within each if statement and further 
prevents endless looping/non-void return 


The following bugs/edge cases have been tested:

Negative integers:
	-Often misinterpreted as a subtraction expression and vise-versa
	-Further found it incompatible with size_t type
	-Resolved by improving logic of when to expect a negative sign (directly 
	 preceeding integers, before/after expressions). 

Nested parentheses:
	-Additional parentheses could often be found within a single command
	-Resolved by recursively calling the parse function when the parser read '('.
	-Also taught parser to completely ignore ')' and ']' characters

Tabs:
	-Tabs mixed in with spaces made skipping either spaces or tabs unpredictable 
	-Resolved by creating a skip_whitespace() function

Linenumbers greater than INTMAX:
	-There was no guarantee that the number of linenumbers in a file would not 
	 exceed the maximum input for an integer (roughly ~2.1e^10). 
	-Resolved by streaming directly between size_t and string withou int 
	 conversions. Avoided stoi() among other int-based functions to prevent 
	 read errors.

Excess newlines at end of text file:
	-Would accidently read excess newlines with the getline() function, and would 
	 fail to read a valid LineNumber object.
	-Resolved by checking valid input before calling LineNumber construction.



Thank you for reading!
