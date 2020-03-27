#include "arithmetic.h"
#include <string>
#include <iostream> 
#include <fstream>
#include <sstream>

using namespace std;


ConstantExpression::ConstantExpression(string constantValue) {
	stringstream s; s << constantValue; s >> this->value;
	//locally defined stoi, can be adapted if value is string type
}

ConstantExpression::~ConstantExpression() {
}

string ConstantExpression::format() const {	
	stringstream t; t << this->value; return t.str();
	//locally defined stoi, can be adapted if value is string type
}


VariableExpression::VariableExpression(string VariableName) {
	this->name = VariableName;
}
    
VariableExpression::~VariableExpression() {	
}

string VariableExpression::format() const {
    return this->name;
}


ArrayExpression::ArrayExpression(string ArrayName, NumericExpression* ArrayPosition) {
	this->name = ArrayName; 
	this->array_position = ArrayPosition; 
}
    
ArrayExpression::~ArrayExpression() {
	delete this->array_position;
	//delete [] this->values; FUTURE IMPLEMENTATION
}

string ArrayExpression::format() const {
	return this->name + "[" + this->array_position->format() + "]";
}


AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
	this->left = left; 
	this->right = right;
}

AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}


SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
	this->left = left; 
	this->right = right;
}

SubtractionExpression::~SubtractionExpression() {
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}


MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
	this->left = left; 
	this->right = right;
}

MultiplicationExpression::~MultiplicationExpression() {
    delete this->left;
    delete this->right;
}

string MultiplicationExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}


DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
	this->left = left; 
	this->right = right;
}

DivisionExpression::~DivisionExpression() {
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}
