#ifndef __TOTALISTIC_CA_H
#define __TOTALISTIC_CA_H

#include "CellularAutomata.h"

class TotalisticCA : public CellularAutomata {
	public:
		TotalisticCA(unsigned int _rule, unsigned int _radius,
			unsigned int _state,
			enum Distribution _dist, unsigned int _rowcount,
			unsigned int _cellcount);
		virtual ~TotalisticCA(void);

		virtual unsigned int Generate(void);
		
	private:
		TotalisticCA(void);

		unsigned int *rulebook;
};

#endif
