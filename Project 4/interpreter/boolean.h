#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include "arithmetic.h"


class BooleanExpression {
public:
    virtual ~BooleanExpression() {}
    
    virtual std::string format() const = 0; //return boolean expression string
    virtual bool getValue() const = 0; //return evalution of boolean expression
};


class EqualityExpression : public BooleanExpression {
public:
    EqualityExpression(NumericExpression* left, NumericExpression* right);
    ~EqualityExpression();

    virtual std::string format() const; //return boolean expression string
    virtual bool getValue() const; //evalutes boolean expression

private:
    NumericExpression* left;
    NumericExpression* right;
};


class GreaterExpression : public BooleanExpression {
public:
    GreaterExpression(NumericExpression* left, NumericExpression* right);
    ~GreaterExpression();

    virtual std::string format() const; //return boolean expression string
    virtual bool getValue() const; //return evalution of boolean expression

private:
    NumericExpression* left;
    NumericExpression* right;
};


class LesserExpression : public BooleanExpression {
public:
    LesserExpression(NumericExpression* left, NumericExpression* right);
    ~LesserExpression();

    virtual std::string format() const; //return boolean expression string
    virtual bool getValue() const; //return evalution of boolean expression

private:
    NumericExpression* left;
    NumericExpression* right;
};


#endif
