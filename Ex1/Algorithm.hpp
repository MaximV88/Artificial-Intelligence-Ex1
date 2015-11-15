//
//  Algorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include <stdio.h>
#include <vector>

using namespace std;

enum class Direction;
class Map;

class Algorithm {
public:
    
    enum class AlgorithmType {
        kIDS,
        kUCS
    };
    
    static Algorithm* createAlgorithm(AlgorithmType eType);

    /** Returns a vector of direction that represent the result of the algorithm */
    virtual vector<Direction>& apply(const Map& cMap) const = 0;

};

#endif /* Algorithm_hpp */
