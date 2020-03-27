#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    //Course item definition

    string name;
    double work;
    double value;
    //all variables

    Course(string n, double w, double v) {
        name = n; work = w; value = v;
        //initializes all course values
    }
};


double maxLearning(vector<Course>& courses, int i, double max_work){
    //i = array place (starts at -1), max_work = remaining unused work 

    if (max_work <= 0.0) return 0.0; 
    //if maximum work is 0 or negative value
    
    if (i == (int)courses.size()-1) return 0.0; 
    //if iterated through entire array

    if (courses[i+1].work > max_work) {

        return maxLearning(courses, i+1, max_work); 
        //skips course if requires too much work
    }

    return max(courses[i+1].value + maxLearning(courses, i+1, max_work - courses[i+1].work), 
    maxLearning(courses, i+1, max_work)); 

    //Returns the maximum of two recursive calls:
    //1st: Include next course in array in total work/learning
    //2nd: Skip next course in array in total work/learning
    //Thus runs BFS by evaluating all 2^n possible binary outcomes
}


int main(int argc, char* argv[]){
    
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

    vector<Course> courses; //vector array of all courses

    string line; //string for line contents

    getline(input, line); //read in current line
    stringstream stream;
    stream << line;

    int course_total; //number of courses
    double max_work; //maximum capable work
    stream >> course_total; //read in values
    stream >> max_work;

    for (int i=0; i < course_total; i++) {

        getline(input, line);
        stringstream stream;
        stream << line;
        //read in input to a line

        string course_name;
        double total_work;
        double total_value;
        //declare all variables

        stream >> course_name;
        stream >> total_work;
        stream >> total_value;
        //read into all variables

        Course c(course_name, total_work, total_value);
        courses.push_back(c);
        //push each course into vector array
    }

    cout << maxLearning(courses, -1, max_work) << endl;
    //array place starts at -1 as i+1 = 0th array place

    return 0;
}