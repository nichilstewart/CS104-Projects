#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <vector>
#include <string>
#include "command.h"

class Interpreter {

public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);

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
};

#endif