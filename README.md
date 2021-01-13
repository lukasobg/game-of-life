# Conway's Game of Life

I was interested in this simulation as it displays how complex structures appear from a VERY simple  
set of rules and initial state. I decided to build the game myself with C++ and SFML.

# Set up your environment

## Linux

Install the SFML graphics library (make, gcc etc. also required).

    sudo apt-get install libsfml-dev

## Windows

Install an X-server. I found success with VcXsrv and MobaXTerm.

Use WSL to run the program and launch the graphics through the X-server.  
Install the SFML graphics library in WSL (make, gcc etc. also required).

    sudo apt-get install libsfml-dev

You might have to play around with the DISPLAY environment variable.  
Hint: the DISPLAY environment variable is set differently for WSL and WLS2.

# Compiling and running

Build and compile the project with `make main` and run the program with `./main`.
    
The program first asks for some user input in the commandline and then it will launch a graphical window.
    
# Structure of the project directory

The structure of the repository is as follows:

  * `resources/` -- Font file - arial.ttf

  * `src/` -- All C++ source + Makefile

  * `README.md`

# User controls

There are user controls to control the game directly from the window where the game runs.

You can add and remove cells with the left-click of the mouse.  
It is recommended to pause the game during addition/removal.

To customize window size or the number of cells, give input in the commandline, when you run the program.

List of keyboard and mouse shortcuts:

    Mouse:
    left click  - add/remove cell

    Keyboard:
    space          - pause/play
    right arrow    - while paused, advances one step
    R              - reset to a random inital state, pauses game
    C              - clear/kill all cells, pauses game
    Ctrl + [1-9]   - save configuration (current state)
    Shift + [1-9]  - load configuration
    Q              - quit the program


# Classes

## Game of Life

The following classes are used in the actual game.

* **Universe** -- Simulated universe where the cells live.

* **Cell** -- Cell.
   
## Graphics

The following classes are used in the visualization of the game.

* **Graphics** -- Creates an instance of **Universe**, draws it, handles user input,  
    controls the addition of cells and redrawing the state.

The main function of the program creates an instance of **Graphics**.