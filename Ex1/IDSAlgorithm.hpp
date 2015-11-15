//
//  IDSAlgorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef IDSAlgorithm_hpp
#define IDSAlgorithm_hpp

#include "Algorithm.hpp"

class IDSAlgorithm : public Algorithm {
    
    const Tile* depthLimitedSearch(const Tile* cCurrent, const Tile* cGoal, size_t depth, std::vector<const Tile*>& vcVisited) const;
    
public:
    
    /** Returns a vector of direction that represent the result of the algorithm */
    virtual Path* apply(const Tile& cStart, const Tile& cDestination) const;
    
};

#endif /* IDSAlgorithm_hpp */
