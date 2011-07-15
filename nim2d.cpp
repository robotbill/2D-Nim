#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#include <list.h>

#include "matrix.h"
#include "nimber.h"
#include "hash.h"

/*
 * Program to play 2-D Nim.
 * July 13, 2005
 * Joe Lewis
 */

Nimber newGame(Matrix & game, Hashtable & table, Hashtable & moves, int prime);
void printFile(Hashtable & table);

int main()
{
	cout << "Welcome to 2-D Nim (h for help)" << endl;
	Matrix game;
	Nimber value;
	int prime = 11;
	Hashtable table = prime;
	Hashtable moves = prime;
	// Initialize hash table w/ 0 game
	for ( ; ; ) {
		cout << "prompt> ";
		char command;
		cin >> command;
		switch (command) {
			case 'h':
				cout << "h\t\tShow options" << endl;
				cout << "n\t\tEnter a new game" << endl;
				cout << "p\t\tPrint normalized form of current game" << endl;
				cout << "v\t\tPrint the value of the current game" << endl;
				cout << "a\t\tPrint solved games and values" << endl;
				cout << "w\t\tWrite solved games and valuse to file" << endl;
				cout << "m\t\tPrint winning moves" << endl;
				
				cout << "q\t\tquit" << endl;
				break;
			case 'q':
				return 0;
			case 'n':
				value = newGame(game, table, moves, prime);
				break;
			case 'p':
				game.print();
				break;
			case 'v':
				cout << value << endl;
				break;
			case 'a':
				table.print();
				break;
			case 'w':
				printFile(table);
				break;
			case 'm':
				cout << "Best move(s):" << endl;
				moves.print();
				break;
		}
	}
}

void printFile(Hashtable & table)
{
	cout << "Enter file name: ";
	string file;
	cin >> file;
	table.printToFile(file);
}
