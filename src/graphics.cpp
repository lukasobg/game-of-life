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
	world_ = new World(30,30);
	int nx = world_->get_nx();
	int ny = world_->get_ny();

	// Add cells to world
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			add_cell(i,j);
		}
	}
	
	// Randomly set some cells alive
	srand(time(0));
	int x; int y;
	for (int i = 0; i< (nx*ny)/5; i++) {
	  	std::uniform_real_distribution<double> u(0,1);
	  	x = (rand() % nx);
	  	y = (rand() % ny);
	  	world_->set_alive(x, y);
	}
	
	
	
	// GLIDER GUN
	//world_->add_glider_gun(1,1);
	//world_->add_glider_gun(1,8);
}

void Graphics::add_cell(int i, int j) {
	Cell* cell = new Cell(i, j);
	world_->insert(cell);

	// Create graphical shapes for cells
	sf::RectangleShape* g_cell = new sf::RectangleShape();
	g_cell->setSize(g_size());
	g_cell->setPosition(g_pos(i,j));
	g_cell->setFillColor(sf::Color::Black);
	g_cells_.push_back(g_cell);
}


void Graphics::animate(void) {
	std::cout << "Animating..." << std::endl;

	// initial draw
	redraw();

	// timer for speed
	clock_t t2 = clock();
	clock_t t1 = clock();


    int i = 0;
	while (window_.isOpen()) {
		parse_user_input();
		
		t2 = clock();
		if((t2-t1) > step_length_) {
			redraw();
		  	i++;
		  	t1 = clock(); t2 = clock();
		}
	}
}

void Graphics::parse_user_input() {
    sf::Event event;
    while (window_.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window_.close();
        }

        if (event.type == sf::Event::KeyPressed) {

        	if (event.key.code == sf::Keyboard::Space) {
          		paused_ = !paused_;
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
    			int click_x = event.mouseButton.x;
            	int click_y = event.mouseButton.y;
            	toggle_cell_at(click_x, click_y);
    		}
        }
    }
}

void Graphics::toggle_cell_at(int click_x, int click_y) {
	int idx = 0;
	for (auto g_cell : g_cells_) {
		auto bounds = g_cell->getLocalBounds();
		if (bounds.contains(sf::Vector2f(click_x,click_y))) {
			std::cout << "Click in bounds:";
			if (!world_->is_alive(idx)) {
				world_->set_alive(idx);
				redraw();
			} else {
				world_->set_dead(idx);
				redraw();
			}
		}
		idx++;
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

	// Always redraw, only update back end game of life if sim not paused
	if (!paused_) {
	    world_->update();
	}

	window_.clear();

	// Track speed, draws font in lower right corner
	sf::Font font;
  	font.loadFromFile("../resources/arial.ttf");
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(16);
    msg.setFillColor(sf::Color::White);
    msg.setPosition(w_-150, h_-20);
    std::stringstream ss;
    double percentage = (1 - (step_length_ - 20000.0) / (20000.0+500000.0)) * 100;
    ss << "Speed: " << std::setprecision(1) << std::fixed << percentage << "%.";
    std::string s = ss.str();
    msg.setString(s);
    window_.draw(msg);
	
	// Redraw cells
	int i = 0;
	for ( auto cell : world_->get_cells() ) {

		if (cell->is_alive() ) {
			g_cells_[i]->setFillColor(sf::Color::White);
			window_.draw(*(g_cells_[i]));
		} else if (cell->state_changed() && !cell->is_alive()) {
			g_cells_[i]->setFillColor(sf::Color::Black);
			window_.draw(*(g_cells_[i]));
		}
		i++;
	}
	//window_.draw(*border_);


	window_.display();
	
}

void Graphics::toggle_speed(int i) {
	if (i == 1) {
		step_length_ = std::max(step_length_*0.8, 20000.0);
	} else {
		step_length_ = std::min(step_length_*1.2, 500000.0);
	}
}

void Graphics::quit() {
	
}