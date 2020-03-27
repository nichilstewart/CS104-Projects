#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include "command.h"

class Interpreter {

public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out); 
    //prints all lines

    void main(std::ostream& out); 
    //catches errors and runs execute()

    void execute(std::ostream& out); 
    //executes all lines of code

private:
    void parse(std::istream& in);

	LineNumber* parse_line_number(std::string line);
	NumericExpression* parse_constant(std::string line);
	std::string parse_variable_name(std::string line);
	NumericExpression* parse_numeric_expression(std::string line);
	BooleanExpression* parse_boolean_expression(std::string line);
    //all parse functions

    std::vector<Command*> command_vector;
    //a vector array to store commands in order

    size_t position;
    //class-scope position variable

    size_t set_position(std::string line, char letter);
    void skip_whitespace(std::string line, char c);
    //helper functions to set position and remove whitespace

    size_t current_line; 
    //size_t for current line in case of error message

    std::map<std::string, int*> variable_map;
    //Maps of all variable names to their value

    std::map<std::string, std::map<int, int>*> array_map; 
    //Map within a map: Maps all array variable names to their own map of values that act as pseudo-arrays

    std::map<size_t, size_t> linenumber_map;
    //Map linking line numbers to position in command vector array

    bool skip_line; //previous GOTO, IF, GOSUB, RETURN command, will skip line
    size_t newline; //value in array to skip to

    std::stack<size_t> gosub_stack; 
    //Stack of all "saved" linenumbers
};

#endif