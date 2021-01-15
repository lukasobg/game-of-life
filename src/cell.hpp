#pragma once
#include <vector>
#include "universe.hpp"

class Cell {
private:
	// position
	int x_;
	int y_;

	// state
	bool alive_ = false;
	bool next_ = false;

	// helps detect which cells to redraw
	bool changed_ = false;

	// universe where cell lives
	Universe* universe_;
	
public:
	// Constructor, destructor, copy constructor, copy assignment
	Cell(int x, int y);
	~Cell();
	Cell(const Cell& c);
	Cell& operator=(const Cell& c);

	// Getters
	int x() const { return x_; }
	int y() const { return y_; }
	Universe* get_universe() const { return universe_; };
	bool is_alive() const { return alive_; }
	bool state_changed() const { return changed_; }

	// Setters
	void set_universe(Universe* u) { universe_ = u; };
	void set_alive() { alive_ = true; }
	void set_dead() { alive_ = false; }
	void toggle() { alive_ = next_; }
	void update();
};