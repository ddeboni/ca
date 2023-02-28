#include "GeometricCA.h"

using namespace std;

GeometricCA::GeometricCA(unsigned int _sides, unsigned int _rule, unsigned int _radius,
	enum Distribution _dist, unsigned int _rowcount, unsigned int _cellcount)
 : CellularAutomata(_rule, _radius, 1, _dist, _rowcount*3, _cellcount*3),
	sides(_sides) {

	for(unsigned int i=0; i<sides; i++)
		ca[i] = new ElementaryCA(_rule, _radius, _dist, _rowcount, _cellcount);
}

GeometricCA::~GeometricCA(void) {

	for(map<unsigned int, ElementaryCA *>::iterator iter = ca.begin(); iter != ca.end(); iter++) {
		delete iter->second;
		iter->second = 0x0;
	}

	ca.clear();
}

unsigned int GeometricCA::Generate() {

	for(map<unsigned int, ElementaryCA *>::iterator iter = ca.begin(); iter != ca.end(); iter++) {
		iter->second->Generate();
	}
	return ++stepcount;
}

unsigned int GeometricCA::GetCellState(unsigned int _row, unsigned int _col) const {

	return 0;
}
