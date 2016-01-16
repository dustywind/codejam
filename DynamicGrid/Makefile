
CC          = g++
CFLAGS      = -g -pedantic -Wall -std=c++11
IDIR        = -I.

OBJ         = grid.o

RM          = rm -f

.PHONY: all

all: dg ;

dg: dg.cpp $(OBJ) ; \
    $(CC) $(CFLAGS) $(IDIR) -o $@ $^ ; \
    cp ./dg ./test/

grid.o: grid.cpp grid.h; \
    $(CC) -c $(CFLAGS) $(IDIR) -o $@ grid.cpp

clean: ; \
    $(RM) $(OBJ) dg
