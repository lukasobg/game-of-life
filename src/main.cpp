#include "graphics.hpp"

/*TODO: Cleanup? Write comments */
int main() {

    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl << "\tGame of Life" << std::endl << "----------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "TL;DR: Enter twice to run with default values" << std::endl << std::endl;
    std::cout << "The graphical program currently only supports:" << std::endl;
    std::cout << "\t square windows: for ex. 700 x 700 pixels" << std::endl;
    std::cout << "\t square universe: for ex. 25 x 25 number of cells" << std::endl;
    std::cout << std::endl;

    std::cout << "The backend simulation, that is the Universe class however does support uneven sized universes:" << std::endl;
    std::cout << "\t for ex. 30 x 50 number of cells" << std::endl;
    std::cout << std::endl;

    std::cout << "Give the follwing inputs as a single integer. Empty input for default values." << std::endl;
    std::cout << std::endl;

    int w_size = 700;
    int n = 25;
    std::cout << "Input window size (default 700 x 700): ";
    
    std::string u_size;
    std::getline( std::cin, u_size );
    if ( !u_size.empty() ) {
        std::istringstream stream(u_size);
        stream >> w_size;
    }

    std::cout << "Input number of cells (default 25 x 25): ";
    
    std::string u_n;
    std::getline( std::cin, u_n);
    if ( !u_n.empty() ) {
        std::istringstream stream(u_n);
        stream >> n;
    }

    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl << "\tGame of Life" << std::endl << "----------------------------" << std::endl;
    std::cout << std::endl;


    Graphics g(w_size,n);
    
    g.animate();


    return 0;
}
