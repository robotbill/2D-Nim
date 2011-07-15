#include "matrix.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;


Matrix::Matrix()
		: myRows(0),
		  myCols(0),
		  myMatrix(0)
{

}

Matrix::Matrix(int rows, int cols)
		: myRows(rows),
		  myCols(cols),
		  myMatrix(rows)
{
	int k;
	for (k = 0; k < rows; k++) {
		myMatrix[k].resize(cols);
	}
}

void Matrix::resize(int rows, int cols)
{
	int k;
	myMatrix.resize(rows);
	
	for(k=0; k < rows; k++)
	{
		myMatrix[k].resize(cols);
	}
	myRows = rows;
	myCols = cols;
}

const Matrix & Matrix::operator = (const Matrix & rhs)
{
	if (this != &rhs) {
		myMatrix.resize(rhs.myRows);
		myRows = rhs.myRows;
		myCols = rhs.myCols;
		
		int k;
		for (k = 0; k < myRows; k++) {
			myMatrix[k] = rhs.myMatrix[k];
		}
	}
	return *this;
}

int Matrix::rows() const
{
	return myRows;
}

int Matrix::cols() const
{
	return myCols;
}

const vector<int> & Matrix::operator []  (int k) const
{
	if (k < 0 || myRows <= k) {
		cerr << "Illegal matrix index: " << k << " max index = ";
		cerr << myRows-1 << endl;
		exit(1);
	}
	return myMatrix[k];
}

vector<int> & Matrix::operator []  (int k)
{
	if (k < 0 || myRows <= k) {
		cerr << "Illegal matrix index: " << k << " max index = ";
		cerr << myRows-1 << endl;
		exit(1);
	}
	return myMatrix[k];
}

void Matrix::print() const
{
	int rowindex,colindex;
	for (rowindex = 0; rowindex < myRows; rowindex++) {
	cout << "|";
		for (colindex = 0; colindex < myCols; colindex++) {
			cout << myMatrix[rowindex][colindex] << " ";
		}
		cout << "|" << endl;
	}
}

void Matrix::printTo(ofstream & output) const
{
	int rowindex,colindex;
	for (rowindex = 0; rowindex < myRows; rowindex++) {
	output << "|";
		for (colindex = 0; colindex < myCols; colindex++) {
			output << myMatrix[rowindex][colindex] << " ";
		}
		output << "|" << endl;
	}
}

int Matrix::hash(int prime) const
{
	int tot = 0;
	int cols,rows;
	for (rows = 0; rows < myRows; rows++) {
		for (cols = 0; cols < myCols; cols++) {
			tot += myMatrix[rows][cols];
		}
	}
	return (tot + myRows + myCols) % prime;
}

int Matrix::sum() const
{
	int tot=0;
	int cols,rows;
	for (rows = 0; rows < myRows; rows++) {
		for (cols = 0; cols < myCols; cols++) {
			tot += myMatrix[rows][cols];
		}
	}
	return tot;
}

void Matrix::normalize()
{
	int i;
	for (i = 0; i < myRows && i < myCols; i++)
	{
		int row = i;
		int col = i;
		findMax(row, col);
		swapRow(i, row);
		swapCol(i, col);
	}
}

void Matrix::swapRow(int r1, int r2)
{
	if (r1 != r2) {		// Only swap if rows are different
		if (r1 < 0 || myRows <= r1 || r2 < 0 || myRows <= r1) {
			cerr << "Illigal row number" << endl;
			exit(1);
		}
		vector<int> temp = myMatrix[r1];
		myMatrix[r1] = myMatrix[r2];
		myMatrix[r2] = temp;
	}
}

void Matrix::swapCol(int c1, int c2)
{
	if (c1 != c2) {		// Only swap if columns are different
		if (c1 < 0 || myCols <= c1 || c2 < 0 || myCols <= c2) {
			cerr << "Illegal column number" << endl;
			exit(1);
		}
		int k,temp;
		for (k = 0; k < myRows; k++) {
			temp = myMatrix[k][c1];
			myMatrix[k][c1] = myMatrix[k][c2];
			myMatrix[k][c2] = temp;
		}
	}
}

void Matrix::findMax(int & row, int & col)
{
	int max = myMatrix[row][col];
	int maxRow = row;
	int maxCol = col;
	int rowcolsum = rowsum(row) + colsum(col);
	int rowindex, colindex;
	
	for (rowindex = row; rowindex < myRows; rowindex++) {
		for (colindex = col; colindex < myCols; colindex++) {
			if (myMatrix[rowindex][colindex] > max ||
				(myMatrix[rowindex][colindex] == max &&
				(rowsum(rowindex) + colsum(colindex)) > rowcolsum)) {
				max = myMatrix[rowindex][colindex];
				maxRow = rowindex;
				maxCol = colindex;
				rowcolsum = rowsum(maxRow) + colsum(maxCol);
			}
		}
	}
	row = maxRow;
	col = maxCol;
}

int Matrix::rowsum(int row)
{
	int colindex;
	int total = 0;
	for (colindex = 0; colindex < myCols; colindex++) {
		total += myMatrix[row][colindex];
	}
	return total;
}

int Matrix::colsum(int col)
{
	int rowindex;
	int total = 0;
	for (rowindex = 0; rowindex < myRows; rowindex++) {
		total += myMatrix[rowindex][col];
	}
	return total;
}

const bool operator ==(const Matrix & lhs, const Matrix & rhs) {
	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
		return false;
	int rowindex,colindex;
	
	for (rowindex = 0; rowindex < lhs.rows(); rowindex++) {
		for (colindex = 0; colindex < lhs.cols(); colindex++) {
			if (lhs[rowindex][colindex] != rhs[rowindex][colindex])
				return false;
		}
	}
	return true;
}
