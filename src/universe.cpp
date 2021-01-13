#include "universe.hpp"
#include "cell.hpp"
#include <vector>
#include <iostream>


Universe::~Universe() {
	for (auto cell : cells_) {
		delete cell;
	}
}

bool Universe::is_alive(int idx) {
	return cells_[idx]->is_alive();
}

int Universe::neighbours_alive(int x, int y) const {

	int alive = 0;
	for (int i=-1; i<2; i++) {
		int xi = (x+i+nx_) % nx_;
		for (int j=-1; j<2; j++) {
			int yi = (y+j+ny_) % ny_;
			if (cells_[xi*ny_+yi]->is_alive() && !(xi==x && yi==y)) {
				alive++;
			}
		}
	}
	
	return alive;
}

void Universe::insert(Cell* cell) {
	cells_.push_back(cell);
	cell->set_universe(this);
}

void Universe::set_alive(int idx) {
	cells_[idx]->set_alive();
}

void Universe::set_dead(int idx) {
	cells_[idx]->set_dead();
}

void Universe::set_alive(int x, int y) {
	cells_[x*ny_ + y]->set_alive();
}

void Universe::set_dead(int x, int y) {
	cells_[x*ny_ + y]->set_dead();
}

void Universe::add_glider_gun(int x, int y) {
	set_alive(x,y);
	set_alive(x+1,y+1);
	set_alive(x+1,y+2);
	set_alive(x,y+2);
	set_alive(x-1,y+2);
}


void Universe::update() {
	for (auto cell : cells_) {
		cell->update();
	}
	for (auto cell : cells_) {
		cell->toggle();
	}
}
