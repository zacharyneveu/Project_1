// Project 2a: Solving knapsack using greedy algorithms
// p2a.cpp
// Bobby Ky & Zach Neveu

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

void greedyKnapsack(knapsack &k);


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

      greedyKnapsack(k);
      k.printSolution();
      cout << endl << "Output file created." << endl;

      
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

// Function that implements a greedy algorithm to solve the knapsack problem
void greedyKnapsack(knapsack &k) {
    int i = 0; // counter for knapsack elements
    // Iterate through all knapsack objects, objects are stored in a matrix that contains their
    // index and value/ cost ratio. Matrix is sorted by descending order of ratios.
    // Algorithm iterates through matrix and selects any knapsack object whose cost doesn't exceed the cost constraint
    // when added to the knapsack
    while (k.getCost() + k.getCost(k.getKnapsackVector(i)[0]) < k.getCostLimit() && i < k.getNumObjects()) {
        
        k.select(k.getKnapsackVector(i)[0]); // add knapsack object to knapsack
        i += 1;
    }


}





