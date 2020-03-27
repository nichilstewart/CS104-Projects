#include "interpreter.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Interpreter::Interpreter(std::istream& in) : position(0) {
    this->parse(in);
}

Interpreter::~Interpreter() {
	for (size_t i=0; i < this->command_vector.size(); i++) {
		delete this->command_vector[i];
		//delete all command members
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

        	Command* temp_PrintCommand = new PrintCommand(_temp_linenumber, _print_statement);
        	//create print command with respective inputs

        	command_vector.push_back(temp_PrintCommand);
        	//push print command to vector container
        }


	 	if (command == "LET") {

	 		this->position = set_position(line, 'T');
        	//set position after the T in LET

        	NumericExpression* _variable_array = parse_numeric_expression(line);
        	NumericExpression* _value = parse_numeric_expression(line);
        	//parse line for variable/array name and value

			Command* temp_LetCommand = new LetCommand(_temp_linenumber, _variable_array, _value);
        	//create let command with respective inputs

        	command_vector.push_back(temp_LetCommand);
        	//push let command to vector container
        }

	 	if (command == "GOTO") {

	 		this->position = set_position(line, 'O');
        	//set position after the O in GOTO

        	LineNumber* _destination = parse_line_number(line);
        	//parse line for destination linenumber
			
			Command* temp_GotoCommand = new GotoCommand(_temp_linenumber, _destination);
			//create goto command with respective inputs

        	command_vector.push_back(temp_GotoCommand);
        	//push goto command to vector container
        }

	 	if (command == "IF") {

	 		this->position = set_position(line, 'F');
        	//set position after the F in IF

	 		BooleanExpression* _expression = parse_boolean_expression(line);
	 		LineNumber* _linetarget = parse_line_number(line);
	 		//parse line for boolean expression and line number

	 		Command* temp_IfCommand = new IfCommand(_temp_linenumber, _expression, _linetarget);
	 		//create if command with respective inputs

        	command_vector.push_back(temp_IfCommand);
        	//push if command to vector container
        }

	 	if (command == "GOSUB") {

        	this->position = set_position(line, 'B');
        	//set position after the B in GOSUB

	 		LineNumber* _linetarget = parse_line_number(line);
	 		//parse line for target linenumber

	 		Command* temp_GosubCommand = new GosubCommand(_temp_linenumber, _linetarget);
	 		//create gosub command with respective inputs

	 		command_vector.push_back(temp_GosubCommand);
	 		//push gosub command to vector container
        }

	 	if (command == "RETURN") {

	 		Command* temp_ReturnCommand = new ReturnCommand(_temp_linenumber);
	 		//create return command with respective inputs

        	command_vector.push_back(temp_ReturnCommand);
        	//push gosub command to vector container
        }

	 	if (command == "END") {

	 		Command* temp_EndCommand = new EndCommand(_temp_linenumber);
	 		//create end command with respective puts

        	command_vector.push_back(temp_EndCommand); 
	 		//push gosub command to vector container
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
			//not an array

			NumericExpression* temp_Var = new VariableExpression(name);
			return temp_Var;
			//creates and returns variable expression
		}

		if (line[this->position] == '[') {
			//an array

			this->position++;

			skip_whitespace(line, ' ');

			NumericExpression* index = parse_numeric_expression(line);
			NumericExpression* temp_Arr = new ArrayExpression(name, index);
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
