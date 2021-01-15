#include "cell.hpp"

// Constructors

Cell::Cell(int x, int y) {
	x_ = x;
	y_ = y;
	alive_ = false;
}

Cell::~Cell() {
	delete universe_;
}

Cell::Cell(const Cell& c) {
	x_ = c.x();
	y_ = c.y();
	alive_ = c.is_alive();
	universe_ = c.get_universe();
}

Cell& Cell::operator=(const Cell& c) {
	x_ = c.x();
	y_ = c.y();
	alive_ = c.is_alive();
	delete universe_;
	universe_ = c.get_universe();
	return *this;
}

// Update state function, changes the cells state according to the rules
void Cell::update() {
	
	int a = universe_->neighbours_alive(x_,y_);

	if (is_alive()) {
		if ( a < 2 || a > 3 ) {
			next_ = false;
		} else {
			next_ = true;
		}
	} else {
		if (a == 3) {
			next_ = true;
		} else {
			next_ = false;
		}
	}

	changed_ = (alive_ != next_) || next_;
}
