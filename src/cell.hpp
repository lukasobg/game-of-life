#pragma once
#include <vector>
#include "world.hpp"


class Cell {
private:
	int x_;
	int y_;
	bool alive_ = false;
	bool next_ = false;
	bool changed_ = false;
	World* world_;
	
public:
	Cell(int x, int y);
	~Cell();

	int x() const { return x_; }
	int y() const { return y_; }

	void set_world(World* w);
	bool is_alive() { return alive_; }
	bool state_changed() { return changed_; }
	void set_alive() { alive_ = true; }
	void toggle() { alive_ = next_; }
	void update();
};