#include "graphics.hpp"

/* Destructor. */
Graphics::~Graphics() {
	for (auto g_cell : g_cells_ ) {
		delete g_cell;
	}
	delete world_;
}

/* Initialize is called in the constructor. It creates a window, initializes the world,
   and randomly sets some cells alive. */
void Graphics::initialize() {
	// Create window
	window_.create(sf::VideoMode(w_, h_), "Game of Life");
	window_.setVerticalSyncEnabled(true);

	// Set world window size
	width_ = 0.9*w_;
	height_ = 0.9*h_;

	// Initialize world
	world_ = new World(45,45);
	int nx = world_->get_nx();
	int ny = world_->get_ny();

	// Add cells to world
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			add_cell(i,j);
		}
	}

	// Initialize empty configurations
	for (int i = 0; i<9; i++) {
		std::vector<int> v = {};
		cells_alive_.push_back(v);
	}
	
	init_default_configurations();

	add_random_cells((nx*ny)/6);
}

// Randomly set some cells alive
void Graphics::add_random_cells(int nr) {
	srand(time(0));
	int x; int y;
	for (int i = 0; i<nr; i++) {
	  	std::uniform_real_distribution<double> u(0,1);
	  	x = (rand() % world_->get_nx());
	  	y = (rand() % world_->get_ny());
	  	world_->set_alive(x, y);
	}
}

/* Clears the world, i.e. kills all cells. */ 
void Graphics::clear() {
	paused_ = true;

	for (auto cell : world_->get_cells()) {
		cell->set_dead();
	}
}
/* Adds a cell to the world and creates a graphical cell. */
void Graphics::add_cell(int i, int j) {
	Cell* cell = new Cell(i, j);
	world_->insert(cell);

	// Create graphical shapes for cells
	sf::RectangleShape* g_cell = new sf::RectangleShape();
	g_cell->setSize(g_size());
	g_cell->setPosition(g_pos(i,j));
	g_cell->setFillColor(sf::Color::Black);
	g_cell->setOutlineColor(sf::Color::Black);
	g_cell->setOutlineThickness(1.5);
	g_cells_.push_back(g_cell);
}

void Graphics::save_configuration(int nr) {
	cells_alive_[nr].clear();
	for (auto cell : world_->get_cells() ) {
		if (cell->is_alive()) {
			cells_alive_[nr].push_back(1);
		} else {
			cells_alive_[nr].push_back(0);
		}
	}

	std::cout << "Saved configuration " << nr+1 << "." << std::endl;
}

void Graphics::load_configuration(int nr) {

	if (cells_alive_[nr].size() < 2) {
		std::cout << "No configuraion: " << nr+1 << std::endl;
	} else {

		paused_ = true;

		int i = 0;
		for (auto cell : world_->get_cells() ) {
			if (cells_alive_[nr][i] == 1) {
				cell->set_alive();
			} else {
				cell->set_dead();
			}
			i++;
		}

		std::cout << "Loading configuration " << nr+1 << "." << std::endl;
	}
}

/* This function contains the loop that is run as long as the 
   window is open. Calls user input parsing and drawing functions.
   Also takes care of the speed of the simulation, based on realtime. */ 
void Graphics::animate(void) {

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

/* Parses user input. Check readme for clear instructions. */
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

          	else if (event.key.code == sf::Keyboard::Right) {
          		if (paused_) {
          			world_->update();
          		}
          	}

          	else if (event.key.code == sf::Keyboard::C) {
          		clear();
          	}

          	else if (event.key.code == sf::Keyboard::R) {
          		paused_ = true;
          		clear();
          		add_random_cells((world_->get_ny()*world_->get_ny())/6);
          	}

          	else if ( event.key.shift && event.key.code > sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 ) {
          		if (paused_) save_configuration(event.key.code-sf::Keyboard::Num0-1);
          	}

          	else if (event.key.code > sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 ) {
          		load_configuration(event.key.code-sf::Keyboard::Num0-1);
          	}

          	else if (event.key.code == sf::Keyboard::Q) {
          		window_.close();
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
/* Toggles, i.e. kills a live cell,  */
void Graphics::toggle_cell_at(int click_x, int click_y) {
	int idx = 0;
	for (auto g_cell : g_cells_) {
		auto bounds = g_cell->getGlobalBounds();

		if (bounds.contains(click_x,click_y)) {
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

	double gx = x_start + unit_x * x + 3 ;
	double gy = y_start + unit_y * y + 3 ;

	return sf::Vector2f(gy, gx);
}

sf::Vector2f Graphics::g_size() const {
	double unit_x = ( width_ / world_->get_nx() ) - 3;
	double unit_y = ( height_ / world_->get_ny() ) - 3;
	return sf::Vector2f(unit_x, unit_y);
}

void Graphics::redraw() {

	// Always redraw, only update back end game of life if sim not paused
	if (!paused_) {
	    world_->update();
	}

	window_.clear();
	
	draw_texts();

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

void Graphics::draw_texts() {
	// Load font
	sf::Font font;
  	font.loadFromFile("../resources/arial.ttf");
  	// Track speed, draws font in lower right corner
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
    
    // Paused
    sf::Text msg2;
    msg2.setFont(font);
    msg2.setCharacterSize(16);
    msg2.setFillColor(sf::Color::White);
    msg2.setPosition(w_-260, h_-20);
    std::string s2 = "PAUSED";
    msg2.setString(s2);
    if (paused_) window_.draw(msg2);
}

void Graphics::toggle_speed(int i) {
	if (i == 1) {
		step_length_ = std::max(step_length_*0.8, 20000.0);
	} else {
		step_length_ = std::min(step_length_*1.2, 500000.0);
	}
}


void Graphics::init_default_configurations() {

}
