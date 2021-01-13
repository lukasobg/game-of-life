#include "cell.hpp"

Cell::Cell(int x, int y) {
	x_ = x;
	y_ = y;
	alive_ = false;
}

Cell::~Cell() {
	//delete universe_;
}

void Cell::set_universe(Universe* u) {
	universe_ = u;
}

void Cell::update() {
	
	int a = universe_->neighbours_alive(x_,y_);

	if (is_alive()) {

		if( a < 2 || a > 3) {
			next_= false;
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