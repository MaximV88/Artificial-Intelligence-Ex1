//
//  UCSAlgorithm.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "UCSAlgorithm.hpp"
#include "Map.hpp"
#include "Path.hpp"
#include <stack>

Path* UCSAlgorithm::apply(const Tile& cStart, const Tile& cDestination, size_t uiTotalTiles) const {
    
    std::stack<const Tile*> vcPath;
    std::vector<const Tile*> vcOpen;
    std::vector<const Tile*> vcClose;
    
    //Push starting node
    vcOpen.push_back(&cStart);
    
    while (!vcOpen.empty()) {
        
        const Tile* cNext = vcOpen.front();
        vcOpen.pop_back();

        vcClose.push_back(cNext);

        if ((*cNext) == cDestination) {
            vcPath.push(cNext);
            break;
        }
        
        
    }
    
    return Path::createPath(vcPath);
    
}