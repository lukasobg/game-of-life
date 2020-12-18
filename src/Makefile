CC = g++
CFLAGS  = -g -Wall -I.
DEP = cell.hpp world.hpp graphics.hpp  # all hpp files
OBJ = main.o graphics.o world.o cell.o # all .o files
# all hpp files? TESTDEP = 
# all .o files TESTOBJ = 
GUICFLAGS  = -g -Wall -I. -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJ)
	$(CC) -o $@ $^ $(GUICFLAGS)

# tests.o: tests.cpp $(TESTDEP)
#	$(CC) $(CFLAGS) -c $< -o $@

#tests: $(TESTOBJ)
#	$(CC) -o $@ $^ $(GUICFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(GUIOBJ) $(TESTOBJ) main #gui tests
