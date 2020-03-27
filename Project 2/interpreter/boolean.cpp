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


GreaterExpression::GreaterExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {
}

GreaterExpression::~GreaterExpression() {
    delete this->left;
    delete this->right;
}

string GreaterExpression::format() const {
	return this->right->format() + " < " + this->left->format();    
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
