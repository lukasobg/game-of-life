#include "world.hpp"
#include "cell.hpp"
#include <vector>
#include <iostream>


World::~World() {
	for (auto cell : cells_) {
		delete cell;
	}
}

int World::neighbours_alive(int x, int y) const {

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

void World::insert(Cell* cell) {
	cells_.push_back(cell);
	cell->set_world(this);
}

void World::set_alive(int x, int y) {
	cells_[x*ny_ + y]->set_alive();
}

void World::add_glider_gun(int x, int y) {
	set_alive(x,y);
	set_alive(x+1,y+1);
	set_alive(x+1,y+2);
	set_alive(x,y+2);
	set_alive(x-1,y+2);
}


void World::update() {
	for (auto cell : cells_) {
		cell->update();
	}
	for (auto cell : cells_) {
		cell->toggle();
	}
}
