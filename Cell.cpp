#include "Cell.h"

Cell::Cell(std::vector<std::string> elements, int idx, bool isProg)
{
    // parse known values
    lID_ = idx;
    ID_ = std::stoi(elements[0]);
    birth_ = std::stoi(elements[1]);
    motherID_ = std::stoi(elements[3]);
    proID_ = std::stoi(elements[4]);
    growthRate_ = std::stod(elements[5],NULL);
    isProgenitor_ = isProg;

    mother_ = NULL;
    progenitor_ = NULL;

    // is this cell a progenitor?
    if(isProg){
        // generation 0
        // old pole is initialized to age 1
        motherID_ = getID();
        generation_ = 0;
        oldPoleAge_ = 1;
    }
    else{
        generation_ = 0;
        oldPoleAge_ = 0;
    }
}

void Cell::linkCell(Cell* m, Cell* p){
    setMother(m);
    setPro(p);
}

void Cell::initAge(std::string age){
    if(age=="NaN"){
        int a = getMother()->getAge();
        setAge(a);
    }
    // else assign given value
    else{
        int a = std::stoi(age);
        setAge(a);
    }  
    int g = getMother()->getGen() + 1;
    setGen(g);
}

void Cell::printCell(){
    std::cout << "My ID is " << getID() << std::endl;
    //std::cout << "My birth is " << getBirth() << std::endl;
    std::cout << "My mother ID is " << getMotherID() << std::endl;
    std::cout << "My progenitor ID is " << getProID() << std::endl;
    std::cout << "My lineage ID is " << getProID() << std::endl;
    std::cout << "My growth rate is " << getGrowthRate() << std::endl;
    std::cout << "My age is " << getAge() << std::endl;
    std::cout << "My generation is " << getGen() << std::endl;
}