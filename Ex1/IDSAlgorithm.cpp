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
#include <iostream>

Path* IDSAlgorithm::apply(const Tile& cStart, const Tile& cDestination) const {

    size_t uiDepth = 0;
    
    bool bIsFound = false;
    while (!bIsFound) {
        
        std::vector<const Tile*> vcVisited;
        bIsFound = depthLimitedSearch(&cStart, &cDestination, uiDepth, vcVisited);
        ++uiDepth;
        
        /*
         * If the goal node has been found, get the information
         * from the order they were added by.
         */
        
        if (bIsFound) {
            
            size_t uiCost = 0;
            std::vector<Tile::Directions> vcDirections;
            const Tile* cPreviousTile = &cStart;
            
            for (const Tile* cTile : vcVisited) {
                
                switch (cTile->eType) {
                    case Tile::Types::kRoad: uiCost += 1; break;
                    case Tile::Types::kDirt: uiCost += 3; break;
                    case Tile::Types::kHill: uiCost += 10; break;
                    default: break; //Shouldnt add cost for non-existing tiles
                }

                //Store the direction of this tile compared to the previous
                if ((*cTile) != (*cPreviousTile)) vcDirections.push_back(cPreviousTile->getDirection(*cTile));

                //Update for next iteration
                cPreviousTile = cTile;
                
            }
         
            return new Path(vcDirections, uiCost);
            
        }
        
    }
    
    return new Path(std::vector<Tile::Directions>(), 0);
    
}

const Tile* IDSAlgorithm::depthLimitedSearch(const Tile *cCurrent, const Tile *cGoal, size_t depth, std::vector<const Tile *>& vcVisited) const {
    
    //Since using unsigned int depth 0 is converted to simple check
    if ((*cCurrent) == (*cGoal)) return cCurrent;
    else if (depth > 0) {
       
        //Insert into the visited set
        vcVisited.push_back(cCurrent);
        
        //Iterate over all it's neighbors (that have not been iterated on yet)
        for (const Tile* cTile : cCurrent->getNeighbors())
            if (std::find(vcVisited.begin(), vcVisited.end(), cTile) == vcVisited.end()) {
               
                const Tile* cResult = depthLimitedSearch(cTile, cGoal, depth - 1, vcVisited);
                
                //Return only if found the Goal (otherwise would be null)
                if (cResult) return cResult;
                
            }
        
    }
    
    return nullptr;
    
}