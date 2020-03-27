#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


bool distinctCheck(std::vector<size_t>& i_values) {
//Checks if all letters from initial string are used only once.
//if there are two in with same 'i' value, they are both
//from the same position in the initial string.

for (size_t i=0; i < i_values.size(); i++) {

   for (size_t j=0; j < i_values.size(); j++) {  

      if(i_values[i] == i_values[j] && i != j) { 

         return false; //there exist duplicates from initial string
      }
   }
}
return true;
}

void vector_copy(std::vector<size_t>& i_values_copy, std::vector<size_t>& i_values) {
//copies values of a vector size_to newly created vector.

   for (size_t y=0; y < i_values.size(); y++) {
 
      i_values_copy.push_back(i_values[y]);
      //push back each value size_to vector
   }
}

void permutationsHelper(std::string in, size_t n, std::string curr,
         std::vector<string>& combos, std::vector<size_t> i_values)
{
   if (n == curr.size()){
      //checks if length of string is same as original length

      if (distinctCheck(i_values)) { 
         //checks if all letters from initial string are used only once
         
         combos.push_back(curr);
         //pushes valid combination size_to 'combo' vector
      } 
   }

   else {
      for(size_t i=0; i < in.size(); i++) {

            std::vector<size_t> i_values_copy; //new i_values vector for each case
            vector_copy(i_values_copy, i_values); //copy values to new vector
            i_values_copy.push_back(i); //push back newest i value size_to vector

            permutationsHelper(in, n, curr+in[i], combos, i_values_copy);
            //call the helper function recursively
      }
   }
}


void permutations(std::string in) 
{
   size_t n = in.size(); //to pass in size of initial string
   std::vector<string> combos; //vector containing string combinations
   std::vector<size_t> i_values; //vector containing array positions 

   permutationsHelper(in, n, "", combos, i_values);
   //call helper function

   for (size_t i = 0; i < combos.size(); ++i)
   {
      std::cout << combos[i] << endl;
      //output valid combinations from vector
   }
}
