#include "ElementaryCA.h"
#include <math.h>

ElementaryCA::ElementaryCA(unsigned int _rule, unsigned int _radius,
	enum Distribution _dist, unsigned int _rowcount, unsigned int _cellcount)
  : CellularAutomata(_rule, _radius, 1, _dist, _rowcount, _cellcount),
	rulebook(0x0) {

	// create rulebook
	unsigned int rulesize = pow(2, GetRadius()*2+1);
	unsigned int rule = GetRule();
	rulebook = new unsigned int[rulesize];
	for(unsigned int i=0; i<rulesize; i++) {
		rulebook[i] = rule & (1<<i) ? 1 : 0;
	}
}

ElementaryCA::~ElementaryCA(void) {

	// delete rulebook
	delete rulebook;
	rulebook = 0x0;
}

unsigned int ElementaryCA::Generate() {
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
		for(unsigned int j=0; j<radius*2+1; j++)
			if(grid[stepcount][neighborIndex[j]])
				mask |= (unsigned char)(1 << (radius*2-j));
		grid[stepcount+1][i] = rulebook[mask];
	}

	delete[] neighborIndex;
	return ++stepcount;
}
