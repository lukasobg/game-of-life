CC = g++ 

CFLAGS  = -std=c++20 -g -Wall -I/opt/homebrew/Cellar/sfml/2.5.1_2/include # macOS
#CFLAGS  = -std=c++20 -g -Wall  # others

DEP = cell.hpp universe.hpp graphics.hpp
OBJ = main.o graphics.o universe.o cell.o

GUICFLAGS  = -g -Wall -I. -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system # macOS
#GUICFLAGS  = -g -Wall -I. -lsfml-graphics -lsfml-window -lsfml-system # others

%.o: %.cpp $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

main: $(OBJ)
	$(CC) -o $@ $^ $(GUICFLAGS)



# Tests and clean for future implementation

# TESTDEP = 
# TESTOBJ = 

# tests.o: tests.cpp $(TESTDEP)
#	$(CC) $(CFLAGS) -c $< -o $@

#tests: $(TESTOBJ)
#	$(CC) -o $@ $^ $(GUICFLAGS)

#.PHONY: clean

#clean:
#	rm -f $(OBJ) $(GUIOBJ) main
