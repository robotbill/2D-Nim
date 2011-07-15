#include "matrix.h"
#include "nimber.h"
#include "hash.h"

Nimber findValue(Matrix & game, Hashtable & table, Hashtable & moves, int prime, int call);


Nimber newGame(Matrix & game, Hashtable & table, Hashtable & moves, int prime)
{
	cout << "Enter the number of rows: ";
	int numrows;
	cin >> numrows;
	
	cout << "Enter the number of columns: ";
	int numcols;
	cin >> numcols;
	
	game.resize(numrows, numcols);
	
	int rowindex,colindex;
	for (rowindex = 0; rowindex < numrows; rowindex++) {
		cout << "Enter row " << rowindex << ": ";
		for (colindex = 0; colindex < numcols; colindex++) {
			cin >> game[rowindex][colindex];
		}
	}
	cout << "You entered: " << endl;
	game.print();
	cout << "which normalizes to: " << endl;
	game.normalize();
	game.print();
	cout << endl;
	moves.clear();
	return findValue(game, table, moves, prime, 0);
}