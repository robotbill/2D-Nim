#ifndef _MATRIX_H
#define _MATRIX_H

#include <fstream>
#include <iostream>
using namespace std;
#include <vector.h>

/*
 * Matrix class for 2-d NIM.
 * July 13, 2005
 * by Joe Lewis
 */
 
 
class Matrix
{
	public:
		Matrix();						// Default constructor size 0 x 0
		Matrix( int rows, int cols);	// rows x cols matrix
		
	// assignment
		const Matrix & operator = (const Matrix & rhs);
		
	// indexing
		const vector<int> & operator [] (int k) const;	// indexing
		vector<int> & operator [] (int k);				// indexing

	// modifiers
		void normalize();				// Put the matrix in normal form
		void resize(int rows, int cols); // resize the matrix
		
	// accessors
		int rows() const;				// accessor for myRows
		int cols() const;				// accessor for myCols
		
		void print() const;					// prints the matrix
		void printTo(ofstream & output) const;
		int hash(int prime) const;		// compute hash value for matrix
		int sum() const;				// Add up the elements of the matrix
	
	private:
		int myRows;						// # of rows
		int myCols;						// # of columns
		vector < vector<int> > myMatrix;// Matrix of items
		void swapRow(int r1, int r2);	// Swap r1 with r2
		void swapCol(int c1, int c2);	// Swap c1 with c2
		int rowsum(int row);
		int colsum(int col);
		void findMax(int & row, int & col); // Find the location of largest
		                                    // heap starting at [row][col]
};

// non-member functions

const bool operator ==(const Matrix & lhs, const Matrix & rhs);

#endif