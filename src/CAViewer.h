#ifndef __CA_VIEWER_H
#define __CA_VIEWER_H

class CAViewer {
	public:
		CAViewer(const class CellularAutomata *_ca,
			unsigned int _cellsize = 10, bool _lines = true);
		virtual ~CAViewer(void);

		void Run(void);

	private:
		void InitDisplay(void);
		void LoadGrid(void);
		CAViewer(void);

		const class CellularAutomata *ca;
};

#endif
