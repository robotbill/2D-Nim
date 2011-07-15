#ifndef _HASH_H
#define _HASH_H

#include <vector.h>
#include "matrix.h"
#include "nimber.h"

struct GameNode {
	Nimber value;
	Matrix game;
	GameNode *next;
	GameNode(const Matrix & g, const Nimber & n, GameNode * link)
		: value(n),
		  game(g),
		  next(link)
	{
	}
};

class Hashtable
{
	public:
		Hashtable();			// creates a hash table of w/ 1 list.
		Hashtable(int size);	// creates a hash table of size lists
		
		void add(int hash, const Matrix game, const Nimber & nim);	// Add game
																	// table
		const int lookup(const Matrix & g, Nimber & nim) const;	// find a game
		void print() const;						// Print
		void printToFile(string file) const;	// Print to file
		void clear();			// Clear the list
		
	private:
		vector<GameNode*> myTable;	// vector of lists
};

#endif