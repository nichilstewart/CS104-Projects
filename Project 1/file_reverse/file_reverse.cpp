#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        //Wrong number of arguments
        cout << "Please enter correct number of arguments" << endl;
        return 1;
    }

    ifstream in_file;               
    //stream to open
    in_file.open(argv[1]);          
    //open file

    if (in_file.fail())
    {                               
        //Failed to read file
        cout << "Sorry, file reading failed" << endl;
        return 1;
    }

    int char_count;                 
    in_file >> char_count;
    //read character count from file

    if (in_file.fail())
    {
        //Not an integer
        cout << "Not an integer!" << endl;
        return 1;
    }

	char* sentence = new char[char_count + 1]; 
    //Dynamically allocate char* array  

	int i = 0;                     
    //Set increment variable

	while(!in_file.eof() && i < char_count + 1)
	{
	    in_file.get(sentence[i]);  //Read single character from file to array
	    i++;                       //Will also replicate spaces, tabs, linebreaks
	}

	for(i = char_count; i >= 0; i--) 
	{
		cout << sentence[i];       
        //Output to terminal
	}	

	delete [] sentence;            
    //Wipe memory
	in_file.close();               
    //close stream

}
