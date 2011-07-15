#include <list.h>

#include "matrix.h"
#include "nimber.h"
#include "hash.h"

void checkRows(Matrix & game, Hashtable & table, Hashtable & moves, int prime, list<Nimber> & nimlist, int call);
void checkCols(Matrix & game, Hashtable & table, Hashtable & moves, int prime, list<Nimber> & nimlist, int call);

Nimber mex(list<Nimber> & nimlist)
// Pre: nimlist is a list of Nimbers
// Post: applies the mex rule to nimlist and returns a Nimber
{
	nimlist.sort();
	nimlist.unique();
	int size = nimlist.size();
	int i;
	for (i = 0; i < size; i++) {
		Nimber nimcheck = i;
		if (nimlist.front() != nimcheck) return nimcheck;
		nimlist.pop_front();
	}
	Nimber retval = i;
	return retval;
	
}


Nimber findValue(Matrix & game, Hashtable & table, Hashtable & moves, int prime, int call)
// Pre: game is a game, table is a hash table with prime lists
// Post: checks all possible moves and returns value of game.
{
	list<Nimber> nimlist;
	Nimber v;
	Nimber zero;

	if (table.lookup(game, v) == 0 && call != 0) { 
	//Check if we've already found the value for this game if so return value
	// except for the original game.  Look for possible moves so we can 
	// find the optimal move.
		if (v == zero && call == 1) moves.add(game.hash(prime), game, v);
		return v;
	}
	if (game.sum() == 0) {  // zero games have a value of zero!
		return zero;
	} else {	// haven't seen the game and not all zeros so check moves
		game.print();  // print for user feedback
		checkRows(game, table, moves, prime, nimlist, call);	//check the rows first
		checkCols(game, table, moves, prime, nimlist, call);	// then check the columns
	}
	v = mex(nimlist);	// find the value of the nimlist
	if (table.lookup(game, v) != 0) {	// Make sure the game hasn't been solved
		table.add(game.hash(prime), game, v); // Since the game was new add it to
	}										  // the hash table
	// Add the winning moves to the moves table.
	if (v == zero && call == 1) moves.add(game.hash(prime), game, v);
	return v;
}

void checkRows(Matrix & game, Hashtable & table, Hashtable & moves, int prime, list<Nimber> & nimlist, int call)
// Check the value of the possible moves from each row in game.
{
	int rowindex;
	int colindex;
	int doneflag;
	if (call == 0 || call == 1) call++;
	for (rowindex = 0; rowindex < game.rows(); rowindex++) { //for each row.
		int rowsum = 0;
		vector<int> rowvector(game.cols());
		for (colindex = 0; colindex < game.cols(); colindex++) {
		// copy row to vector for checking if we're finished.
			rowvector[colindex] = game[rowindex][colindex];
			rowsum += rowvector[colindex];
		}
		if (rowsum == 0) continue; // Row is already all 0s, Nothing to subtract
		for (colindex = 0; colindex < game.cols(); colindex++) {
			game[rowindex][colindex] = 0;  // set zero row
		}
		nimlist.push_front(findValue(game, table, moves, prime, call)); 
											// find the value of the game
											// with 0's in the row.
		for ( ; ; ) {
			doneflag = 1;
			for (colindex = 0; colindex < game.cols(); colindex++) {
				if (game[rowindex][colindex] == rowvector[colindex] &&
						colindex != game.cols() - 1) {
					// We've reached the maximum of a non-last colum so
					// rollover and go to next column
					game[rowindex][colindex] = 0;
					continue;
				}
				if (game[rowindex][colindex] < rowvector[colindex] &&
						   colindex == game.cols() - 1) {
					// Haven't reached the maximum for the last column
					// so increment it.
					game[rowindex][colindex]++;
					break;
				}
				if (game[rowindex][colindex] == rowvector[colindex] &&
						colindex == game.cols() - 1) {
					// We've reached the max for the last column so we're done
					break;		
				}
				if (game[rowindex][colindex] < rowvector[colindex]) {
					// haven't reached the max for this column yet so increment
					game[rowindex][colindex]++;
					break;
				}
			}
			for (colindex = 0; colindex < game.cols(); colindex++) {
				if (game[rowindex][colindex] != rowvector[colindex]) {
				// Check for stopping condition.
					doneflag = 0;
					break;
				}
			}
			if (doneflag == 1) break;
			// check value of new position.
			nimlist.push_front(findValue(game, table, moves, prime, call));
		}
		for (colindex = 0; colindex < game.cols(); colindex++) {
		// copy vector back to row.
			game[rowindex][colindex] = rowvector[colindex];
		}
	}
}

void checkCols(Matrix & game, Hashtable & table, Hashtable & moves, int prime, list<Nimber> & nimlist, int call)
{
	int rowindex;
	int colindex;
	int doneflag;
	if (call == 0 || call == 1) call++;
	for (colindex = 0; colindex < game.cols(); colindex++) { //Check columns
		int colsum = 0;
		vector<int> colvector(game.rows());
		for (rowindex = 0; rowindex < game.rows(); rowindex++) {
		// copy column to vector for checking
			colvector[rowindex] = game[rowindex][colindex];
			colsum += colvector[rowindex];
		}
		if (colsum == 0) continue; //Nothing to subtract;
		for (rowindex = 0; rowindex < game.rows(); rowindex++) {
			game[rowindex][colindex] = 0;  // set zero column
		}
		nimlist.push_front(findValue(game, table, moves, prime, call));
		
		for ( ; ; ) {
			doneflag = 1;
			for (rowindex = 0; rowindex < game.rows(); rowindex++) {
				if (game[rowindex][colindex] == colvector[rowindex] &&
						rowindex != game.rows() - 1) {
					game[rowindex][colindex] = 0;
					continue;
				}
				if (game[rowindex][colindex] < colvector[rowindex] &&
						rowindex == game.rows() - 1) {
					game[rowindex][colindex]++;
					break;
				}
				if (game[rowindex][colindex] == colvector[rowindex] &&
						rowindex == game.rows() - 1) {
					break;		
				}
				if (game[rowindex][colindex] < colvector[rowindex]) {
						game[rowindex][colindex]++;
					break;		
				}
			}
			for (rowindex = 0; rowindex < game.rows(); rowindex++) {
				if (game[rowindex][colindex] != colvector[rowindex]) {
					doneflag = 0;
					break;
				}
			}
			if (doneflag == 1) break;
			nimlist.push_front(findValue(game, table, moves, prime, call));
		}
		for (rowindex = 0; rowindex < game.rows(); rowindex++) {
		// copy vector back to column.
			game[rowindex][colindex] = colvector[rowindex];
		}
	}
}