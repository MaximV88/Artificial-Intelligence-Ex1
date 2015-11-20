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
#include <stack>
#include <vector>
#include <set>

class IDSAlgorithm : public Algorithm {
    
    /** Returns the depth reached by the function */
    size_t depthLimitedSearch(const Tile* cCurrent, const Tile* cGoal, size_t depth, std::set<const Tile*, TileComparatorLessThan>& scPath, std::stack<const Tile*>& scValid) const;
    
public:
    
    /** Returns a path that represent the result of the algorithm */
    virtual Path* apply(const Tile& cStart, const Tile& cDestination) const;
    
};

#endif /* IDSAlgorithm_hpp */
