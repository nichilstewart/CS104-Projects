#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>


class NumericExpression {
public:
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;
};


class ConstantExpression : public NumericExpression { 
public:
    ConstantExpression(std::string constantValue);
    ~ConstantExpression();

    virtual std::string format() const;

private:
	int value;
	//std::string value; //FUTURE IMPLEMENTATION
};


class VariableExpression : public NumericExpression {
public:
	VariableExpression(std::string VariableName /*, std::string VariableValue*/);
    ~VariableExpression();

    virtual std::string format() const;

private:
	std::string name;
	//int value; //FUTURE IMPLEMENTATION
};


class ArrayExpression : public NumericExpression {
public:
	ArrayExpression(std::string ArrayName, NumericExpression* ArrayPosition /*, std::string ArrayValue*/);
    ~ArrayExpression();

    virtual std::string format() const;
    
private:
	std::string name;
	NumericExpression* array_position; 
  //int value; //FUTURE IMPLEMENTATION
};



class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


class SubtractionExpression : public NumericExpression {
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


class MultiplicationExpression : public NumericExpression {
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


class DivisionExpression : public NumericExpression {
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();

    virtual std::string format() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

#endif
