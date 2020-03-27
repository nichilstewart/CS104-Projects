#include "command.h"
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>

using namespace std;


LineNumber::LineNumber(string temp_linenumber) {
	stringstream ss; ss << temp_linenumber; ss >> this->line_number;
	//converts string to size_t without integer loss
}

LineNumber::~LineNumber() {
}

string LineNumber::format() const {
	return to_string(line_number);
	//converts size_t to string without intger-size loss
}


PrintCommand::PrintCommand(LineNumber* command_linenumber, NumericExpression* print_expression) {
	this->command_linenumber = command_linenumber;
	this->print_expression = print_expression;
	//read in expressions
}

PrintCommand::~PrintCommand() {
	delete this->print_expression;
	delete this->command_linenumber;
	//clear pointer memory
}

string PrintCommand::format() const {
	return this->command_linenumber->format() + " PRINT " + this->print_expression->format();
	//format as string
}


LetCommand::LetCommand(LineNumber* command_linenumber, NumericExpression* target_variable, NumericExpression* target_value) {
	this->command_linenumber = command_linenumber;
	this->target_variable = target_variable;
	this->target_value = target_value;
} 

LetCommand::~LetCommand() {
	delete this->target_variable;
	delete this->target_value;
	delete this->command_linenumber;
}

string LetCommand::format() const {
	
	return this->command_linenumber->format() + " LET " + this->target_variable->format() + " " + this->target_value->format();
}  				


GotoCommand::GotoCommand(LineNumber* command_linenumber, LineNumber* line_destination) {
	this->command_linenumber = command_linenumber;
	this->line_destination = line_destination;
}

GotoCommand::~GotoCommand() {
	delete this->line_destination;
	delete this->command_linenumber;
}

string GotoCommand::format() const {
	return this->command_linenumber->format() + " GOTO <" + this->line_destination->format() + '>';
}


IfCommand::IfCommand(LineNumber* command_linenumber, BooleanExpression* boolean_condition, LineNumber* line_destination) {
	this->command_linenumber = command_linenumber;
	this->boolean_condition = boolean_condition;
	this->line_destination = line_destination;
}

IfCommand::~IfCommand() {
	delete this->boolean_condition;
	delete this->line_destination;
	delete this->command_linenumber;
}

string IfCommand::format() const {
	return this->command_linenumber->format() + " IF [" + this->boolean_condition->format() + "] THEN <" + this->line_destination->format() + '>';
}


GosubCommand::GosubCommand(LineNumber* command_linenumber, LineNumber* jump_line) {
	this->command_linenumber = command_linenumber;
	this->jump_line = jump_line;
}

GosubCommand::~GosubCommand() {
	delete this->jump_line;
	delete this->command_linenumber;
}

string GosubCommand::format() const {
	return this->command_linenumber->format() + " GOSUB <" + this->jump_line->format() + '>';
}


ReturnCommand::ReturnCommand(LineNumber* command_linenumber) {
	this->command_linenumber = command_linenumber;
}

ReturnCommand::~ReturnCommand() {
	delete this->command_linenumber;
}

string ReturnCommand::format() const {
	return this->command_linenumber->format() + " RETURN";
}


EndCommand::EndCommand(LineNumber* command_linenumber) {
	this->command_linenumber = command_linenumber;
}

EndCommand::~EndCommand() {
	delete this->command_linenumber;
}

string EndCommand::format() const {
	return this->command_linenumber->format() + " END";
}
