#include <iostream>
#include <fstream>
#include "interpreter/interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file." << endl;
        //output error
        return 1;
    }

    ifstream input(argv[1]);

    if (input.fail()) {
    	cout << "File <" << argv[1] << "> cannot be opened." << endl;
    	//output error
    	return 1;
    }

    Interpreter interpreter(input);
    //interpreter.write(cout); //uncomment to include pretty-printing 
    //cout  << endl; //uncomment to seperate pretty-printing
    interpreter.main(cout);
    return 0;
}
