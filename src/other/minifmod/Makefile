# ============================================================================
#  Makefile for Linux version of MiniFMOD test player
# ============================================================================

# = LIBRARY DEFINITIONS ======================================================

LIBPATH  = ./lib/linux
LIB      = $(LIBPATH)/libminifmod.a
SRCPATH  = ./src
INCPATH  = ./include

# = CORE DEFINITIONS =========================================================

CFLAGS   = -s -Os -c -I$(INCPATH) -D__LINUX__ -Wall 
LFLAGS   = -s  -L$(LIBPATH) -lminifmod -lpthread -lm 

# = MAKEFILE =================================================================

test :
	gcc $(LFLAGS) -o test main.cpp

