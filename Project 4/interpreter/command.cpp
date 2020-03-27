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

size_t LineNumber::getLinenumber() const {
	return this->line_number;
}


PrintCommand::PrintCommand(LineNumber* command_linenumber, string command_type, NumericExpression* print_expression) {
	this->command_linenumber = command_linenumber;
	this->print_expression = print_expression; //read in expressions
	this->command_type = command_type; //initialize string of command type
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

string PrintCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t PrintCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}

int PrintCommand::getInt() const {
	return print_expression->getValue();
}


LetCommand::LetCommand(LineNumber* command_linenumber, string command_type, NumericExpression* target_variable, NumericExpression* target_value) {
	this->command_linenumber = command_linenumber;
	this->target_variable = target_variable;
	this->target_value = target_value;
	this->command_type = command_type; //initialize string of command type
} 

LetCommand::~LetCommand() {
	delete this->target_variable;
	delete this->target_value;
	delete this->command_linenumber;
}

string LetCommand::format() const {	
	return this->command_linenumber->format() + " LET " + this->target_variable->format() + " " + this->target_value->format();
	//format as string
}

string LetCommand::getCommandType() const {
	return this->command_type; //return command type string
}  				

size_t LetCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}

bool LetCommand::isArray() const {
	return this->target_variable->isArray();
	//check if expression is an array
}

string LetCommand::getName() const {

	if (this->target_variable->isArray()) {
		string name = this->target_variable->format();
		//get fully-formatted array name

		size_t nameEnding = name.find('[');
		//find firsr occurance of '['

		string finalName = name.substr (0,nameEnding);
		//take substring before index chars begin
		
		return finalName;
		//return "fixed" array name
	}
	else {
		return this->target_variable->format(); 
		//not an array, can call format() for name string
	}
}

int LetCommand::getTarget() const {
	return this->target_value->getValue();
	//returns value of target expression
}

int LetCommand::getIndex() const {

	return ((ArrayExpression*)target_variable)->getIndex();
	//returns value of array index
}


GotoCommand::GotoCommand(LineNumber* command_linenumber, string command_type, LineNumber* line_destination) {
	this->command_linenumber = command_linenumber;
	this->line_destination = line_destination;
	this->command_type = command_type; //initialize string of command type
}

GotoCommand::~GotoCommand() {
	delete this->line_destination;
	delete this->command_linenumber;
}

string GotoCommand::format() const {
	return this->command_linenumber->format() + " GOTO <" + this->line_destination->format() + '>';
	//format as string
}

string GotoCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t GotoCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}

size_t GotoCommand::getDestination() const {
	return this->line_destination->getLinenumber();
	//return line destination
}


IfCommand::IfCommand(LineNumber* command_linenumber, string command_type, BooleanExpression* boolean_condition, LineNumber* line_destination) {
	this->command_linenumber = command_linenumber;
	this->boolean_condition = boolean_condition;
	this->line_destination = line_destination;
	this->command_type = command_type; //initialize string of command type
}

IfCommand::~IfCommand() {
	delete this->boolean_condition;
	delete this->line_destination;
	delete this->command_linenumber;
}

string IfCommand::format() const {
	return this->command_linenumber->format() + " IF [" + this->boolean_condition->format() + "] THEN <" + this->line_destination->format() + '>';
	//format as string
}

string IfCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t IfCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}

bool IfCommand::getBool() const {
	return this->boolean_condition->getValue();
	//return evaluation of boolean condition
}

size_t IfCommand::getDestination() const {
	return this->line_destination->getLinenumber();
	//return destination line
}


GosubCommand::GosubCommand(LineNumber* command_linenumber, string command_type, LineNumber* line_destination) {
	this->command_linenumber = command_linenumber;
	this->line_destination = line_destination;
	this->command_type = command_type; //initialize string of command type
}

GosubCommand::~GosubCommand() {
	delete this->line_destination;
	delete this->command_linenumber;
}

string GosubCommand::format() const {
	return this->command_linenumber->format() + " GOSUB <" + this->line_destination->format() + '>';
	//format as string
}

string GosubCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t GosubCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}

size_t GosubCommand::getDestination() const {
	return this->line_destination->getLinenumber();
	//return destination line
}


ReturnCommand::ReturnCommand(LineNumber* command_linenumber, string command_type) {
	this->command_linenumber = command_linenumber;
	this->command_type = command_type; //initialize string of command type
}

ReturnCommand::~ReturnCommand() {
	delete this->command_linenumber;
}

string ReturnCommand::format() const {
	return this->command_linenumber->format() + " RETURN";
	//format as string
}

string ReturnCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t ReturnCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}


EndCommand::EndCommand(LineNumber* command_linenumber, string command_type) {
	this->command_linenumber = command_linenumber;
	this->command_type = command_type; //initialize string of command type
}

EndCommand::~EndCommand() {
	delete this->command_linenumber;
}

string EndCommand::format() const {
	return this->command_linenumber->format() + " END";
	//format as string
}

string EndCommand::getCommandType() const {
	return this->command_type; 
	//return command type string
}

size_t EndCommand::getLinenumber() const {
	return this->command_linenumber->getLinenumber();
	//return linenumber
}
