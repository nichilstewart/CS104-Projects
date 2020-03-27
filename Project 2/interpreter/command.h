#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include "boolean.h"

class Command {
public:
	virtual ~Command() {}
    virtual std::string format() const = 0;
};


class LineNumber { 
public:
	LineNumber(std::string temp_linenumber);
	~LineNumber();
	std::string format() const;

private:
	size_t line_number;
};


class PrintCommand : public Command { 
public:
    PrintCommand(LineNumber* command_linenumber, NumericExpression* print_expression);
    ~PrintCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
    NumericExpression* print_expression;
};

class LetCommand : public Command { 
public:
    LetCommand(LineNumber* command_linenumber, NumericExpression* target_variable, NumericExpression* target_value);
    ~LetCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
    NumericExpression* target_variable;
    NumericExpression* target_value;
};


class GotoCommand : public Command { 
public:
    GotoCommand(LineNumber* command_linenumber, LineNumber* line_destination);
    ~GotoCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
    LineNumber* line_destination;
};


class IfCommand : public Command { 
public:
    IfCommand(LineNumber* command_linenumber, BooleanExpression* boolean_condition, LineNumber* line_destination);
    ~IfCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
	BooleanExpression* boolean_condition;
    LineNumber* line_destination;
};


class GosubCommand : public Command { 
public:
    GosubCommand(LineNumber* command_linenumber, LineNumber* jump_line);
    ~GosubCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
	LineNumber* jump_line;
};


class ReturnCommand : public Command { 
public:
    ReturnCommand(LineNumber* command_linenumber);
    ~ReturnCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
	//Access previous Gosub linenumber
	//Implement in future assignment
};


class EndCommand : public Command { 
public:
    EndCommand(LineNumber* command_linenumber);
    ~EndCommand();
    virtual std::string format() const;

private:
	LineNumber* command_linenumber;
};


#endif