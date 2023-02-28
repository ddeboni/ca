#include "ElementaryCA.h"
#include "TotalisticCA.h"
#include "CAViewer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	
	unsigned int rule = 18;
	unsigned int nr = 1;
	unsigned int state = 1;
	enum RuleType type = RULE_ELEMENTARY;
	enum Distribution dist = DIST_POINT;
	unsigned int height = 16;
	unsigned int width = 32;
	unsigned int cellsize = 40;
	unsigned int zoom = 1;
	bool grid = true;

	int opt;
	while((opt = getopt(argc, argv, "r:n:s:t:d:z:c:g")) != -1) {
		switch(opt) {
			case 'r':
				rule = atoi(optarg);
				break;
			case 'n':
				nr = atoi(optarg);
				break;
			case 's':
				state = atoi(optarg);
				break;
			case 't':
				if(strcmp(optarg, "elementary") == 0)
					type = RULE_ELEMENTARY;
				else if(strcmp(optarg, "totalistic") == 0)
					type = RULE_TOTALISTIC;
				else {
					printf("Error - Unsupported rule type\n");
					exit(-1);
				}
				break;
			case 'd':
				if(strcmp(optarg, "point") == 0)
					dist = DIST_POINT;
				else if(strcmp(optarg, "uniform") == 0)
					dist = DIST_UNIFORM;
				else if(strcmp(optarg, "gaussian") == 0)
					dist = DIST_GAUSSIAN;
				else if(strcmp(optarg, "poisson") == 0)
					dist = DIST_POISSON;
				else {
					printf("Error - Unsupported rule type\n");
					exit(-1);
				}
				break;
			case 'z':
				zoom = atoi(optarg);
				break;
			case 'c':
				cellsize = atoi(optarg);
				break;
			case 'g':
				grid = false;
				break;
			default:
				printf("Usage - %s [-r <rule>] [-n <neighbor radius>]\n", argv[0]);
				printf("           [-s <state>] [-t <ca type>]\n");
				printf("           [-d <initial distribution>]\n");
				printf("           [-z <zoom>] [-c <cellsize>] [-g]\n");
				exit(-1);
		}
	}

	CellularAutomata *ca = 0x0;
	CAViewer *view = 0x0;
 
	switch(type) {
		case RULE_ELEMENTARY:
			ca = new ElementaryCA(rule, nr, dist, height*zoom, width*zoom);
			break;
		case RULE_TOTALISTIC:
			ca = new TotalisticCA(rule, nr, state, dist, height*zoom, width*zoom);
			break;
		default:
			printf("Error - Unsupported rule type\n");
			exit(-1);
	}

#ifdef STEP_DEBUG	
	ca->PrintState();
	while(ca->IsDone() == false) {
		ca->Generate();
		ca->PrintState();
	}
#else
	ca->GenerateAll();
#endif

	view = new CAViewer(ca, cellsize/zoom, grid);
	view->Run();
	
	delete view;
	view = 0x0;

	delete ca;
	ca = 0x0;

	return 0;
}

