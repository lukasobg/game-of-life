#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "world.hpp"
#include "cell.hpp"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <sstream>

class World;


/* Graphics class. This class contains the graphics for our simulation. */
class Graphics {
private:
	sf::RenderWindow window_;
	World* world_;
	int w_; // width of window
	int h_;
	int width_;	// width of graphical world
	int height_;
	std::vector<sf::Shape*> g_cells_;
	sf::RectangleShape* border_;

	bool paused_ = true;
	double step_length_ = 100000.0;
	std::vector<std::vector<int>> cells_alive_;

	sf::Vector2f g_pos(int x, int y) const;
	sf::Vector2f g_size() const;
public:

	Graphics() : w_(800), h_(800) { initialize(); }
	~Graphics();

	void initialize();
	void animate();
	void parse_user_input();
	void redraw();
	void draw_texts();

	void add_random_cells(int nr);
	void clear();
	void add_cell(int i, int j);
	void toggle_cell_at(int click_x, int click_y);
	void toggle_speed(int i);
	void save_configuration(int nr);
    void load_configuration(int nr);
    void init_default_configurations();
};