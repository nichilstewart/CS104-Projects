//#include "arithmetic"
#include "boolean.h"
#include <string>

using namespace std;


EqualityExpression::EqualityExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

EqualityExpression::~EqualityExpression() {
    delete this->left;
    delete this->right;
}

string EqualityExpression::format() const {
    return this->left->format() + " = " + this->right->format();    
}

bool EqualityExpression::getValue() const {
	if (this->left->getValue() == this->right->getValue()) {
		//if values of right and left expressions are equal
		return true;
	} 
	else { //not equal
		return false;
	}
}


GreaterExpression::GreaterExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

GreaterExpression::~GreaterExpression() {
    delete this->left;
    delete this->right;
}

string GreaterExpression::format() const {
	return this->right->format() + " < " + this->left->format();    
}

bool GreaterExpression::getValue() const {
	if (this->right->getValue() < this->left->getValue()) {
		//left expression is greater than right
		return true;
	} 
	else { //not greater
		return false;
	}
}


LesserExpression::LesserExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

LesserExpression::~LesserExpression() {
    delete this->left;
    delete this->right;
}

string LesserExpression::format() const {
    return this->left->format() + " < " + this->right->format();
}

bool LesserExpression::getValue() const {
	if (this->left->getValue() < this->right->getValue()) {
		//left expression is lesser than right
		return true;
	} 
	else { //not lesser
		return false;
	}
}
