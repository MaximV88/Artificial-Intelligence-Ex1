//
//  main.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 10/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Map.hpp"
#include "Algorithm.hpp"
#include "Path.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    //Read the file to seperate the contents of map and algorithm
    ifstream ifs("input4I.txt");
    
    //Get the algorithm type
    string strAlgorithmType;
    std::getline(ifs, strAlgorithmType);
    
    //Get the formatted map (reading from current location until end of file)
    std::string strFormattedMap((std::istreambuf_iterator<char>(ifs) ),
                                (std::istreambuf_iterator<char>()    ));

    
    //Create the representation of the map
    Map cMap = Map(strFormattedMap);
    
    //Create the required algorithm
    Algorithm* cAlgorithm = Algorithm::createAlgorithm(strAlgorithmType);
    
    Path* cPath;
    
    try {
        
        //Get the result of the algorithm's application on the map
        cPath = cAlgorithm->apply(cMap.getStartTile(), cMap.getEndTile());
        
    } catch (std::exception& cException) {
        
        //Since one of the conditions for completing the traversal is incomplete, there is no solution
        cPath = Path::createPath(nullptr);
        
    }

    //Print the path to file
    ofstream output("output.txt");
    output << *cPath;
    output.close();
    
    //Remove all dynamiclly allocated memory and return
    delete cPath;
    delete cAlgorithm;
    
    return 0;
}
