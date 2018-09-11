#include "Lineage.h"

// utility function
// splits a string by delimiter and returns element vector
std::vector<std::string> split(const std::string &s, char delim){
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item));
    }
    return elems;
}

std::shared_ptr<Lineage> findLineage(std::map<int, std::shared_ptr<Lineage>> lm, int ID){
	auto search = lm.find(ID);
    if (search != lm.end()) {
        return search->second;
    } else return NULL;
}

int main(int argc, char *argv[]) {

	// top level structure: LINEAGE MAP
	// every progenitor cell constitutes a new lineage
	// the key is the cell ID (int) and its corresponding value is a pointer to the Lineages
    std::map<int, std::shared_ptr<Lineage>> LineageMap;

    // initialize cell array

    int cellcount = std::stoi(argv[2]);
    int cell_ctr = 1;
    int l_ctr = 0;


    std::cout << "Considering " << cellcount << " first cells." << std::endl;

    //open cell list
    std::cout << "Opening cell list ..." << std::endl;
    std::ifstream infile(argv[1]);
    std::string line;
    // discard header
    std::getline(infile, line);
    do
    {
        std::getline(infile, line);
        std::vector<std::string> celldata = split(line,',');  

        // check progenitor ID
        int proID = std::stoi(celldata[4]);

        // does it exist in the map?
        std::shared_ptr<Lineage> pLin = findLineage(LineageMap,proID);

        // yes: create and insert new cell in corresponding lineage
        if(pLin){
        	pLin->insertCell(celldata);
        }
        // no: create new lineage and insert its progenitor cell
        else{
        	int birthf = std::stoi(celldata[1]);
        	// insert lineage
        	l_ctr++;
			LineageMap.emplace(proID, std::make_shared<Lineage>(birthf,l_ctr,celldata));
        }

        cell_ctr++;
    }while(cell_ctr < cellcount);

    for(auto it = LineageMap.begin(); it != LineageMap.end(); ++it)
    {
	    int key = it->first;
	    std::shared_ptr<Lineage> l = it->second;
	    if(l->getSize() < 7){
	    	continue;
	    }
	    std::cout << "#@@# Printing lineage of size " << l->getSize() << std::endl;
	    for(auto cell_it = l->getCells()->begin(); cell_it!= l->getCells()->end(); ++cell_it)
	    {
	    	(*cell_it).printCell();
	    }
    }

    return 0;
}
