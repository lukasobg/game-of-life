#pragma once
#include <vector>

class Cell;

class Universe {
private:
	// All cells that live in the universe
	std::vector<Cell*> cells_;

	// Number of rows and columns of cells in the universe
	int nx_;
	int ny_;

public:
	// Constructors, destructor, copy constructor, copy assignment
	Universe(int nx, int ny) : nx_(nx), ny_(ny) { }
	Universe() { Universe(100,100); }
	~Universe();
	Universe(const Universe& u);
	Universe& operator=(const Universe& u);

	// Getters
	const std::vector<Cell*>& get_cells() const { return cells_; }
	int get_nx() const { return nx_; }
	int get_ny() const { return ny_; }
	bool is_alive(int idx) const;
	
	// Setters
	void set_alive(int idx);
	void set_dead(int idx);
	void set_alive(int x, int y);
	void set_dead(int x, int y);

	int neighbours_alive(int x, int y) const;
	void insert(Cell* cell);
	void add_glider_gun(int x, int y);
	void update();
};