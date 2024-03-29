#include "graphics.hpp"

// Constructors

Graphics::~Graphics() {
	for (auto g_cell : g_cells_ ) {
		delete g_cell;
	}
	//delete universe_; universe deleted in destruction of cells?
}

// Currently copy constructor and assignment recreate
// a universe and g_cells, instead of copying them over
Graphics::Graphics(const Graphics& g) {
	window_w_ = g.get_window_width();
	n_cells_ = g.get_nr_of_cells();
	initialize();
}

Graphics& Graphics::operator=(const Graphics& g) {
	window_w_ = g.get_window_width();
	n_cells_ = g.get_nr_of_cells();

	for (auto g_cell : g_cells_) {
		delete g_cell;
	}

	initialize();
	return *this;
}

// Initialize is called in the constructor. It creates a window, initializes the universe,
// and randomly sets some cells alive.
void Graphics::initialize() {
	window_.create(sf::VideoMode(window_w_, window_w_), "Game of Life");
	window_.setVerticalSyncEnabled(true);

	// Set universe graphical size
	game_w_ = 0.9 * window_w_;

	// Initialize universe ()
	universe_ = new Universe(n_cells_,n_cells_);
	int nx = universe_->get_nx();
	int ny = universe_->get_ny();
	// Add cells to universe
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			add_cell(i,j);
		}
	}

	// Initialize empty configurations 1-9
	for (int i = 0; i<9; i++) {
		std::vector<int> v = {};
		cells_alive_.push_back(v);
	}
	if ( nx == 25 && ny == 25) {
		init_default_configurations();
	}
	add_random_cells((nx*ny)/6);
}

// Randomly set some cells alive
void Graphics::add_random_cells(int nr) {
	srand(time(0));
	int x; int y;
	for (int i = 0; i<nr; i++) {
	  	std::uniform_real_distribution<double> u(0,1);
	  	x = (rand() % universe_->get_nx());
	  	y = (rand() % universe_->get_ny());
	  	universe_->set_alive(x, y);
	}
}

// Clears the universe, i.e. kills all cells.
void Graphics::clear() {
	paused_ = true;

	for (auto cell : universe_->get_cells()) {
		cell->set_dead();
	}
}

// Adds a cell to the universe and creates a graphical cell. 
void Graphics::add_cell(int i, int j) {
	Cell* cell = new Cell(i, j);
	universe_->insert(cell);

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
	for (auto cell : universe_->get_cells() ) {
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
		for (auto cell : universe_->get_cells() ) {
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

// This function runs as long as the window is open. 
// Calls user input parsing and drawing functions.
// Also takes care of the speed of the simulation, based on realtime.
void Graphics::render() {

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

// Parses user input. Check readme for clear instructions.
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
          			universe_->update();
          		}
          	}

          	else if (event.key.code == sf::Keyboard::C) {
          		clear();
          	}

          	else if (event.key.code == sf::Keyboard::R) {
          		paused_ = true;
          		clear();
          		add_random_cells((universe_->get_ny()*universe_->get_ny())/6);
          	}

          	else if ( event.key.control && event.key.code > sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 ) {
          		save_configuration(event.key.code-sf::Keyboard::Num0-1);
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
// Toggles, i.e. kills a live cell at position of mouse click
void Graphics::toggle_cell_at(int click_x, int click_y) {
	int idx = 0;
	for (auto g_cell : g_cells_) {
		auto bounds = g_cell->getGlobalBounds();

		if (bounds.contains(click_x,click_y)) {
			if (!universe_->is_alive(idx)) {
				universe_->set_alive(idx);
				redraw();
			} else {
				universe_->set_dead(idx);
				redraw();
			}
		}
		idx++;
	}
}

sf::Vector2f Graphics::g_pos(int x, int y) const {
	double unit_x = game_w_ / universe_->get_ny(); // 1/4 * width_
	double x_start = (window_w_ - game_w_) / 2;			// 0.5

	double gx = x_start + unit_x * x + 3;		// 0.5 + 
	double gy = x_start + unit_x * y + 3;
	return sf::Vector2f(gx, gy);
}

sf::Vector2f Graphics::g_size() const {
	double y = ( game_w_ / universe_->get_ny() ) - 3;
	return sf::Vector2f(y,y);
}

void Graphics::redraw() {

	// Always redraw, only update back end game of life if sim not paused
	if (!paused_) {
	    universe_->update();
	}

	window_.clear();
	
	draw_texts();

	// Redraw cells
	int i = 0;
	for ( auto cell : universe_->get_cells() ) {

		if (cell->is_alive() ) {
			g_cells_[i]->setFillColor(sf::Color::White);
			window_.draw(*(g_cells_[i]));
		} else if (cell->state_changed() && !cell->is_alive()) {
			g_cells_[i]->setFillColor(sf::Color::Black);
			window_.draw(*(g_cells_[i]));
		}
		i++;
	}

	window_.display();
	
}

void Graphics::draw_texts() {
	// Load font
	sf::Font font;
  	font.loadFromFile("../resources/arial.ttf");
  	// Track speed, draws font in lower right corner
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(18);
    msg.setFillColor(sf::Color::White);
    msg.setPosition(window_w_ - 150, window_w_ - 30);
    std::stringstream ss;
    double percentage = (1 - (step_length_ - 20000.0) / (20000.0+500000.0)) * 100;
    ss << "Speed: " << std::setprecision(1) << std::fixed << percentage << "%.";
    std::string s = ss.str();
    msg.setString(s);
    window_.draw(msg);
    
    // Paused
    sf::Text msg2;
    msg2.setFont(font);
    msg2.setCharacterSize(18);
    msg2.setFillColor(sf::Color::White);
    msg2.setPosition(window_w_ - 260, window_w_ - 30);
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

	int nx = universe_->get_nx();
	int ny = universe_->get_ny();

	// fill configs 0-2 with dead cells
	for (int i = 0; i < nx*ny; i++ ) {
		cells_alive_[0].push_back(0);
		cells_alive_[1].push_back(0);
		cells_alive_[2].push_back(0);
		cells_alive_[3].push_back(0);
		cells_alive_[4].push_back(0);
	}

	// add live cells to configs 0-2 from file
	std::ifstream conf;
	conf.open("default_states.txt");
	int i; int j;

	while (conf >> i >> j && i != -1) cells_alive_[0][i*nx+j] = 1;
	while (conf >> i >> j && i != -1) cells_alive_[1][i*nx+j] = 1;
	while (conf >> i >> j && i != -1) cells_alive_[2][i*nx+j] = 1;
	while (conf >> i >> j && i != -1) cells_alive_[3][i*nx+j] = 1;
	while (conf >> i >> j && i != -1) cells_alive_[4][i*nx+j] = 1;
    
	std::cout << std::endl;
	std::cout << "Launching program with default settings..." << std::endl;
	std::cout << "Default configurations 1-5 set" << std::endl;
	std::cout << std::endl;
}