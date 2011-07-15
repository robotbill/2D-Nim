#include <fstream>
#include <iostream>
using namespace std;
#include <vector.h>

#include "hash.h"
#include "matrix.h"
#include "nimber.h"

Hashtable::Hashtable()
// Initialize hash table with just one list
		: myTable(1)
{
	myTable[0] = 0;
}

Hashtable::Hashtable(int size)
// Initialize hash table with size lists
		: myTable(size)
{
	int i;
	for (i = 0; i < size; i++) {
		myTable[i] = 0;
	}
}

void Hashtable::add(int hash, const Matrix g, const Nimber & nim)
// Pre: 0 <= Hash < myTable.size(), g is a game, nim is its value
// Post: Range checked for hash index, adds game and value to the table
{
	if (hash < 0 || hash >= myTable.size()) {
		cerr << "Illegal Hash index: " << hash << " max index = ";
		cerr << myTable.size() - 1 << endl;
		exit(1);
	}
	Matrix game = g;
	game.normalize();
	myTable[hash] = new GameNode(game, nim, myTable[hash]);
}

void Hashtable::print() const
// Prints out all entries in table to standard out
{
	int i;
	for (i = 0; i < myTable.size(); i++) {
		GameNode * temp;
		for (temp = myTable[i]; temp != 0; temp = temp -> next) {
			cout << "Game:" << endl;
			temp->game.print();
			cout << "Value: " << temp->value << endl << endl;
		}
	}
}

void Hashtable::clear()
{
	int i;
	for (i = 0; i < myTable.size(); i++) {
		GameNode * temp;
		while (myTable[i] != 0) {
			temp = myTable[i]->next;
			delete myTable[i];
			myTable[i] = temp;
		}
	}
}

void Hashtable::printToFile(string file) const
// Prints all entries in table to file file
{
	ofstream output;
	output.open(file.c_str());
	int i;
	for (i = 0; i < myTable.size(); i++) {
		GameNode * temp;
		for (temp = myTable[i]; temp != 0; temp = temp -> next) {
			output << "Game:" << endl;
			temp->game.printTo(output);
			output << "Value: " << temp->value << endl << endl;
		}
	}
}

const int Hashtable::lookup(const Matrix & game, Nimber & nim) const
// Pre: game is a game, nim is a Nimber
// Post: Search table for game, if game is found return 0 and store
//       the value for the game in nim.  Else return -1.
{
	Matrix g = game;
	g.normalize();
	int i;
	for (i = 0; i < myTable.size(); i++) {
		GameNode * temp;
		for (temp = myTable[i]; temp !=0; temp = temp -> next) {
			if (g == temp->game) {
				nim = temp->value;
				return 0;
			}
		}
	}
	return -1;
}