#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

// Class Declaration

class Cell {

public:
    Cell();


private:
    
    // cell ID
    // birth frame
    // generation relative to progenitor
    // mother cell (reference)
    // progenitor
    // old pole age
    // growth rate
};


void constructLineage(){
    // Declaring Vector of String type 
    std::vector<std::string> celldata;
    // read lines one by one
    //while (!cell_in.eof()) {
        //const std::string line = getline();
        //celldata = split(line,',');
}

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

int main() {
    
    // initialize cell array

    // initialize cell address register
    //Cell *ptr[linecount];


    return 0;
}
