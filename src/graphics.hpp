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

	sf::Vector2f g_pos(int x, int y) const;
	sf::Vector2f g_size() const;
public:

	Graphics() : w_(700), h_(700) { initialize(); }
	~Graphics();

	void initialize();
	void animate();
	void parse_user_input();
	void redraw();
	void quit();

	void add_cell(int i, int j);
	void toggle_cell_at(int click_x, int click_y);
	void toggle_speed(int i);
};