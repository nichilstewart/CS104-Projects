#include <iostream>
#include <ctime>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../avl/avlbst.h"
#include "../splay/splay.h"

using namespace std;

void parse(vector<string>& node_array, istream& in) {
    
    string line; //storage line
	while (getline(in, line)) {

        stringstream stream(line); //to read content value
        string content; //to store content

        while(stream >> content) {
        	node_array.push_back(content); //read content into vector
        }
    }
}

void AVLTimer(vector<string>& node_array, ofstream& out) {

	AVLTree<string, int> myavl; //declare AVL tree
	std::pair <string,int> insert_pair; //create pair for insertion
    
    const int ITERATE = 1000; //iterations
    clock_t start, finish; //declare clock
    double duration; //create duration timer

    start = clock(); //start timer

    for (int i = 0; i < ITERATE; i++) {
		for (size_t i=0; i < node_array.size(); i++) {
			insert_pair = make_pair (node_array[i], i); 
			myavl.insert(insert_pair); //make and insert pair
		}
	}
	
	finish = clock(); //finish timer
   	duration = (double)(finish - start); //calc duration
	duration /= (CLOCKS_PER_SEC * ITERATE); //calc duration

    //cout << "AVL " << /*scientific <<*/ duration << " seconds" << endl; //cout method
    out << "AVL " << /*scientific <<*/ duration << " seconds" << endl; //output file
}

void SplayTimer(vector<string>& node_array, ofstream& out) {

	SplayTree<string, int> mysplay; //declare Splay tree
	std::pair <string,int> insert_pair; //create pair for insertion
    
    const int ITERATE = 1000; //iterations
    clock_t start, finish; //declare clock
    double duration; //create duration timer

    start = clock(); //start timer

    for (int i = 0; i < ITERATE; i++) {
		for (size_t i=0; i < node_array.size(); i++) {
			insert_pair = make_pair (node_array[i], i); 
			mysplay.insert(insert_pair); //make and insert pair
		}
	}

	finish = clock(); //finish timer
   	duration = (double)(finish - start); //calc duration
	duration /= (CLOCKS_PER_SEC * ITERATE); //calc duration

    //cout << "Splay " << /*scientific <<*/ duration << " seconds" << endl;
	//cout << "Splay expensive: " << mysplay.report() << endl; //cout method

	out << "Splay " << /*scientific <<*/ duration << " seconds" << endl;
	out << "Splay expensive: " << mysplay.report() << endl; //output file
}


int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        //argument count error
        return 1;
    }

    ifstream input(argv[1]);

    if (input.fail()) {
    	cout << "File <" << argv[1] << "> cannot be opened." << endl;
    	//output error
    	return 1;
    }

    ifstream in(argv[1]); //declare input stream
    ofstream out(argv[2]); //declare output stream
    vector<string> node_array; //declare node array
	parse(node_array, in); //parse file into vector array

	//cout << node_array.size() << " insertions" << endl; //cout method
	out << node_array.size() << " insertions" << endl; //output file

	AVLTimer(node_array, out); //run AVL tree timer
	SplayTimer(node_array, out); //run Splay tree timer

    return 0;
}