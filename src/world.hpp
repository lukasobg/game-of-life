#pragma once
#include <vector>
//#include "cell.hpp"

class Cell;

class World {
private:
	std::vector<Cell*> cells_;
	int nx_;
	int ny_;

public:
	World(int nx, int ny) : nx_(nx), ny_(ny) { }
	World() { World(100,100); }
	~World();

	const std::vector<Cell*>& get_cells() { return cells_; }
	int get_nx() const { return nx_; }
	int get_ny() const { return ny_; }
	int neighbours_alive(int x, int y) const;
	void insert(Cell* cell);
	void set_alive(int x, int y);
	void add_glider_gun(int x, int y);
	void update();
};