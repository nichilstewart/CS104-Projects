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

int ConstantExpression::getValue() const {
	return value;
	//returns value of constant
}


VariableExpression::VariableExpression(string VariableName, int* TempValue) {
	this->name = VariableName;
	this->value = TempValue;
}
    
VariableExpression::~VariableExpression() {
	//int* value is deleted via map in interpreter.cpp
}

string VariableExpression::format() const {
    return this->name;
}

int VariableExpression::getValue() const {
	return (*value);
	//returns value of int* value pointer
}

bool VariableExpression::isArray() const {
	return false; //not an array
}


ArrayExpression::ArrayExpression(string ArrayName, NumericExpression* ArrayPosition, map<int,int>* ValueArray) {
	this->name = ArrayName; 
	this->array_position = ArrayPosition; 
	this->value_array = ValueArray;
}
    
ArrayExpression::~ArrayExpression() {
	delete this->array_position;
	//map<int,int>* value_array is deleted via map in interpreter.cpp
}

string ArrayExpression::format() const {
	return this->name + "[" + this->array_position->format() + "]";
}

int ArrayExpression::getValue() const {
	int index_position = this->array_position->getValue(); 
	//evaluate array_position

	if (value_array->find(index_position) != value_array->end()) {
		int temp_val = (*value_array)[index_position];
		return temp_val;
		//finds the corresponding value to the index position
	}
	else {
		return 0; //array position not yet defined, returns 0
	}
}

bool ArrayExpression::isArray() const {
	return true; //is an array
}

int ArrayExpression::getIndex() const {
	return this->array_position->getValue();
	//returns value of index object
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

int AdditionExpression::getValue() const {
	return this->left->getValue() + this->right->getValue();
	//add values of left and right expressions
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

int SubtractionExpression::getValue() const {
	return this->left->getValue() - this->right->getValue();
	//subtract values of left and right expressions
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

int MultiplicationExpression::getValue() const {
	return this->left->getValue() * this->right->getValue();
	//multiply values of left and right expressions
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

int DivisionExpression::getValue() const {
	if (this->right->getValue() != 0) {
		//does not divide by 0

		return this->left->getValue() / this->right->getValue();
		//divide values of left and right expressions
	}
	else { //divides by 0
		string error = "Division by 0: <" + left->format() + "> = <" +
		to_string(left->getValue()) + ">, <" + right->format() + "> = <" + 
		to_string(right->getValue()) + ">.";
		//format error string

		throw out_of_range(error); return 0;
		//throw divide by 0 error
	}
}
