#ifndef __OUTERTOTALISTIC_CA_H
#define __OUTERTOTALISTIC_CA_H

#include "TotalisticCA.h"

class OuterTotalisticCA : public TotalisticCA {
	public:
		OuterTotalisticCA(unsigned int _rule, unsigned int _radius,
			unsigned int _state,
			enum Distribution _dist, unsigned int _rowcount,
			unsigned int _cellcount);
		virtual ~OuterTotalisticCA(void);

		virtual unsigned int Generate(void);
		
	private:
		OuterTotalisticCA(void);

		unsigned int *rulebook;
};

#endif
