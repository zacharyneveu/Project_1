#ifndef MATRIX_CLASS
#define MATRIX_CLASS

#include <iostream>
#include <vector>

#include "d_except.h"

using namespace std;

template <typename T>
class matrix
{
	public:
		matrix(int numRows = 1, int numCols = 1, const T& initVal = T());
			// constructor.
			// Postcondition: create array having numRows x numCols elements
			// all of whose elements have value initVal

		vector<T>& operator[] (int i);
			// index operator.
			// Precondition: 0 <= i < nRows. a violation of this
			// precondition throws the indexRangeError exception.
			// Postcondition: if the operator is used on the left-hand
			// side of an assignment statement, an element of row i 
			// is changed

		const vector<T>& operator[](int i) const;
			// version for constant objects

		int rows() const;
				// return number of rows
		int cols() const;
				// return number of columns

		void resize(int numRows, int numCols);
				// modify the matrix size.
				// Postcondition: the matrix has size numRows x numCols.
				// any new elements are filled with the default value of type T

		void fillMatrix(vector <T> indexVector, vector <T> ratioVector); // populates matrix
		void sortByRatio(); // sorts matrix by ratio

	private:
      	int nRows, nCols;
			// number of rows and columns

      	vector<vector<T> > mat;
			// matrix is implemented as nRows vectors (rows),
			// each having nCols elements (columns)
};

template <typename T>
matrix<T>::matrix(int numRows, int numCols, const T& initVal):
	nRows(numRows), nCols(numCols),
	mat(numRows, vector<T>(numCols,initVal))
{}

// non-constant version. provides general access to matrix
// elements
template <typename T>
vector<T>& matrix<T>::operator[] (int i)
{
	if (i < 0 || i >= nRows)
		throw indexRangeError(
			"matrix: invalid row index", i, nRows);

   return mat[i];
}

// constant version.  can be used with a constant object.
// does not allow modification of a matrix element
template <typename T>
const vector<T>& matrix<T>::operator[] (int i) const
{
	if (i < 0 || i >= nRows)
		throw indexRangeError(
			"matrix: invalid row index", i, nRows);

   return mat[i];
}

template <typename T>
int matrix<T>::rows() const
{
   return nRows;
}

template <typename T>
int matrix<T>::cols() const
{
   return nCols;
}

template <typename T>
void matrix<T>::resize(int numRows, int numCols)
{
   int i;
   
   // handle case of no size change with a return
   if (numRows == nRows && numCols == nCols)
      return;

	// assign the new matrix size
	nRows = numRows;
	nCols = numCols;

	// resize to nRows rows
	mat.resize(nRows);

	// resize each row to have nCols columns
	for (i=0; i < nRows; i++)
		mat[i].resize(nCols);
}

// Populate matrix with index and ratios of knapsack objects
template <typename T>
void matrix<T>::fillMatrix(vector <T> indices, vector <T> ratios) {
	// resize matrix, # of rows = number of knapsack objects, # of cols = 2
	resize(indices.size(), 2);
	for(int i = 0; i < rows(); i++) {
		mat[i][0] = indices[i]; // first column of matrix contains indices
		mat[i][1] = ratios[i]; // second column of matrix contains ratios
	}
}

// Sorts matrix by value/cost ratio of knapsack object and keeps track of indices
template <typename T>
void matrix<T>::sortByRatio() {
	int temp;
	// Iterate through matrix
	for (int i = 0; i < rows() - 1; i++) {
		temp = i;
		for (int j = i+1; j < rows(); j++) {
			if (mat[j][1] > mat[temp][1]) // checks if comparison object is larger than current object
				temp = j;
		}
		mat[temp].swap(mat[i]); // swap objects if ratio of comparison object > current object
	}
}

#endif	// MATRIX_CLASS
