//
//  IDSAlgorithm.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "IDSAlgorithm.hpp"
#include "Tile.hpp"
#include "Path.hpp"

Path* IDSAlgorithm::apply(const Tile& cStart, const Tile& cDestination, size_t uiTotalTiles) const {

    size_t uiDepth = 0;
    std::stack<const Tile*> scValid;
    
    bool bIsFound = false;
    while (!bIsFound ) {
        
        std::vector<const Tile*> vcOpenList;
        std::set<const Tile*, TileComparatorLessThan> scPath;
        bIsFound = depthLimitedSearch(&cStart, &cDestination, uiDepth, scPath, scValid);
        ++uiDepth;
        
        
        //No need to proceed more than the maximum path length
        if (uiDepth > uiTotalTiles)
            break;
        
    }

    return Path::createPath(scValid);
    
}

bool IDSAlgorithm::depthLimitedSearch(const Tile *cCurrent, const Tile *cGoal, size_t depth, std::set<const Tile*, TileComparatorLessThan>& scPath, std::stack<const Tile *>& scValid) const {
    
    scPath.insert(cCurrent);
    
    //Since using unsigned int depth 0 is converted to simple check - add to visited if part of the path
    if ((depth == 0) && (*cCurrent) == (*cGoal)) { scValid.push(cCurrent); return true; }
    else if (depth > 0) {
        
        //Iterate over all it's neighbors (that have not been iterated on yet)
        for (const Tile* cTile : cCurrent->getNeighbors()) {
            
            //If the tile has not been visited yet on the current path (prevents cycles)
            if (scPath.find(cTile) == scPath.end()) {
                
                //Copy the current path to every unique following
                std::set<const Tile*, TileComparatorLessThan> scCurrentPath = scPath;
                
                if(depthLimitedSearch(cTile, cGoal, depth - 1, scCurrentPath, scValid)) {
                    
                    //Insert into the visited set
                    scValid.push(cCurrent);
                    return true;
                    
                }
                
            }
            
        }
        
    }
    
    return false;
    
}
