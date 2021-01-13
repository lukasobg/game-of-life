#pragma once
#include <vector>

class Cell;

/* TODO: write comments. RO3*/
class Universe {
private:
	std::vector<Cell*> cells_;
	int nx_;
	int ny_;

public:
	Universe(int nx, int ny) : nx_(nx), ny_(ny) { }
	Universe() { Universe(100,100); }
	~Universe();

	const std::vector<Cell*>& get_cells() { return cells_; }
	int get_nx() const { return nx_; }
	int get_ny() const { return ny_; }
	bool is_alive(int idx);
	int neighbours_alive(int x, int y) const;
	void insert(Cell* cell);
	void set_alive(int idx);
	void set_dead(int idx);
	void set_alive(int x, int y);
	void set_dead(int x, int y);
	void add_glider_gun(int x, int y);
	void update();
};