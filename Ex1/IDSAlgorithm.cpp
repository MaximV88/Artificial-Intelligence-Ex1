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

Path* IDSAlgorithm::apply(const Tile& cStart, const Tile& cDestination) const {

    size_t uiDepth = 0;
    std::stack<const Tile*> scValid;
    
    //Some initial value different from 0, could be anything
    size_t uiPrevDepth = 1;

    while (true) {
        
        std::set<const Tile*, TileComparatorLessThan> scPath;
        size_t uiReachedDepth = depthLimitedSearch(&cStart, &cDestination, uiDepth, scPath, scValid);
        ++uiDepth;
        
        //No need to proceed if the iteration cant go further despite having larger depth limit, or if result recieved
        if ((uiPrevDepth == uiReachedDepth) || !scValid.empty())
            break;
        
        //Update for next iteration
        uiPrevDepth = uiReachedDepth;
        
    }

    return Path::createPath(scValid);
    
}

size_t IDSAlgorithm::depthLimitedSearch(const Tile *cCurrent, const Tile *cGoal, size_t depth, std::set<const Tile*, TileComparatorLessThan>& scPath, std::stack<const Tile *>& scValid) const {
    
    scPath.insert(cCurrent);
    
    //Since using unsigned int depth 0 is converted to simple check - add to visited if part of the path
    if ((depth == 0) && (*cCurrent) == (*cGoal)) { scValid.push(cCurrent); }
    else if (depth > 0) {
        
        size_t uiMaximalReachedDepth = 0;
        
        //Iterate over all it's neighbors (that have not been iterated on yet)
        std::vector<const Tile*> vcNeighbors = cCurrent->getNeighbors();
        
        for (std::vector<const Tile*>::const_iterator iterator = vcNeighbors.begin() ; iterator != vcNeighbors.end() ; iterator++) {
            
            const Tile* cTile = *iterator;
            
            //If the tile has not been visited yet on the current path (prevents cycles)
            if (scPath.find(cTile) == scPath.end()) {
                
                //Copy the current path to every unique following
                std::set<const Tile*, TileComparatorLessThan> scCurrentPath = scPath;
                
                size_t uiReachedDepth = depthLimitedSearch(cTile, cGoal, depth - 1, scCurrentPath, scValid);
                
                //Push if result was found
                if (!scValid.empty()) {
                    
                    //Insert into the visited set and return depth that includes another step upwards toward the root
                    scValid.push(cCurrent);
                    return uiReachedDepth + 1;
    
                }
                
                //The maximum reached depth is gathered from previous iterations
                if (uiMaximalReachedDepth < uiReachedDepth)
                    uiMaximalReachedDepth = uiReachedDepth;
                
            }
            
        }
        
        //Since we are keeping the value of the height, it needs to be incremented when going back
        return uiMaximalReachedDepth + 1;
        
    }
    
    //Reached bottom of recursion - height is 0
    return 0;
    
}
