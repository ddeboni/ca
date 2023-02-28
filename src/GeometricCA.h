#ifndef __GEOMETRIC_CA_H
#define __GEOMETRIC_CA_H

#include "ElementaryCA.h"

#include <map>

enum SHAPE {
	SHAPE_UNKNOWN = 0,
	SHAPE_TRIANGLE,
	SHAPE_SQUARE,
	SHAPE_PENTAGON,
	SHAPE_HEXAGON,
	SHAPE_SEPTAGON,
	SHAPE_OCTAGON
};

class GeometricCA : private CellularAutomata {
	public:
		GeometricCA(unsigned int _sides, unsigned int _rule, unsigned int _radius,
			enum Distribution _dist, unsigned int _rowcount,
			unsigned int _cellcount);
		virtual ~GeometricCA(void);

		virtual unsigned int Generate(void);
		virtual unsigned int GetCellState(unsigned int _row, unsigned int _col) const;

	private:
		GeometricCA(void);

		std::map<unsigned int, ElementaryCA *> ca;
		unsigned int sides;
};

#endif
