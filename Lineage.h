#ifndef LINEAGE_H
#define LINEAGE_H

#include "Cell.h"
#include <map>
#include <memory>

#define CELLCOUNTMAX 	128

class Lineage {

protected:
	// cell count
	int size;

	int lineage_idx;

	// birth frame
	int birth;

	// Cell register
	std::map<int, Cell*> cellIdx;

	// vector containing the cells
    std::vector <Cell> cellVect;

public:
	// constructor
	Lineage(int, int, std::vector<std::string>);

	int getSize() {return size;}
	int getBirth() {return birth;}
	std::vector <Cell>* getCells() {return &cellVect;}

	// add new cell to lineage
	void insertCell(std::vector<std::string>);

	// find cell by ID (using register)
	Cell* findCell(int);

};

#endif