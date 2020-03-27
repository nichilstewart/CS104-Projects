#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

class TheRani {
public:
    TheRani(char* input_path, char* output_path);
    ~TheRani();
    void main();

private:
    int experiment_count;       // To track the number of experiments
    int* subject_counts;        // For each, the number of subjects
    string** subject_history;   // And for each subject, their history
    int total_subjects;         // Also the total number of subjects
    bool has_started;           // Has start been executed
    bool not_int;               // Is input not an integer


    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    void execute(const string& line);    // Called in the main method
    void cleaner();                      // Cleans memory on exit
    int num_check(string str_num);       // Checks if input is an integer

};

TheRani::TheRani(char* input_path, char* output_path) : experiment_count(0),
total_subjects(0), has_started(false), not_int(false), input(input_path), 
output(output_path){

}

TheRani::~TheRani() {

}

void TheRani::main() {
    int line_num = 0;
    string line;
    while (getline(input, line)) {
        line_num++;
        try {
            this->execute(line);
        } catch(exception& e) {
            this->output << "Error on line " << 
            line_num << ": " << e.what() << endl;
            //Sends error report to output file
        }
    }
    cleaner();
}

void TheRani::cleaner() {

    if (has_started == true){
       for(int i = 0; i <= experiment_count; i++){

            delete [] subject_history[i];
        }
        delete [] subject_history;
        delete [] subject_counts;
    }
}

int TheRani::num_check(string str_num){

    stringstream ss; double dou_num; ss << str_num; ss >> dou_num;

    if (ss.fail()){

        not_int = true;
        return -1;
        //Not a number
    }

    if ((int)dou_num != dou_num){

        not_int = true;
        return -1;
        //Not an int
    }

    else {

        return (int)dou_num;
        //Is an int
    }
}

void TheRani::execute(const string& line) {
    string command;
    stringstream stream(line);  
    stream >> command;          

    if (command == "START") {   

        string temp_str_subs;       
        //Temporary string for input
        stream >> temp_str_subs;    
        //Read into temporary string

        int temp_int_subs = num_check(temp_str_subs);
        //Get integer value

        if (stream.fail()){

            throw out_of_range("too few arguments"); return;
            //If no input to read
        }

        else if (not_int == true){

            not_int = false;
            throw out_of_range("expected integer argument"); return;
            //If the not-integer flag has been turned on
        }

        else if (temp_int_subs < 0) {

            throw out_of_range("argument out of range"); return;
            //If negative pool size
        }

        else {

            total_subjects = temp_int_subs;     
            //Ppdate total_subjects variable

            if (has_started == true){           
            //In case has been started before

                for(int i = 0; i <= experiment_count; i++){

                    delete [] subject_history[i];
                }
                delete [] subject_history;
                delete [] subject_counts;
                //Clear all subject memory        
                experiment_count = 0;
                //Reset the number of experiments
            }

            has_started = true; 
            //Program start flag on

            subject_history = new string*[1];            
            subject_history[0] = new string[total_subjects];
            //Declare memory for subject history

            for(int i = 0; i < total_subjects; i++){

                subject_history[0][i] = "";             
                //Set new column to blank
            }

            subject_counts = new int[1];          
            //Declare memory for subject history
            subject_counts[0] = total_subjects;   
            //Set to total subjects
        }

    } 

    else if (command == "ADD") {

        if (has_started == false) {

            throw out_of_range("no subjects yet");
            //First command is not start
        }

        else {

            experiment_count++; 

            int* temp_subject_counts = new int[experiment_count + 1];
            temp_subject_counts[experiment_count] = 0;
            //Create new array for larger subject count

            for(int i = 0; i < experiment_count; i++){ 

                temp_subject_counts[i] = subject_counts[i];
                //Fill in new array
            }
            delete [] subject_counts; 
            //Wipe memory
            subject_counts = temp_subject_counts;       
            //Reset pointer

            string **updated_subject_history = 
            new string*[experiment_count + 1];
            //Create new array for larger subject history

            for (int i = 0; i <= experiment_count; i++){

                updated_subject_history[i] = new string[total_subjects];
                //Fill in new array
            }

            for(int i = 0; i < total_subjects; i++){
                            
                updated_subject_history[experiment_count][i] = "";
                //Set new column to blank
            }

            for(int i = 0; i < experiment_count; i++){ 
            //i < experiment count does not include latest experiment

                for(int j = 0; j < total_subjects; j++){

                    updated_subject_history[i][j] =
                    subject_history[i][j];
                    //Set to previous array values
                }
                delete [] subject_history[i];  
            }
            delete [] subject_history;
            //Wipe memory

            subject_history = updated_subject_history;  
            //Reset pointer
        }
    }    

    else if (command == "MOVE") {

        string t_exp_1, t_exp_2, t_sub_first, t_sub_last;
        stream >> t_exp_1 >> t_exp_2 >> t_sub_first >> t_sub_last;
        //Create strings to read in all inputs

        int exp_1 = num_check(t_exp_1); 
        int exp_2 = num_check(t_exp_2);
        int sub_first = num_check(t_sub_first);
        int sub_last = num_check(t_sub_last);
        //Get int values of inputs

        if (has_started == false) {

            throw out_of_range("no subjects yet"); return;
            //First command is not start
        }

        else if (stream.fail()) {

            throw out_of_range("too few arguments"); return;
            //Not enough arguments
        }

        else if (not_int == true){

            not_int = false;
            throw out_of_range("expected integer argument"); return;
            //Not an integer
        }

        else if (exp_1 > experiment_count || exp_2 > experiment_count ||
                sub_first >= subject_counts[exp_1] || sub_last >= 
                subject_counts[exp_1] ||exp_1 < 0 || exp_2 < 0 || 
                sub_first < 0 || sub_last < 0){

            throw out_of_range("argument out of range"); return;
            //Inputs are out of range
        }

        else if (sub_first > sub_last)
        {
            throw out_of_range("invalid range of subjects to move"); return;
            //First subject in higher location than second
        }

        else {

            int moved_subs_count = sub_last - sub_first + 1;
            //Number of subs being moved

            string* temp_pool = new string[total_subjects];
            //Allocate temporary string pool

            for(int i = 0; i < total_subjects; i++ ){

                temp_pool[i] = subject_history[exp_1][i];
                //Copy values from previous pool
            }                        

            for(int i = sub_first; i <= sub_last; i++){

                if (exp_2 != 0){

                    //If not being moved to the main pool (experiment 0)
                    stringstream ss; ss << exp_2; string str_exp_2 = ss.str();
                    temp_pool[i] += str_exp_2 + " ";
                }   

                int increment = 0; 
                //Increment variable

                subject_history[exp_2][subject_counts[exp_2] + increment] 
                = temp_pool[i];                              
                //Move the string to experiment 2

                subject_counts[exp_2]++; 
                subject_counts[exp_1]--;
                //Update experiment subject counts
            }

            for(int i = sub_last + 1; i < subject_counts[exp_1]; i++ ){

                subject_history[exp_1][i] = "";
                subject_history[exp_1][i - moved_subs_count] = temp_pool[i];
                //For moving down all the subjects in old experiment
            }

            delete [] temp_pool; 
            //delete memory
        }       
    }  


    else if (command == "QUERY") {

        string exp_num, sub_num;
        stream >> exp_num >> sub_num;
        //Set temp strings to read input

        int experiment_number = num_check(exp_num); 
        int subject_number = num_check(sub_num);
        //Get int values
    
        if (has_started == false) {

            throw out_of_range("no subjects yet"); return;
            //First command is not start
        }

        else if (stream.fail()) {

            throw out_of_range("too few arguments"); return;
            //Not enough inputs
        }

        else if (not_int == true) {

            not_int = false;
            throw out_of_range("expected integer argument"); return;
            //Not a valid int
        }

        else if (experiment_number > experiment_count || subject_number >= 
            total_subjects || experiment_number < 0 || subject_number < 0) {

            throw out_of_range("argument out of range"); return;
            //Out of range
        }

        else {

        this->output << subject_history[experiment_number][subject_number]+"\n";
                          //Write history to output text file
        }
    }

    else {

        if (has_started == false){

            throw out_of_range("no subjects yet"); return;
            //First command not start
        }

        else {

            throw out_of_range("command does not exist"); return;
            //Command does not exist
        }
    }  
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }
    TheRani tr(argv[1], argv[2]);
    tr.main();
    return 0;
}