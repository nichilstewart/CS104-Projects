#include <vector>
#include <string>
#include "heap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


using namespace std;

struct GraphNode{
	string word; //word string
	int heuristic; //heuristic value
	vector<int> transformations; //words within 1 letter
	GraphNode(string w, int h) : word(w), heuristic(h) { }
};


void toUpper(string& input) {

	for (size_t i=0; i < input.size(); i++) {

		if ((int)input[i] >= 97 && (int)input[i] <= 122 ) {
			//if ASCII value of character is lowercase
			//then make uppercase by subtracting 32
			int convert = (int)input[i]-32;
			input[i] = (char)convert;
		}
	}
}


int calculateHeuristic(const string& word, const string& end) {
	int count = 0;
	//counts number of different letters
	for (size_t i=0; i<word.size(); i++) {
		if (word[i] != end[i]) {count++;}
		//letters don't match
	}
	return count;
}


void makeGraph(vector<GraphNode>& graph, map<string,int>& index_map){

	for (size_t i=0; i<graph.size(); i++) {
		string temp_word = graph[i].word;
		//get the word for easier access

		for (size_t j=0; j<temp_word.size(); j++) {
			string temp_copy = temp_word;
			//copy the word to iterate through all transformations

			for (char k = 'A'; k <= 'Z'; k++) {
				temp_copy[j] = k;
				//change single character in string
				
				if(temp_copy != temp_word) { //skips itself

					map<string, int>::iterator it = index_map.find(temp_copy); 
					//check if word exists in all graph nodes		

					if (it != index_map.end()){ //if word does exist
						int temp_index = it->second;
						// add it to the graph neighbors
						int location = index_map[temp_word];
						//location of original word graph node
						graph[location].transformations.push_back(temp_index);
						//add location of transformed word in diction
					}
				}
			}
		} 
	}
}


void searchGraph(vector<GraphNode>& graph, map<string,int>& index_map, int start_index, string& end) {

	bool visited[graph.size()]; //visited array (prevent backwards/loops)
	int g_values[graph.size()]; //g-value array (total steps)

	for (size_t i=0; i<graph.size(); i++){
		visited[i] = false;
		g_values[i] = 0;
		//set all values to false and 0
	}

	bool foundWord = false; //found target word
	int expansions = 0; //total expansions

	MinHeap<string> heap(2); // base-2 heap
	map<string, int> order_added; //order added to heap

	string start_word = graph[start_index].word; //get the start word
	
	int priority = (graph[start_index].heuristic)*(start_word.size()+1)+(graph[start_index].heuristic); 
	//calculate priority while also breaking all ties

	order_added[start_word] = heap.add(start_word, priority); //first node in heap
	//note that add() function returns the number of times calle to update order_added array

	while(!heap.isEmpty()) {

		string current_word = heap.peek(); 
		//peek top of the heap
		visited[index_map[current_word]] = true; 
		//update visited array
		heap.remove(); 
		//remove the node

		if (current_word == end) { //found the word!!
			foundWord = true; 
			cout << g_values[index_map[current_word]] + graph[index_map[current_word]].heuristic << endl;
			//g_value of current word + h_value of current word
			cout << expansions << endl;
			break; //don't have to continue searching
		}

		else { //havent't found word yet
			expansions++; //update total expansions
			for (size_t i=0; i < graph[index_map[current_word]].transformations.size(); i++) {

				int index = graph[index_map[current_word]].transformations[i];
				//copy index of next transformed word
				int h_value = graph[index].heuristic;
				//get the h_value of next transformed word

				if (!visited[index]){ 
				//if not visited, continue search on new word
					visited[index] = true; 
					//update visited array
					g_values[index] = g_values[index_map[current_word]] + 1; 
					//updates g value if finds a shorter path				
					int priority = (g_values[index]+h_value)*(graph[index].word.size()+1)+h_value; 
					//set priority value;
					order_added[graph[index].word] = heap.add(graph[index].word, priority); 
					// add into heap, update order_added
				}
				else if (g_values[index_map[current_word]]+1 < g_values[index]){ //
				//visited and can update
					g_values[index] = g_values[index_map[current_word]] + 1;
					//updates g value if finds a shorter path				
					int priority = (g_values[index]+h_value)*(graph[index].word.size()+1)+h_value;
					//set priority value;
					heap.update(order_added[graph[index].word], priority);
					//update priority value of word
				}
			}
		}
	}

	if (foundWord == false) {
	//didn't find path from start to end
		cout << "No transformation" << endl;
		cout << expansions << endl;
	}
}


int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Please provide appropriate number of inputs." << endl;
        //output error
        return 1;
    }

    string start = argv[1];
    string end = argv[2];

    toUpper(start);
    toUpper(end);

	if (start == end || start.size() != end.size()) {
		//either start is the same as end or strings are different sizes
		cout << "No transformation" << endl << 0 << endl;
		return 1;
	}

    ifstream input(argv[3]);

    if (input.fail()) {
    	cout << "File <" << argv[3] << "> cannot be opened." << endl;
    	//text file cannot be opened
    	return 1;
    }

	int n; //number of words in the list
	input >> n;

	string temp; //dummy line
	getline(input, temp);

	vector<GraphNode> graph; 
	// all graph nodes
	map<string, int> index_map; //pos_map???
	// map from word to index in the vector

	string line, word; 
	//line and word variable

	int index = 0;
	int start_index = 0;
	//index of word location in graph

	for (int i=0; i<n; i++) {

		getline(input, line);
		if (line != "") { 
		// skip if empty line

			stringstream ss(line);
			ss >> word;
			toUpper(word); 
			//read in word, convert to uppercase

			if (word.size() == start.size()) {
			//skip if different in size

				int heuristic = calculateHeuristic(word, end); 
				//calculate heuristic
				GraphNode temp_node(word, heuristic); 
				//create node
				graph.push_back(temp_node); 
				//push node into graph array

				index_map[word] = index; 
				//insert word key and index value
				if (word == start) {
					start_index = index;
					//set index of start of A* search
				}
				index++;
				//update index when not empty and correct size
			}
		}
	}

	makeGraph(graph, index_map); 
	//make the graph
	searchGraph(graph, index_map, start_index, end); 
	//run A* search on graph
	return 0;
}
