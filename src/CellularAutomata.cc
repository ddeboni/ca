#include "CellularAutomata.h"

#include <cstdlib>
#include <iostream>

using namespace std;

CellularAutomata::CellularAutomata(unsigned int _rule,	unsigned int _radius,
	unsigned int _state, enum Distribution _dist,
	unsigned int _rowcount, unsigned int _cellcount)
  : grid(0x0), stepcount(0), rule(_rule), radius(_radius), state(_state), dist(_dist),
	rowcount(_rowcount), cellcount(_cellcount) {

	// initialize cell grid
	grid = new unsigned int*[rowcount];
	for(unsigned int i=0; i<rowcount; i++) {
		grid[i] = new unsigned int[cellcount];
		for(unsigned int j=0; j<cellcount; j++)
			grid[i][j] = 0;
	}

	// seed initial distribution (generation 0)
	InitState();
}

CellularAutomata::~CellularAutomata(void) {
	// delete cell grid
	for(unsigned int i=0; i<rowcount; i++) {
		delete grid[i];
		grid[i] = 0x0;
	}
	delete grid;
	grid = 0x0;
}

void CellularAutomata::InitState(void) {
	switch(dist) {
		case DIST_POINT:
			grid[0][cellcount/2] = state;
			break;
		case DIST_UNIFORM:
			for(unsigned int i=0; i<cellcount; i++)
				grid[0][i] = rand() % 2;
			break;
		default:
			break;
	}
}

unsigned int CellularAutomata::GenerateAll(void) {
	return Generate(GetRowCount());
}

unsigned int CellularAutomata::Generate(unsigned int _steps) {
    	for(unsigned int i=0; i<_steps; i++)
		Generate();

	return stepcount;
}

unsigned int CellularAutomata::GetCellState(unsigned int _row, unsigned int _col) const {
	if(_row < rowcount && _col < cellcount)
		return grid[_row][_col];

	cerr << "Error - Index out of bounds" << endl;
	return -1;
}

void CellularAutomata::PrintState(void) {
	for(unsigned int i=0; i<cellcount; i++)
		cout << (grid[stepcount][cellcount-1-i] ? "*" : " ");
	cout << endl;
}

void CellularAutomata::PrintGrid(void) {
	for(unsigned int i=0; i<rowcount; i++) {
		for(unsigned int j=0; j<cellcount; j++) {
			cout << grid[i][cellcount-1-j] << " ";
		}
		cout << endl;
	}
}
