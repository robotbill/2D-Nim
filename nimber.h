#ifndef _NIMBER_H
#define _NIMBER_H
#include <string>
using namespace std;

#include <vector.h>

class Nimber
{
	public:
		Nimber();						// Default constructor makes 0
		Nimber(int num);				// Constructor
		Nimber::Nimber(const Nimber & nim); // create from other Nimber
		
		// assignment
		
		const Nimber & operator = (const Nimber & rhs);
		
		// accessors
		
		const vector<int> & getBin() const;	// get reverse binary represention
		
		string toString() const;		// Converts Nimber to a  string
		
		// operators
		
		const Nimber & operator += (const Nimber & nim); // add two nimbers
	
	private:
		vector<int> myNimber;			// Storage for binary version.
};

ostream & operator << (ostream & os, const Nimber & nim);

Nimber operator + (const Nimber & lhs, const Nimber & rhs);

bool operator == (const Nimber & lhs, const Nimber & rhs);
bool operator != (const Nimber & lhs, const Nimber & rhs);

// The following are for sorting purposes only.  Nimbers are normally 
// confused with different nimbers.
bool operator < (const Nimber & lhs, const Nimber & rhs); 
bool operator > (const Nimber & lhs, const Nimber & rhs);

#endif