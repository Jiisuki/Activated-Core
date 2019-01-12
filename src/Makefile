# ============================================================================
#  Makefile for Activated Core
# ============================================================================

# = LIBRARY DEFINITIONS ======================================================

LIBPATH  = ./lib
#LIB      = $(LIBPATH)/minifmod.lib
LIB      = $(LIBPATH)/libfmodex.so
SRCPATH  = ./
INCPATH  = ./include

# = CORE DEFINITIONS =========================================================

CFLAGS   = -s -Os -c -I$(INCPATH) -D__LINUX__ -Wall 
#LFLAGS   = -s  -lX11 -lglut -lGL -lGLU -lm -L$(LIBPATH) -lminifmod -lpthread
LFLAGS   = -s  -lX11 -lglut -lGL -lGLU -lm -L$(LIBPATH) lib/libfmodex.so -lpthread

# = MAKEFILE =================================================================

test : $(LIB) main.o
	g++ main.cpp $(LFLAGS) -o ../activate
	
main.o : main.cpp
	g++ $(CFLAGS) $<
