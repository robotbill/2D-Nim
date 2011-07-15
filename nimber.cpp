#include "matrix.h"
#include "nimber.h"
#include <string>
#include <iostream>
using namespace std;
#include <sstream>
#include <math.h>


Nimber::Nimber()
// Makes 0
		: myNimber(1)
{
	myNimber[0] = 0;
}

Nimber::Nimber(int num)
// Stores binary version of number in a vector with most significant digit
// on the end and least signifacant digit in the front.
		: myNimber(0)
{
	int temp = num;
	int i = 0;
	while (temp > 0) {
		myNimber.push_back(temp % 2);
		temp /= 2;
	}
}

Nimber::Nimber(const Nimber & nim)
// Makes a nimber from a nimber.
		: myNimber(nim.getBin().size())
{
	int i;
	for (i = 0; i < myNimber.size(); i++) {
		myNimber[i] = nim.getBin()[i];
	}
}

string Nimber::toString() const
// Turns a nimber into a string *number
{
	int tot = 0;
	int exp, index;
	for (index = 0, exp = 0; index < myNimber.size(); index++, exp++) {
		tot += myNimber[index] * (int)(pow((double)(2), exp));
	}
	ostringstream stream;
	stream << tot;
	return "*" + stream.str();
}

const Nimber & Nimber::operator = (const Nimber & rhs)
// Assignment operator
{
	myNimber.resize(rhs.getBin().size());
	int i;
	for (i = 0; i < myNimber.size(); i++) {
		myNimber[i] = rhs.getBin()[i];
	}
}

const Nimber & Nimber::operator += (const Nimber & nim)
// Pre: adds nim is a nimber
// Post: adds nim to Nimber by xoring the binary representations.
{
	vector<int> temp = nim.getBin();
	if (myNimber.size() < temp.size()) {
		myNimber.resize(temp.size());
	} else if (myNimber.size() > temp.size()) {
		temp.resize(myNimber.size());
	}
	int index;
	for (index = 0; index < myNimber.size(); index++) {
		if (((myNimber[index] + temp[index]) == 0) ||
			 ((myNimber[index] * temp[index]) > 0))
			myNimber[index] = 0;
		else myNimber[index] = 1;
	}
}

Nimber operator + (const Nimber & lhs, const Nimber & rhs)
// Pre: lhs and rhs are Nimbers
// Post: adds lhs and rhs
{
	Nimber temp(lhs);
	temp += rhs;
	return temp;
}

const vector<int> & Nimber::getBin() const
// Returns the reverse binary representation of a Nimber
{
	return myNimber;
}

ostream & operator << (ostream & os, const Nimber & nim)
{
	os << nim.toString();
	return os;
}

bool operator == (const Nimber & lhs, const Nimber & rhs)
//  Check two nimbers to see if they are equal
{
	vector<int> left = lhs.getBin();
	vector<int> right = rhs.getBin();
	if (left.size() < right.size()) {
		left.resize(right.size());
	} else if (left.size() > right.size()) {
		right.resize(left.size());
	}
	int i;
	for (i = 0; i < left.size(); i++) {
		if (left[i] != right[i]) return false;
	}
	return true;
}

bool operator != (const Nimber & lhs, const Nimber & rhs)
// Check if two nimbers are not equal.
{
	if (lhs == rhs) return false;
	else return true;
}

bool operator < (const Nimber & lhs, const Nimber & rhs)
// Nimbers can't actually be less than eachother, this is for sorting purposes
// only
{
	int left = 0;
	int right = 0;
	int exp;
	for (exp = 0; exp < lhs.getBin().size(); exp++) {
		left += lhs.getBin()[exp] * (int)(pow((double)(2), exp));
	}
	for (exp = 0; exp < rhs.getBin().size(); exp++) {
		right += rhs.getBin()[exp] * (int)(pow((double)(2), exp));
	}
	return left < right;
}

bool operator > (const Nimber & lhs, const Nimber & rhs)
// Same as above.
{
	return rhs < lhs;
}