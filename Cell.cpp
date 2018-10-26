#include "Cell.h"

Cell::Cell(std::vector<std::string> elements, int idx, bool isProg)
{
    // parse known values
    lID_ = idx;
    ID_ = std::stoi(elements[0]);
    //std::cout << "ID is " << ID_ << std::endl;
    birth_ = std::stoi(elements[1]);
    //std::cout << "birth is " << birth_ << std::endl;
    death_ = (int)std::stod(elements[2],NULL);
    birthLen_ = std::stoi(elements[4]);
    //std::cout << "birth len is " << birthLen_ << std::endl;
    deathLen_ = std::stoi(elements[5]);
    //std::cout << "death len is " << deathLen_ << std::endl;
    motherID_ = std::stoi(elements[6]);
    //std::cout << "mother ID is " << motherID_ << std::endl;
    dist_ = std::stod(elements[7],NULL);
    //std::cout << "dist is " << dist_ << std::endl;
    proID_ = std::stoi(elements[8]);
    //std::cout << "pro is " << proID_ << std::endl;
    growthRate_ = std::stod(elements[9],NULL);
    //std::cout << "gr is " << growthRate_ << std::endl;
    //std::cout << "death is " << death_ << std::endl;
    
    isProgenitor_ = isProg;
    isOldest_ = false;
    birthCount_ = 0;
    // lifespan defaults to NaN, to avoid 0s at end of timelapse
    lifespan_ = std::numeric_limits<double>::quiet_NaN();
    if(death_!=birth_)
    {
        lifespan_ = death_ - birth_;
    }

    mother_ = NULL;
    progenitor_ = NULL;
    d1_ = NULL;
    d2_ = NULL;

    // is this cell a progenitor?
    if(isProg){
        // progenitor is its own mother
        motherID_ = ID_;
    }

    generation_ = 0;
    oldPoleAge_ = 0;
    divAge_ = 0;
}

void Cell::linkCell(Cell* m, Cell* p){
    //std::cout << "linking cell..." << std::endl;
    //std::cout << "set mother cell..." << std::endl;
    setMother(m);
    //std::cout << "set pro cell..." << std::endl;
    setPro(p);
    //std::cout << "set birth count..." << std::endl;
    m->setBirthCount();
}

void Cell::initAge(std::string age){
    //std::cout << "intializing age..." << std::endl;
    if(age=="NaN"){
        //cell is possibly oldest sibling (TBD when linking)
        
        //int a = getMother()->getAge() + 1;
        int a = 0;
        setAge(a);
    }
    // else assign given value
    else{
        int a = std::stoi(age) - 1;
        setAge(a);
    }
    // generation is assigned relative to mother
    int g = getMother()->getGen() + 1;
    setGen(g);
}

void Cell::linkDaughter(){ 
    //std::cout << "linking daughters..." << std::endl;
    // if mother cell has two daughters
    if(getMother()->getBirthCount()==1){
        getMother()->setD1(this);
        //getMother()->setLifespan(this->getBirth()-getMother()->getBirth());
    }
    else{
        getMother()->setD2(this);
        // set proper age of both daughters

        int age = getAge();
        int m = getMother()->getAge() + 1;
        int d = getMother()->getDivAge() + 1;

        if(age==0){
            // if both siblings have age 0: most likely result of first division
            if(getMother()->getD1()->getAge()==0){
                // assign old pole of 1 to each
                setAge(1);
                getMother()->getD1()->setAge(1);
                setDivAge(1);
                getMother()->getD1()->setDivAge(1);
                setOldest();
                getMother()->getD1()->setOldest();
            }
            // if present cell has age 0 but sibling > 0, then present is oldest
            else{
                // add to successive old pole divisions
                setOldest();
                setAge(m);
            }
        }
        else{
            // else if both cells have age > 0 and sibling is older
            // OR if sibling has age 0
            if(getMother()->getD1()->getAge()>age || getMother()->getD1()->getAge()==0)
            {
                // sibling is oldest
                getMother()->getD1()->setOldest();
                getMother()->getD1()->setAge(m);
            }
            // else present cell is oldest
            else{
                setOldest();
                setAge(m);
            }
        }
        // SET NO OF DIVISIONS BASED ON STATUS OF MOTHER (OLD/NEW)
        // if present cell is the oldest, record its number of consecutive old pole divs
        if(isOldest())
        {
            if(getMother()->isOldest())
            {
                setDivAge(d);
                getMother()->getD1()->setDivAge(1);
            }
            else
            {
                setDivAge(1);
                getMother()->getD1()->setDivAge(d);
            }
        }
        // else sibling is oldest
        else
        {
            if(getMother()->isOldest())
            {
                getMother()->getD1()->setDivAge(d);
                setDivAge(1);
            }
            else{
                getMother()->getD1()->setDivAge(1);
                setDivAge(d);
            }
        }
    }
}

void Cell::printCell(int field, int exp){
    std::cout << exp;
    std::cout << "\t" << field;
    std::cout << "\t" << getlID();
    std::cout << "\t" << getID();
    std::cout << "\t" << getBirth();
    std::cout << "\t" << getMotherID();
    std::cout << "\t" << getProID();
    std::cout << "\t" << getGrowthRate();
    std::cout << "\t" << getLifespan();
    std::cout << "\t" << getAge();
    std::cout << "\t" << getDivAge();
    std::cout << "\t" << isOldest();
    std::cout << "\t" << getGen();
    std::cout << "\t" << getBLen();
    std::cout << "\t" << getDLen();
    std::cout << "\t" << getDist() << std::endl;
}