#include "company.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}


CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  for (int i = 0; i < numCompanies; i++) {

    Company* find_parent = findParent(i);
    //locate parent company of 'i'th student

    if (find_parent == companies[i]) { 
      //if student is largest company
      delete companies[i];
      //delete initial student
    }

    else {
      DeleteHelper(find_parent); 
      //calls helper function for each input
      delete companies[i];
      //deletes student company
    }
  }
  delete [] companies;
  //delete companies array
}


void CompanyTracker::DeleteHelper(Company* del_company) {

  if (del_company->merge1 == nullptr || del_company->merge2 == nullptr) {
    return;
  }
  //if company is an initial student

  Company* child1 = del_company->merge1;
  child1->parent = nullptr;
  Company* child2 = del_company->merge2;
  child2->parent = nullptr;
  //create pointers to merged companies
  //set parent pointers to nullptr

  delete del_company;
  //delete parent company

  DeleteHelper(child1);
  DeleteHelper(child2);
  //recursively call function for each merged company
}


bool CompanyTracker::invalidInput(int i) {
  //checks if invalid single input

  if (i < 0 || i >= numCompanies) {return true;}
  //if i is not in companies array

  return false;
}


bool CompanyTracker::invalidInput(int i, int j) {
  //checks if invalid double input

  if (i < 0 || i >= numCompanies) {return true;}
  if (j < 0 || j >= numCompanies) {return true;}
  //if i or j is not within companies array
  if (i == j) {return true;}
  //if i and j are the same

  return false;
}


Company* CompanyTracker::findParent(int i) {
  //finds 'i'th student's highest parent company

  Company* find_parent = companies[i];
  //create pointer to 'i'th student

  while (find_parent->parent != nullptr) {

    find_parent = find_parent->parent;
    //finds highest parent company
  }

  return find_parent;
  //return pointer to highest parent company
}


void CompanyTracker::merge (int i, int j) {
  //merges 'i' and 'j' student's highest parent companies

  if (invalidInput(i,j)) {return;}
  //checks if invalid inputs

  Company* child1 = findParent(i);
  Company* child2 = findParent(j);

  if (child1 == child2) {return;}
  //checks if students have same highest parent

  Company* new_parent = new Company(child1, child2);
  //creates new parent company

  child1->parent = new_parent;  
  child2->parent = new_parent;
  //sets parent pointers to new company
}


void CompanyTracker::split (int i) {
  //splits 'i'th student's highest parent company

  if (invalidInput(i)) {return;}
  //checks if invalid input

  Company* find_parent = findParent(i);
  //finds highest parent company

  if (find_parent == companies[i]) {return;}
  //if original student is highest company, return

  Company* divorcee1 = find_parent->merge1;
  divorcee1->parent = nullptr;
  Company* divorcee2 = find_parent->merge2;
  divorcee2->parent = nullptr;
  //create pointers to each merged company
  //set parent pointers to nullptr

  delete find_parent;
  //delete parent company
}


bool CompanyTracker::inSameCompany (int i, int j) {
  //checks if 'i' and 'j' students are in same company

  if (i == j) {return true;}
  //true if inputs are same
  if (invalidInput(i,j)) {return false;}
  //false if inputs out of range

  Company* student1 = findParent(i);
  Company* student2 = findParent(j);
  //find highest parents

  if (student1 == student2)
  {
    return true;
    //true if same parent
  }
  return false;
  //false if differnt parents
}