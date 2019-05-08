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

      exhaustiveKnapsack(k, 600);

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
	unsigned int num_objs = k.getNumObjects();
	unsigned int num_subsets = pow(2, num_objs);
	// cout << "number of subsets: " << num_subsets << endl;
	cout << "This is exhausting" << endl;
	for (unsigned int j = 0; j < num_subsets; ++j) {
		for (unsigned int i = 0; i < num_objs; ++i) {
			bool to_select = num_objs & (1<<i);
			if(to_select)
				k.select(i);
			else
				k.unSelect(i);
		}	
		k.getCost();
	}
}
