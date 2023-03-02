#include "TotalisticCA.h"

#include <math.h>

TotalisticCA::TotalisticCA(unsigned int _rule, unsigned int _radius,
	unsigned int _state, enum Distribution _dist,
	unsigned int _rowcount, unsigned int _cellcount)
  : CellularAutomata(_rule, _radius, _state, _dist, _rowcount, _cellcount),
	rulebook(0x0) {

	// create rulebook
	unsigned int rulesize = pow(2, GetRadius()*2+1);
	unsigned int rule = GetRule();
	rulebook = new unsigned int[rulesize];
	for(unsigned int i=0; i<rulesize; i++) {
		rulebook[i] = rule & (1<<i) ? 1 : 0;
	}

}

TotalisticCA::~TotalisticCA(void) {
}

unsigned int TotalisticCA::Generate() {
	unsigned int radius = GetRadius();
	unsigned int rowcount = GetRowCount();
	unsigned int cellcount = GetCellCount();
	unsigned int *neighborIndex = new unsigned int[radius*2+1];

	if(stepcount == rowcount-1)
		return stepcount;

	for(unsigned int i=0; i<cellcount; i++) {
		for(unsigned int j=radius; j>0; j--) {
			neighborIndex[radius-j] = ((int)(i - j) < 0 ? cellcount - (j - i) : i - j);
			neighborIndex[radius+j] = (i + j >= cellcount ? j - (cellcount - i) : i + j);
		}
		neighborIndex[radius] = i;

		unsigned int mask = 0;
		unsigned int sum = 0;
		for(unsigned int j=0; j<radius*2+1; j++)
			if(grid[stepcount][neighborIndex[j]]) {
				mask |= (unsigned char)(1 << (radius*2-j));
				sum++;
			}
		grid[stepcount+1][i] = (sum > radius) ? rulebook[mask] : 0;
	}

	delete[] neighborIndex;
	return ++stepcount;
}
