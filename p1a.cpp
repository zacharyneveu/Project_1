// Project 1a: Solving knapsack using exhaustive search
// p1a.cpp
// Bobby Ky

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>
#include <stack>
#include <cmath>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"

void exhaustiveKnapsack(knapsack &k, int t);
void allSubsets(knapsack &k, int start, int &end, int index, vector<int> &objects, vector<int> &subsets, int &t, clock_t &startTime);
void generateSubsets(knapsack &k, int &size, int start, int &end, int index, vector<int> &objects, vector<int> &subsets, int &t, clock_t &startTime);


int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;
   
   // Read the name of the file from the keyboard or
   // hard code it here for testing.
   
   // fileName = "knapsack16.input";

   cout << "Enter filename" << endl;
   cin >> fileName;
   
   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      cout << "Reading knapsack instance" << endl;
      knapsack k(fin);

      exhaustiveKnapsack(k, 40);

      cout << endl << "Best solution" << endl;
      k.printSolution();
      
   }    

   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }

}

// Function that calls helper functions that
// generate all knapsack subsets and selects the subset with the maximum value
// that doesn't exceed the cost limit
void exhaustiveKnapsack(knapsack &k, int t) {
   unsigned int num_obj = k.getNumObjects(); // numbers of objects in knapsack
   int endIndex = num_obj - 1; // last index of object in knapsack
   clock_t startTime = clock();
   vector<int> objects; // vector used to store object indices
   vector<int> subsets; // vector used to store subsets of objects

   for(int i = 0; i < num_obj; i++){
      objects.push_back(i);
   }

   allSubsets(k, 0, endIndex, 0, objects, subsets, t, startTime);
   
}

// Function that calls generateSubsets() to generate all possible subsets of knapsack objects
void allSubsets(knapsack &k, int start, int &end, int index, vector<int> &objects, vector<int> &subsets, int &t, clock_t &startTime) {
   for(int size = 0; size < end; size++) {
      subsets.clear(); // clear vector
      subsets.resize(size); // resize subsets vector according to "new" size

      generateSubsets(k, size, start, end, index, objects, subsets, t, startTime);

   }
}

// Function that recursively generates subsets of knapsack objects
// and decides which subset is the best (max value and under cost limit)
void generateSubsets(knapsack &k, int &size, int start, int &end, int index, vector<int> &objects, vector<int> &subsets, int &t, clock_t &startTime){
   float runTime = (float) (clock() - startTime) / CLOCKS_PER_SEC; // run time of algorithm

   if (runTime > t) { // if run time is exceeded, return the best knapsack found so far
      return;
   }
   else {
      if(index == size) {
         int cost = 0;
         int value = 0;

         for(int i = 0; i < size; i++) { // calculate cost and value of knapsack
            cost += k.getCost(subsets[i]);
            value += k.getValue(subsets[i]);
         }

         // if the current knapsack has a cost <= the cost limit
         // and its value is greater than the best knapsack found so far
         // unselect all old objects and select the objects in the new subset
         if (cost <= k.getCostLimit() && value > k.getValue()) {
            for(int i = 0; i < k.getNumObjects(); i++) {
               k.unSelect(i);
            }

            for(int i = 0; i < size; i++) {
               k.select(subsets[i]);
            }
         }
         return;
      }

      // recursively iterate through all possible subsets of the knapsack
      for(int i = start; i < end && end - i >= size-index; i++){
         subsets[index] = objects[i];
         generateSubsets(k, size, i + 1, end, index + 1, objects, subsets, t, startTime);
      }

   }
}



