#pragma once
#include <vector>
#include "universe.hpp"


/*TODO: Add comments:
Destructor? RO3? */
class Cell {
private:
	int x_;
	int y_;
	bool alive_ = false;
	bool next_ = false;
	bool changed_ = false;
	Universe* universe_;
	
public:
	Cell(int x, int y);
	~Cell();

	int x() const { return x_; }
	int y() const { return y_; }

	void set_universe(Universe* u);
	bool is_alive() { return alive_; }
	bool state_changed() { return changed_; }
	void set_alive() { alive_ = true; }
	void set_dead() { alive_ = false; }
	void toggle() { alive_ = next_; }
	void update();
};