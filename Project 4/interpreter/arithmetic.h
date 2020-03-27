#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <map>


class NumericExpression {
public:
    virtual ~NumericExpression() {}

    virtual std::string format() const = 0; //returns print string
    virtual int getValue() const = 0; //returns value of object
    virtual bool isArray() const {return false;} //returns if object is an array
};


class ConstantExpression : public NumericExpression { 
public:
    ConstantExpression(std::string constantValue);
    ~ConstantExpression();

    virtual std::string format() const;
    virtual int getValue() const; //returns value of object


private:
	int value;
};


class VariableExpression : public NumericExpression {
public:
	VariableExpression(std::string VariableName, int* TempValue);
    ~VariableExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object
    virtual bool isArray() const; //returns false

private:
	std::string name;
    int* value; //specific value corresponding to variable map
};


class ArrayExpression : public NumericExpression {
public:
	ArrayExpression(std::string ArrayName, NumericExpression* ArrayPosition, std::map<int,int>* ValueArray);
    ~ArrayExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object
    virtual bool isArray() const; //returns true 
    int getIndex() const; //evaluates index value

private:
	std::string name;
	NumericExpression* array_position; 
    std::map<int,int>* value_array; //variable map within map of all variable names
    //note: uses map structure to represent an array 
};


class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object

private:
    NumericExpression* left;
    NumericExpression* right;
};


class SubtractionExpression : public NumericExpression {
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object

private:
    NumericExpression* left;
    NumericExpression* right;
};


class MultiplicationExpression : public NumericExpression {
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object

private:
    NumericExpression* left;
    NumericExpression* right;
};


class DivisionExpression : public NumericExpression {
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();

    virtual std::string format() const; //returns print string
    virtual int getValue() const; //returns value of object

private:
    NumericExpression* left;
    NumericExpression* right;
};

#endif
