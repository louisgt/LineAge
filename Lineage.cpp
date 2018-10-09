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

std::string Lineage::inOrderNewick(Cell *root){
	std::string label = "";
	int lifespan = 0;
	if(root->getD1()!=NULL){
		std::string output = "";
        output += "(";
        output += inOrderNewick(root->getD1());
        output += ",";
        output += inOrderNewick(root->getD2());
        output += ")";
        output += std::to_string(root->getID());
        output += ":";
        lifespan = (root->getD1()->getBirth()) - root->getBirth();
		output += std::to_string(lifespan);
		output += "[&&NHX:XX=";
		output += std::to_string(root->getAge());
		output += "]";
        return output;
	} else {
		label += std::to_string(root->getID());
		label += ":";
		// if cell has children, we can compute its lifespan
		if(root->getD1()!=NULL){
			lifespan = (root->getD1()->getBirth()) - root->getBirth();
		}
		// else its lifespan is bounded by the end of the timelapse
		else{
			lifespan = 64 - root->getBirth();
		}
		label += std::to_string(lifespan);
		label += "[&&NHX:XX=";
		label += std::to_string(root->getAge());
		label += "]";
        return label;
    }
}
