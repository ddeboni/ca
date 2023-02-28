#ifndef __ELEMENTARY_CA_H
#define __ELEMENTARY_CA_H

#include "CellularAutomata.h"

class ElementaryCA : public CellularAutomata {
	public:
		ElementaryCA(unsigned int _rule, unsigned int _radius,
			enum Distribution _dist, unsigned int _rowcount,
			unsigned int _cellcount);
		virtual ~ElementaryCA(void);

		virtual unsigned int Generate(void);
		
	private:
		ElementaryCA(void);

		unsigned int *rulebook;
};

#endif
