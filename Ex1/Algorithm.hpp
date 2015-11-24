//
//  Algorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "Tile.hpp"
#include <stdio.h>
#include <vector>
#include <string>


class Path;

enum AlgorithmType {
    kIDS,
    kUCS
};

class Algorithm {
public:
    
    
    virtual ~Algorithm();
    
    /** Returns an algorithm by input string. supports "IDS" or "UCS" */
    static Algorithm* createAlgorithm(const std::string& strFormattedType);
    
    /** Returns an algorithm by requested type */
    static Algorithm* createAlgorithm(AlgorithmType eType);
    
    /** Returns a vector of direction that represent the result of the algorithm */
    virtual Path* apply(const Tile& cStart, const Tile& cDestination) const = 0;

};

#endif /* Algorithm_hpp */
