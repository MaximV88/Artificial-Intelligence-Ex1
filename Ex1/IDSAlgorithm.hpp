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

class IDSAlgorithm : public Algorithm {
    
    /** Returns true if found, false otherwise */
    bool depthLimitedSearch(const Tile* cCurrent, const Tile* cGoal, size_t depth, std::stack<const Tile*>& scValid, std::vector<const Tile*>& vcChecked) const;
    
public:
    
    /** Returns a path that represent the result of the algorithm */
    virtual Path* apply(const Tile& cStart, const Tile& cDestination, size_t uiTotalTiles) const;
    
};

#endif /* IDSAlgorithm_hpp */
