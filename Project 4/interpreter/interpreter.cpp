#include "interpreter.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Interpreter::Interpreter(std::istream& in) : position(0), skip_line(false), newline(0) {
    this->parse(in);
}


Interpreter::~Interpreter() {

	for (size_t i=0; i < this->command_vector.size(); i++) {
		delete this->command_vector[i];
		//delete all command members
	}

	map<string, int*>::iterator var_it; //iterator for variable map

	for (var_it = variable_map.begin(); var_it != variable_map.end(); var_it++) {
		//delete all dynamically allocated int* values
		delete var_it->second;
	}
    
    map<string, map<int, int>*>::iterator arr_it; //iterator for array map

    for (arr_it = array_map.begin(); arr_it != array_map.end(); arr_it++) {
    	//delete all dynamically allocated map<int,int>* values
		delete arr_it->second;
	}
}


void Interpreter::parse(std::istream& in) {
    
    string line;
	while (getline(in, line)) {

        size_t read_linenumber;	
        stringstream stream(line);
        stream >> read_linenumber;
        //read linenumber value

        string command;
        stream >> command;
        //read command name

        this->position = 0; 
        //set position variable

        string linenumber_string;
		stringstream sss; sss << read_linenumber; sss >> linenumber_string;
        //read linenumber to a string

		if (linenumber_string[0] == '\n') {return;}
		//prevents memory leaks from newlines in poorly formatted files

		LineNumber* _temp_linenumber = parse_line_number(linenumber_string);
	    //create linenumber pointer


        if (command == "PRINT") {

        	this->position = set_position(line, 'T');
        	//set position after the T in PRINT

        	NumericExpression* _print_statement = parse_numeric_expression(line);
        	//parse line for numeric expression

			Command* temp_PrintCommand = new PrintCommand(_temp_linenumber, command, _print_statement);
        	//create print command with respective inputs

        	command_vector.push_back(temp_PrintCommand);
        	//push print command to vector container

        	linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }


	 	if (command == "LET") {

	 		this->position = set_position(line, 'T');
        	//set position after the T in LET

        	NumericExpression* _variable_array = parse_numeric_expression(line);
        	NumericExpression* _value = parse_numeric_expression(line);
        	//parse line for variable/array name and value

			Command* temp_LetCommand = new LetCommand(_temp_linenumber, command, _variable_array, _value);
        	//create let command with respective inputs

        	command_vector.push_back(temp_LetCommand);
        	//push let command to vector container

        	linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }

	 	if (command == "GOTO") {

	 		this->position = set_position(line, 'O');
        	//set position after the O in GOTO

        	LineNumber* _destination = parse_line_number(line);
        	//parse line for destination linenumber
			
			Command* temp_GotoCommand = new GotoCommand(_temp_linenumber, command, _destination);
			//create goto command with respective inputs

        	command_vector.push_back(temp_GotoCommand);
        	//push goto command to vector container

        	linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }

	 	if (command == "IF") {

	 		this->position = set_position(line, 'F');
        	//set position after the F in IF

	 		BooleanExpression* _expression = parse_boolean_expression(line);
	 		LineNumber* _linetarget = parse_line_number(line);
	 		//parse line for boolean expression and line number

	 		Command* temp_IfCommand = new IfCommand(_temp_linenumber, command, _expression, _linetarget);
	 		//create if command with respective inputs

        	command_vector.push_back(temp_IfCommand);
        	//push if command to vector container

        	linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }

	 	if (command == "GOSUB") {

        	this->position = set_position(line, 'B');
        	//set position after the B in GOSUB

	 		LineNumber* _linetarget = parse_line_number(line);
	 		//parse line for target linenumber

	 		Command* temp_GosubCommand = new GosubCommand(_temp_linenumber, command, _linetarget);
	 		//create gosub command with respective inputs

	 		command_vector.push_back(temp_GosubCommand);
	 		//push gosub command to vector container

	 		linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }

	 	if (command == "RETURN") {

	 		Command* temp_ReturnCommand = new ReturnCommand(_temp_linenumber, command);
	 		//create return command with respective inputs

        	command_vector.push_back(temp_ReturnCommand);
        	//push gosub command to vector container

        	linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }

	 	if (command == "END") {

	 		Command* temp_EndCommand = new EndCommand(_temp_linenumber, command);
	 		//create end command with respective puts

        	command_vector.push_back(temp_EndCommand); 
	 		//push gosub command to vector container

	 		linenumber_map[read_linenumber] = command_vector.size()-1;
        	//updates map linking all linenumbers to vector positions
        }
    }
}


size_t Interpreter::set_position(string line, char letter) {

	size_t last_pos = 0;
	//last position place

	for (size_t i = 0; i < line.size(); ++i) {
		if (letter == line[i]) 
		{
			last_pos = i;
		}
	}
	//sets position variable to position of specific character in line

	return last_pos + 2;
	//return position so it points beyond the input character
}


void Interpreter::skip_whitespace(string line, char c) {
	if (position < line.size()) {
		while (line[this->position] == ' ' || line[this->position] == '\t' ||
		       line[this->position] == ')' || line[this->position] == ']'  ||
		       line[this->position] == c) 
		{
			this->position++;
		}
	}
	//function to skip whitespace and unimportant characters
	//takes a line input and a custom character 'C' to skip
	//set to ' ' if no special character is desired
}


LineNumber* Interpreter::parse_line_number(string line) {

	skip_whitespace(line, ' ');

	if (line[this->position] == 'T' && line[this->position+1] == 'H' &&
		line[this->position+2] == 'E' && line[this->position+3] == 'N') 
	{
		this->position += 4;
		//ignore "THEN" in IF statements
	}

	skip_whitespace(line, ' ');

	string temp_line;
	while (line[this->position] >= '0' && line[this->position] <= '9') 
	{
		temp_line += line[this->position];
		this->position++;
		//copy all integers to string
	}	
	skip_whitespace(line, ' ');

	return new LineNumber(temp_line);
	//create and return linenumber
}


NumericExpression* Interpreter::parse_constant(string line) {

	string const_line = "";
	//line to copy constant value

	if (line[this->position] == '-' ) {
		const_line += line[this->position];
		this->position++;
		//only first digit can be '-' symbol
	}

	while (line[this->position] >= '0' && line[this->position] <= '9') {
		const_line += line[this->position];
		this->position++;
		//copy all integers to string
	}	

	skip_whitespace(line, ' ');

	NumericExpression* temp_const = new ConstantExpression(const_line);
	//create and return constant 
	return temp_const;
}


string Interpreter::parse_variable_name(string line) {

	string temp_name = "";
	//line to copy variable name

	while (line[this->position] >= 'A' && line[this->position] <= 'Z') {
		temp_name += line[this->position];
		this->position++;
		//copy all uppercase letters to string
	}
	skip_whitespace(line, ' ');
	//create and return variable name 
	return temp_name;
}


NumericExpression* Interpreter::parse_numeric_expression(string line) {

	skip_whitespace(line, ' ');	

	if ((line[this->position] == '-' && line[this->position+1] >= '0' &&
		 line[this->position+1] <= '9') || (line[this->position] >= '0' && 
		 line[this->position] <= '9')) {	
		//first character is a number, or a negative followed by numbers

		return parse_constant(line);
		//parse for constant
	}
	
	if (line[this->position] >= 'A' && line[this->position] <= 'Z') {

		string name = parse_variable_name(line);
		//gets variable name string

		skip_whitespace(line, ' ');

		if (line[this->position] != '[') {
			//not an array, thus a variable

			int* value_ptr; 
			//new value pointer

			if (variable_map.find(name) == variable_map.end() ) {
			//variable name is not in variable map
			  
			  	value_ptr = new int;
			  	//create new value pointer

			  	*(value_ptr) = 0; 
			  	//set default value to 0

				variable_map[name] = value_ptr;
				//insert variable name and value pointer into map
			}
			else {
			//variable name is in variable map

				value_ptr = variable_map[name];
				//copy location of value pointer
			}

			NumericExpression* temp_Var = new VariableExpression(name, value_ptr);
			return temp_Var;
			//creates and returns variable expression
		}

		if (line[this->position] == '[') {
			//an array

			this->position++;

			skip_whitespace(line, ' ');

			map<int,int>* value_array_ptr;
			//create a new map pointer to store all values of an array variable
			//note: I'm using a map as a pseudo-array

			if (array_map.find(name) == array_map.end()) {
			//array name is not in array map
			  
			  	value_array_ptr = new map<int,int>;
			  	//create new value pointer

				array_map[name] = value_array_ptr;
				//insert variable name and value pointer into map
			}
			else {
			//variable name is in variable map

				value_array_ptr = array_map[name];
				//copy location of value pointer
			}

			NumericExpression* index = parse_numeric_expression(line);
			NumericExpression* temp_Arr = new ArrayExpression(name, index, value_array_ptr);
			return temp_Arr;
			//creates and returns array expression
		}
	}

	if (line[this->position] == '(') {
		//if arithmetic expression

		this->position++; 	
		skip_whitespace(line, ' ');

		NumericExpression *left = parse_numeric_expression(line);
		//create left expression

 		if(line[this->position] == '+') {

 			this->position++;
			NumericExpression *right = parse_numeric_expression(line); 
			//create right expression

			NumericExpression* temp_Add = new AdditionExpression(left, right);
			return temp_Add;
			//create and return arithmetic expression
		}

 		if(line[this->position] == '-') {

 			this->position++;
			NumericExpression *right = parse_numeric_expression(line); 
			//create right expression
			
			NumericExpression* temp_Subtract = new SubtractionExpression(left, right);
			return temp_Subtract;
			//create and return arithmetic expression
		}

 		if(line[this->position] == '*') {

 			this->position++;
			NumericExpression *right = parse_numeric_expression(line); 
			//create right expression

			NumericExpression* temp_Multiply = new MultiplicationExpression(left, right);
			return temp_Multiply;
			//create and return arithmetic expression
		}

 		if(line[this->position] == '/') {

 			this->position++;
			NumericExpression *right = parse_numeric_expression(line); 
			//create right expression
			
			NumericExpression* temp_Divide = new DivisionExpression(left, right);
			return temp_Divide;
			//create and return arithmetic expression
		}
	}

	//else
		//cerr << "did not find NumericExpression" << endl;
		NumericExpression* null_expression = new ConstantExpression("-1");
		return null_expression;
		//psuedo-exception to always return argument
		//should never be used for valid files 
}


BooleanExpression* Interpreter::parse_boolean_expression(string line) {

	char operator_type;
	for(size_t i=this->position; i < line.size(); i++) {
		if(line[i] == '=') {operator_type = '=';}
		if(line[i] == '>') {operator_type = '>';}
		if(line[i] == '<') {operator_type = '<';}
		//read what kind of boolean expression
	}
 
	if(operator_type == '=') {

		NumericExpression *left = parse_numeric_expression(line); 
		//set left expression
		
		skip_whitespace(line, '=');
		//ignore the '=' char

		NumericExpression *right = parse_numeric_expression(line); 
		//set right expression
		
		BooleanExpression* temp_Equal = new EqualityExpression(left, right);
		return temp_Equal;
		//create and return equals expression
	}

	if(operator_type == '>') {

		NumericExpression *left = parse_numeric_expression(line); 
		//set left expression
		
		skip_whitespace(line, '>');
		//ignore the '>' char

		NumericExpression *right = parse_numeric_expression(line); 
		//set right expression
		
		BooleanExpression* temp_Greater = new GreaterExpression(left, right);
		return temp_Greater;
		//create and return greater expression
	}

	if(operator_type == '<') {

		NumericExpression *left = parse_numeric_expression(line); 
		//set left expression
		
		skip_whitespace(line, '<');
		//ignore the '<' char

		NumericExpression *right = parse_numeric_expression(line); 
		//set right expression
		
		BooleanExpression* temp_Lesser = new LesserExpression(left, right);
		return temp_Lesser;
		//create and return lesser expression
	}

	//else 
		//cerr << "did not find BooleanExpression" << endl;
		ConstantExpression* x = new ConstantExpression("-1");
		ConstantExpression* y = new ConstantExpression("-1");
		BooleanExpression* null_expression= new EqualityExpression(x,y);
		return null_expression;
		//psuedo-exception to always return argument
		//should never be used for valid files
}


void Interpreter::write(std::ostream& out) {

	for (size_t i=0; i < command_vector.size(); i++) {

		out << command_vector[i]->format() << endl; 
		//outputs string format of vector contents to out
	}
}


void Interpreter::main(std::ostream& out) {

	try {
        	this->execute(out);
        } catch(exception& e) {

			out << "Error in line " << current_line << ": " << e.what() << endl;
            //Sends error report to output file
            //current_line is class variable tracking the current line in execute()
        }
        return;
}


void Interpreter::execute(std::ostream& out) {

	size_t i = 0; //increment variable

	while (i < command_vector.size() || skip_line == true) {

		if (skip_line == true) {
			//previous GOTO, IF, GOSUB, RETURN command

			skip_line = false;
			//turn off skipline warning

			if (newline >= command_vector.size()) {
				//target line is out of range
				return;
				//no more lines, so program terminates
			}
			else {
				i = newline;
				//set increment value to target array position
			}
		} 

		current_line = command_vector[i]->getLinenumber();
		//get current line incase of error messages
		string command = command_vector[i]->getCommandType();
		//get command type as a string
		Command* command_object = command_vector[i];
		//stores command in non-vector/array pointer 

		if (command == "PRINT") {

			int print_output = ((PrintCommand*)command_object)->getInt(); 
			//specifies command-type for class-specific function use

			out << print_output << endl; 
			//prints that int value
		}

		else if (command == "LET") {

			string name = ((LetCommand*)command_object)->getName();
			//get the variable name

			if (((LetCommand*)command_object)->isArray()) { //is an array variable
				
				int new_value = ((LetCommand*)command_object)->getTarget();
				//find target value
				int index_position = ((LetCommand*)command_object)->getIndex();
				//find index position
				map<int,int> * map_reference = array_map[name];
				//create pointer to access submap of array positions and values
				(*map_reference)[index_position] = new_value;
				//set value for variable name to target value
			}
			else { //is a regular variable

				int new_value = ((LetCommand*)command_object)->getTarget();
				//find target value
				int* value_pointer = variable_map[name];
				//get int* pointer 
				*value_pointer = new_value;
				//set value for pointer
			}
		}

		else if (command == "GOTO") {

			size_t goto_line = ((GotoCommand*)command_object)->getDestination();
			//gets the line destination

			if (linenumber_map.find(goto_line) == linenumber_map.end()) { 

				string error = "GOTO to non-existent line <" + to_string(goto_line) + ">.";
				//create error string

				throw out_of_range(error); return;
				//Cannot find specified linenumber in map
			}
			else {
				size_t new_index = linenumber_map[goto_line]; 
				//get map value of new line
				skip_line = true; 
				//lets program know to skip lines
				newline = new_index; 
				//sets value of line to skip to
			}
		}

		else if (command == "IF") {

			bool is_true = ((IfCommand*)command_object)->getBool();
			size_t if_line = ((IfCommand*)command_object)->getDestination();
			//check if statement is true and get value of target line

			if (is_true) {

				if (linenumber_map.find(if_line) == linenumber_map.end()) { 
					
					string error = "IF jump to non-existent line <" + to_string(if_line) + ">.";
					//create error string

					throw out_of_range(error); return;
					//Cannot find specified linenumber in map
				}
				else {
					size_t new_index = linenumber_map[if_line]; 
					//get map value of new line
					skip_line = true; 
					//lets program know to skip lines
					newline = new_index; 
					//sets value of line to skip to
				}
			} 
			//else do nothing
		}

		else if (command == "GOSUB") {

			size_t gosub_line = ((GosubCommand*)command_object)->getDestination();
			//gets the line destination

			if (linenumber_map.find(gosub_line) == linenumber_map.end()) { 

				string error = "GOSUB to non-existent line <" + to_string(gosub_line) + ">.";
				//create error string

				throw out_of_range(error); return;
				//Cannot find specified linenumber in map
			}
			else {
				size_t new_index = linenumber_map[gosub_line]; 
				//get map value of new line
				skip_line = true; 
				//lets program know to skip lines
				newline = new_index; 
				//sets value of line to skip to
				gosub_stack.push(i+1); 
				//adds next line to gosub stack
			}
		}

		else if (command == "RETURN") {

			if (gosub_stack.empty()) {

				throw out_of_range("No matching GOSUB for RETURN."); return;
				//Cannot find a linenumber in the GOSUB stack
			}
			else {
				newline = gosub_stack.top(); 
				//get most recent gosub line
				gosub_stack.pop(); 
				//pop that gosub line
				skip_line = true; 
				//let program know it will be skipping a line
			}
		}

		else if (command == "END") {
			//can return, 
			return;
		}

		else {
			return;
			//There was an error reading comment. Check text formatting.
		}

		i++;
		//incrementing variable
	}
}