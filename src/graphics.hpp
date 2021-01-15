#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "universe.hpp"
#include "cell.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <sstream>

class Universe;

class Graphics {
private:
	sf::RenderWindow window_;
	Universe* universe_;
	int window_w_;  // width of window
	int game_w_;	// width of graphical universe
	int n_cells_;
	std::vector<sf::Shape*> g_cells_;

	bool paused_ = true;
	double step_length_ = 100000.0;
	std::vector<std::vector<int>> cells_alive_;

	// Count graphical size and position
	sf::Vector2f g_pos(int x, int y) const;
	sf::Vector2f g_size() const;
public:
	// Constructors, destructor, copy constructor, copy assignment
	Graphics() : window_w_(700), n_cells_(25)  { initialize(); }
	Graphics(int w_size, int n) : window_w_(w_size), n_cells_(n)  { initialize(); }
	~Graphics();
	Graphics(const Graphics& g);
	Graphics& operator=(const Graphics& g);

	// Getters (only used in copy constructor, copy assignment)
	int get_window_width() const { return window_w_; };
	int get_nr_of_cells() const { return n_cells_; };
	Universe* get_universe() const { return universe_; };
	std::vector<sf::Shape*> get_g_cells() const { return g_cells_; }

	// These functions draw, update and run the graphical universe
	// main functions
	void initialize();
	void render();
	void parse_user_input();
	void redraw();
	void draw_texts();

	// helper functions
	void add_random_cells(int nr);
	void clear();
	void add_cell(int i, int j);
	void toggle_cell_at(int click_x, int click_y);
	void toggle_speed(int i);
	void save_configuration(int nr);
    void load_configuration(int nr);
    void init_default_configurations();
};