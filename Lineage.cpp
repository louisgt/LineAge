#include "Lineage.h"

Lineage::Lineage(int birthframe, int idx, std::vector<std::string> elements){

	cellVect.reserve(CELLCOUNTMAX);

	birth = birthframe;

	lineage_idx = idx;

	//std::cout << "Lineage constructor: new lineage born at frame " << birth << std::endl;

	// push back first cell (progenitor)
	cellVect.emplace_back(elements,lineage_idx,true);

	// get progenitor address
	Cell* last = &cellVect.back();

	// update register
	cellIdx.emplace(last->getID(), last);

	// update size
	size = 1;
}

void Lineage::insertCell(std::vector<std::string> elements){

	cellVect.emplace_back(elements,lineage_idx,false);
	
	// get inserted cell address
	Cell* last = &cellVect.back();

	int mid = last->getMotherID();
	int pid = last->getProID();

	// get pointers
	Cell* m = findCell(mid);
	Cell* p = findCell(pid);

	last->linkCell(m,p);
	last->initAge(elements[2]);
	last->linkDaughter();

	// update register
	cellIdx.emplace(last->getID(), last);

	// update size
	size++;
}

Cell* Lineage::findCell(int ID){
	auto search = cellIdx.find(ID);
    if (search != cellIdx.end()) {
        return search->second;
    } else return NULL;
}
