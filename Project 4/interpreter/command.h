#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include "boolean.h"


class Command {
public:
	virtual ~Command() {}
    
    virtual std::string format() const = 0; //returns formatted print string
    virtual std::string getCommandType() const = 0; //returns string of the command type 
    virtual size_t getLinenumber() const = 0; //returns size_t value of linenumber
};


class LineNumber { 
public:
	LineNumber(std::string temp_linenumber);
	~LineNumber();
	std::string format() const; //returns formatted print string
    size_t getLinenumber() const; //returns size_t value of linenumber

private:
	size_t line_number;
};


class PrintCommand : public Command { 
public:
    PrintCommand(LineNumber* command_linenumber, std::string command_type, NumericExpression* print_expression);
    ~PrintCommand();

    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

    int getInt() const; //return value of numerical object

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
    NumericExpression* print_expression;
};


class LetCommand : public Command { 
public:
    LetCommand(LineNumber* command_linenumber, std::string command_type, NumericExpression* target_variable, NumericExpression* target_value);
    ~LetCommand();

    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

    bool isArray() const; //return if expression is an array
    std::string getName() const; //return variable name as string
    int getTarget() const; //return target value
    int getIndex() const; //return index value

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
    NumericExpression* target_variable;
    NumericExpression* target_value;
};


class GotoCommand : public Command { 
public:
    GotoCommand(LineNumber* command_linenumber, std::string command_type, LineNumber* line_destination);
    ~GotoCommand();
    
    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

    size_t getDestination() const; //return destination line

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
    LineNumber* line_destination;
};


class IfCommand : public Command { 
public:
    IfCommand(LineNumber* command_linenumber, std::string command_type, BooleanExpression* boolean_condition, LineNumber* line_destination);
    ~IfCommand();
    
    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

    bool getBool() const; //return if boolean is true
    size_t getDestination() const; //return destination line

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
	BooleanExpression* boolean_condition;
    LineNumber* line_destination;
};


class GosubCommand : public Command { 
public:
    GosubCommand(LineNumber* command_linenumber, std::string command_type, LineNumber* line_destination);
    ~GosubCommand();
    
    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

    size_t getDestination() const; //return destination line


private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
	LineNumber* line_destination;
};


class ReturnCommand : public Command { 
public:
    ReturnCommand(LineNumber* command_linenumber, std::string command_type);
    ~ReturnCommand();
    
    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
};


class EndCommand : public Command { 
public:
    EndCommand(LineNumber* command_linenumber, std::string command_type);
    ~EndCommand();
    
    virtual std::string format() const; //returns formatted print string
    virtual std::string getCommandType() const; //returns string of the command type 
    virtual size_t getLinenumber() const; //returns size_t value of linenumber

private:
	LineNumber* command_linenumber;
    std::string command_type; //string with type of command
};


#endif
