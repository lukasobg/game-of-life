#include "graphics.hpp"


Graphics::~Graphics() {
	for (auto g_cell : g_cells_ ) {
		delete g_cell;
	}
	delete world_;
}

void Graphics::initialize() {
	// Create window
	window_.create(sf::VideoMode(w_, h_), "Game of Life");
	window_.setVerticalSyncEnabled(true);

	// Set world window size
	width_ = 0.9*w_;
	height_ = 0.9*h_;

	// Draw border
	/*
	border_ = new sf::RectangleShape();
	border_->setSize(sf::Vector2f(width_,height_));
	border_->setPosition(sf::Vector2f((w_-width_) / 2.0, (h_-height_) / 2.0));
	border_->setOutlineThickness(1.f);
	border_->setOutlineColor(sf::Color::White);
	*/

	// Initialize world
	world_ = new World(50,50);
	int nx = world_->get_nx();
	int ny = world_->get_ny();

	// Add cells to world
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			Cell* cell = new Cell(i, j);
			world_->insert(cell);

			// Create graphical shapes for cells
			sf::RectangleShape* g_cell = new sf::RectangleShape();
			g_cell->setSize(g_size());
			g_cell->setPosition(g_pos(i,j));
			g_cell->setFillColor(sf::Color::Black);
			g_cells_.push_back(g_cell);
		}
	}
	
	// Randomly set some cells alive
	
	srand(time(0));
	int x; int y;
	for (int i = 0; i< (nx*ny)/4; i++) {
	  	std::uniform_real_distribution<double> u(0,1);
	  	x = (rand() % nx);
	  	y = (rand() % ny);
	  	world_->set_alive(x, y);
	}
	
	
	// GLIDER GUN
	//world_->add_glider_gun(1,1);
	//world_->add_glider_gun(1,8);
}


void Graphics::animate(void) {
	std::cout << "Animating..." << std::endl;

	clock_t t2 = clock();
	clock_t t1 = clock();


	// timer
	std::clock_t start;
    double duration;
    double sum;

    start = std::clock();

    int i = 0; int c = 0;
	while (window_.isOpen()) {
		t2 = clock();
		if((t2-t1) > step_length_) {
		    parse_user_input();
		    redraw();
		    if (i % 3 == 0 && i != 0) {
		  		duration = ( std::clock()-start) / (double) CLOCKS_PER_SEC;
		  		sum += duration;
	    		std::cout << "3 steps duration: " << duration << std::endl;
	    		c++;
	    		start = std::clock();
		    }
		  	i++;
		  	t1 = clock(); t2 = clock();
		}
	}
	double average = sum / (double)c;
	std::cout << "Average: " << average << std::endl;

    
}

void Graphics::parse_user_input() {
    sf::Event event;
    while (window_.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window_.close();
        }

        if (event.type == sf::Event::KeyPressed) {

        	if (event.key.code == sf::Keyboard::Space) {
          		//world_->update();
          		//redraw();
          	}

          	else if (event.key.code == sf::Keyboard::Up) {
          		toggle_speed(1);
          	}

          	else if (event.key.code == sf::Keyboard::Down) {
          		toggle_speed(0);
          	}
        }

        if (event.type == sf::Event::MouseButtonPressed) {
    		if (event.mouseButton.button == sf::Mouse::Left) {
    		}
        }
    }
}

sf::Vector2f Graphics::g_pos(int x, int y) const {
	double unit_x = height_ / world_->get_nx();
	double unit_y = width_ / world_->get_ny();
	double x_start = (w_-width_) / 2;
	double y_start = (h_-height_) / 2;

	double gx = x_start + unit_x * x + 5;
	double gy = y_start + unit_y * y + 5;

	return sf::Vector2f(gy, gx);
}

sf::Vector2f Graphics::g_size() const {
	double unit_x = ( width_ / world_->get_nx() ) - 5;
	double unit_y = ( height_ / world_->get_ny() ) - 5;
	return sf::Vector2f(unit_x, unit_y);
}

void Graphics::redraw() {
	world_->update();

	window_.clear();
	
	int i = 0;
	for ( auto cell : world_->get_cells() ) {

		if (cell->state_changed()) {
			if (cell->is_alive() ) {
				g_cells_[i]->setFillColor(sf::Color::White);
			} else {
				g_cells_[i]->setFillColor(sf::Color::Black);
			}
			window_.draw(*(g_cells_[i]));
		}
		i++;
	}
	//window_.draw(*border_);
	window_.display();
	
}

void Graphics::toggle_speed(int i) {
	if (i == 1) {
		step_length_ = std::max(step_length_*0.7, 20000.0);
	} else {
		step_length_ = std::min(step_length_*1.3, 300000.0);
	}
}

void Graphics::quit() {
	
}