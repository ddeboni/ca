#ifndef __CELLULAR_AUTOMATA_H
#define __CELLULAR_AUTOMATA_H

enum Distribution {
	DIST_UNKNOWN = 0,
	DIST_POINT,
	DIST_UNIFORM,
	DIST_GAUSSIAN,
	DIST_POISSON
};

enum RuleType {
	RULE_UNKNOWN = 0,
	RULE_ELEMENTARY,
	RULE_TOTALISTIC
};

class CellularAutomata {
	public:
		CellularAutomata(unsigned int _rule, unsigned int _radius,
			unsigned int _state,
			enum Distribution _dist, unsigned int _rowcount,
			unsigned int _cellcount);
		virtual ~CellularAutomata(void);

		unsigned int GenerateAll(void);
		unsigned int Generate(unsigned int _steps);
		virtual unsigned int Generate(void) = 0;
		
		virtual unsigned int GetCellState(unsigned int _row, unsigned int _col) const;
		bool IsDone() const { return stepcount == rowcount-1; }

		void PrintState(void);
		void PrintGrid(void);

	protected:
		friend class CAViewer;
		unsigned int GetRule(void) const { return rule; }
		unsigned int GetRadius(void) const { return radius; }
		unsigned int GetState(void) const { return state; }
		unsigned int GetDistribution(void) const { return dist; }

		unsigned int GetRowCount(void) const { return rowcount; }
		unsigned int GetCellCount(void) const { return cellcount; }
		unsigned int GetStepCount(void) const { return stepcount; }
		
		unsigned int **grid;
		unsigned int stepcount;

	private:
		void InitState(void);
		CellularAutomata(void);

		unsigned int rule;
		unsigned int radius;
		unsigned int state;
		enum Distribution dist;

		unsigned int rowcount;
		unsigned int cellcount;
};

#endif
