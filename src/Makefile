SRCS =	CAViewer.cc \
	ElementaryCA.cc \
	TotalisticCA.cc \
	OuterTotalisticCA.cc \
	GeometricCA.cc \
	CellularAutomata.cc \
	ca.cc

OBJS = $(subst .cc,.o,$(SRCS))

CC = g++
DEBUG = -g

OS := $(shell uname)
ifeq ($(OS), Linux)
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = $(DEBUG) -lglut -lGLU -lGL
else
CFLAGS = -Wall -c $(DEBUG) -DMAC_OS -DGL_SILENCE_DEPRECATION
LFLAGS = $(DEBUG) -framework OpenGL -framework GLUT
endif

ca: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ../ca

CAViewer.o: CAViewer.cc CAViewer.h
	$(CC) $(CFLAGS) -c CAViewer.cc 

ElementaryCA.o: ElementaryCA.cc ElementaryCA.h
	$(CC) $(CFLAGS) -c ElementaryCA.cc 

TotalisticCA.o: TotalisticCA.cc TotalisticCA.h
	$(CC) $(CFLAGS) -c TotalisticCA.cc 

OuterTotalisticCA.o: OuterTotalisticCA.cc OuterTotalisticCA.h
	$(CC) $(CFLAGS) -c OuterTotalisticCA.cc 

GeometricCA.o: GeometricCA.cc GeometricCA.h
	$(CC) $(CFLAGS) -c GeometricCA.cc 

CellularAutomata.o: CellularAutomata.cc CellularAutomata.h
	$(CC) $(CFLAGS) -c CellularAutomata.cc ca.cc

all:	ca

clean:
	rm -f *.o *~ ../ca


