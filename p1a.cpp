// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>
#include <math.h>
#include <stack>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
#include "knapsack.h"

void exhaustiveKnapsack(knapsack &k, int t);
bool increment(knapsack &k);

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

      exhaustiveKnapsack(k, 3);

      cout << endl << "Best solution" << endl;
      k.printSolution();
	  cout << "done" << endl;
      
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


/*
 * param k: knapsack instance
 * param t: limit on total cost
 * Strategy: each item is either selected or un-selected, 0 or 1. Use a simple binary counter to iterate over all
 * possible combinations
 */
void exhaustiveKnapsack(knapsack &k, int t)
{
	clock_t startTime;
	startTime = clock();

	knapsack best_k = k;
	do {
		int val = k.getValue();
		if(val > best_k.getValue() && k.getCost() < k.getCostLimit())
			best_k = k;
		// Set time to run here
		float diff = (float) (clock() - startTime) / CLOCKS_PER_SEC;
		if (diff > t)
		{
			break;
		}
	} while(increment(k));
	k = best_k;
}

bool increment(knapsack &k)
{
	unsigned int num_objs = k.getNumObjects();
	for (int i = 0; i < num_objs; ++i) {
		bool is_set = k.isSelected(i);
		// If already set, reset and go to next bit to carry
		if (is_set) {
			k.unSelect(i);
		}
		// if not set, then set and break loop
		else {
			k.select(i);
			return true;
		}
	}	
	return false;
}
