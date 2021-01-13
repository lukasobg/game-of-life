# TODO: write tests? clean?

CC = g++
CFLAGS  = -g -Wall -I.
DEP = cell.hpp universe.hpp graphics.hpp
OBJ = main.o graphics.o universe.o cell.o
GUICFLAGS  = -g -Wall -I. -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJ)
	$(CC) -o $@ $^ $(GUICFLAGS)



# TESTDEP = 
# TESTOBJ = 

# tests.o: tests.cpp $(TESTDEP)
#	$(CC) $(CFLAGS) -c $< -o $@

#tests: $(TESTOBJ)
#	$(CC) -o $@ $^ $(GUICFLAGS)

#.PHONY: clean

#clean:
#	rm -f $(OBJ) $(GUIOBJ) main
