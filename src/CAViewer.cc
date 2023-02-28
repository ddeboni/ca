#include "CAViewer.h"
#include "CellularAutomata.h"

#ifdef MAC_OS
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>

static unsigned int gridheight = 0;
static unsigned int gridwidth = 0;
static unsigned int **grid = 0x0;
static bool lines = true;

static unsigned int cellstate = 0;
static unsigned int cellsize = 0;
static float xpos = -0.5f;
static float ypos = -0.5f;
static float zoom = 1.0f;

static void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glScalef(zoom, zoom, 1.0f);
	glTranslatef(xpos, ypos, -1.5f);

	glBegin(GL_QUADS);
	for(unsigned int i=0; i<gridheight; i++) {
		for(unsigned int j=0; j<gridwidth; j++) {
			if(grid[i][j]) {
				glColor3f(1.0f-(float)grid[i][j]/cellstate,
					  1.0f-(float)grid[i][j]/cellstate,
					  1.0f-(float)grid[i][j]/cellstate);

				glVertex3f((float)j/gridwidth, 1.0f-(float)i/gridheight, 0.0f);
				glVertex3f((float)(j+1)/gridwidth, 1.0f-(float)i/gridheight, 0.0f);
				glVertex3f((float)(j+1)/gridwidth, 1.0f-(float)(i+1)/gridheight, 0.0f);
				glVertex3f((float)j/gridwidth, 1.0f-(float)(i+1)/gridheight, 0.0f);
			}
		}
	}
	glEnd();

	if(lines) {
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);

		for(unsigned int i=0; i<=gridheight; i++) {
			glVertex3f(0.0f, (float)i/gridheight, 0.0f);
			glVertex3f(1.0f, (float)i/gridheight, 0.0f);
		}

		for(unsigned int i=0; i<=gridwidth; i++) {
			glVertex3f((float)i/gridwidth, 0.0f, 0.0f);
			glVertex3f((float)i/gridwidth, 1.0f, 0.0f);
		}
		glEnd();
	}

	glutSwapBuffers();
}

static void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
		case 27:
			exit(0);
			break;
		case '=':
		case '+':
			zoom += 0.1f;
			break;
		case '-':
			zoom -= 0.1f;
			break;
		case 'g':
		case 'l':
			lines = !lines;
			break;
		default:
			break;
	}
}

static void Special(int key, int x, int y) {

	float mod = 1.0f;
	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		mod = 0.1f;

	switch(key) {
		case GLUT_KEY_LEFT:
			xpos += mod*0.1f;
			break;
		case GLUT_KEY_RIGHT:
			xpos -= mod*0.1f;
			break;
		case GLUT_KEY_UP:
			ypos -= mod*0.1f;
			break;
		case GLUT_KEY_DOWN:
			ypos += mod*0.1f;
			break;
		case GLUT_KEY_HOME:
			xpos = -0.5f;
			ypos = -0.5f;
			zoom = 1.0f;
			lines = false;
			break;
		case GLUT_KEY_END:
			exit(0);
			break;
		case GLUT_KEY_PAGE_UP:
			zoom -= mod*0.1f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			zoom += mod*0.1f;
			break;
		case GLUT_KEY_INSERT:
			lines = !lines;
			break;
		default:
			break;
	}
}

CAViewer::CAViewer(const CellularAutomata *_ca, unsigned int _cellsize, bool _lines)
  : ca(_ca) {
	cellsize = _cellsize;
	lines = _lines;

	InitDisplay();
}

CAViewer::~CAViewer(void) {
	if(grid) {
		for(unsigned int i=0; i<ca->GetRowCount(); i++) {
			delete grid[i];
			grid[i] = 0x0;
		}
		delete grid;
		grid = 0x0;
	}
}

void CAViewer::InitDisplay(void) {
	int argc = 0;

	gridwidth = ca->GetCellCount();
	gridheight = ca->GetRowCount();
	cellstate = ca->GetState();

	glutInit(&argc, 0x0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(gridwidth*cellsize, gridheight*cellsize);
	glutCreateWindow("Cellular Automata Viewer");
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, gridwidth*cellsize, gridheight*cellsize);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CAViewer::LoadGrid(void) {
	grid = new unsigned int*[ca->GetRowCount()];
	for(unsigned int i = 0; i < ca->GetRowCount(); i++) {
		grid[i] = new unsigned int[ca->GetCellCount()];
		for(unsigned int j = 0; j < ca->GetCellCount(); j++) {
			grid[i][j] = ca->GetCellState(i, j);
		}
	}
}

void CAViewer::Run(void) {
	LoadGrid();
	glutMainLoop();
}

