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
    isOldest_ = false;
    birthCount_ = 0;

    mother_ = NULL;
    progenitor_ = NULL;
    d1_ = NULL;
    d2_ = NULL;

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
    //std::cout << "linking cell..." << std::endl;
    setMother(m);
    setPro(p);
    m->setBirthCount();
}

void Cell::initAge(std::string age){
    //std::cout << "intializing age..." << std::endl;
    if(age=="NaN"){
        int a = getMother()->getAge() + 1;
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

void Cell::linkDaughter(){ 
    //std::cout << "linking daughters..." << std::endl;
// if mother cell has two daughters
    if(getMother()->getBirthCount()==1){
        getMother()->setD1(this);
    }
    else{
        getMother()->setD2(this);
        int age = getAge();
        if(getMother()->getD1()->getAge() > age)
        {
            getMother()->getD1()->setOldest();
        }
        else{
            setOldest();
        }
    }
}

void Cell::printCell(int field){
    std::cout << field;
    std::cout << "\t" << getlID();
    std::cout << "\t" << getID();
    std::cout << "\t" << getBirth();
    std::cout << "\t" << getMotherID();
    std::cout << "\t" << getProID();
    std::cout << "\t" << getGrowthRate();
    std::cout << "\t" << getAge();
    std::cout << "\t" << isOldest();
    std::cout << "\t" << getGen() << std::endl;
}