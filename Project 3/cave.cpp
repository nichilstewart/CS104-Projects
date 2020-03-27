#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stack>

using namespace std;

class Cave {
public:
    Cave(char* input_path);
    ~Cave();
    int explore_cave();
    //function for distance calculation

private:
	stack<string> move_history; //stack of past moves
	int distance; //number total moves
    ifstream input; //input stream
};

Cave::Cave(char* input_path) : distance(0), input(input_path) {}

Cave::~Cave() {}

int Cave::explore_cave() {
   
    string direction;
    //create string for to read in directions
 
	while(getline(input, direction)) {        

		if (move_history.empty()) {
				//if empty, don't check top
	        	move_history.push(direction);
	        	distance++;
		}

	    else if (direction == "N") {   
	        if (move_history.top() == "S") {
	        	move_history.pop();
	        	distance--;
	        	//if previous move is in opposite direction, pop
	        	//move from top and walk back/roll up string. 
	        }
	        else {
	        	move_history.push(direction);
	        	distance++;
	        	//otherwise, push new direction to stack and
	        	//continue to walk forward/let out string.
	        }
	    } 

	    else if (direction == "S") {   
	        if (move_history.top() == "N") {
	        	move_history.pop();
	        	distance--;
	        	//see above
	        }
	        else {
	        	move_history.push(direction);
	        	distance++;
	        	//see above
	        }
	    }  

	    else if (direction == "E") {   
	        if (move_history.top() == "W") {
	        	move_history.pop();
	        	distance--;
	        	//see above
	        }
	        else {
	        	move_history.push(direction);
	        	distance++;
	        	//see above
	        }
	    } 

	  	else if (direction == "W") {   
	        if (move_history.top() == "E") {
	        	move_history.pop();
	        	distance--;
	        	//see above
	        }
	        else {
	        	move_history.push(direction);
	        	distance++;
	        	//see above
	        }
	    } 

    	else { //not N,S,E,W (do nothing)
    	}
    }
    return distance;
    //return resulting distance
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }

    Cave cave(argv[1]); 
	int value = cave.explore_cave();
	//create and execute cave function
    
    cout << value << endl;
    //output calculated value

	return value;
	//main also returns said value
}