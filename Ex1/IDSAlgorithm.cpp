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
    
    bool bIsFound = false;
    while (!bIsFound ) {
        
        std::stack<const Tile*> scVisited;
        bIsFound = depthLimitedSearch(&cStart, nullptr, &cDestination, uiDepth, scVisited);
        ++uiDepth;
        
        /*
         * If the goal node has been found, get the information
         * from the order they were added by.
         */
        
        if (bIsFound) {
            
            size_t uiCost = 0;
            std::vector<Tile::Directions> vcDirections;
            
            while (!scVisited.empty()) {
                
                const Tile* cCurrentTile = scVisited.top();
                scVisited.pop();

                switch (cCurrentTile->eType) {
                    case Tile::Types::kRoad: uiCost += 1; break;
                    case Tile::Types::kDirt: uiCost += 3; break;
                    case Tile::Types::kHill: uiCost += 10; break;
                    default: break; //Shouldnt add cost for non-existing tiles
                }

                //Dont add any more directions if its the last
                if (scVisited.empty()) break;
                
                const Tile* cNextTile = scVisited.top();

                //Store the direction of this tile compared to the previous
                if (cNextTile) vcDirections.push_back(cCurrentTile->getDirection(*cNextTile));
                
            }
            
            //Return a path with gathered information
            return new Path(vcDirections, uiCost);
            
        }
     
        //No need to proceed more than the maximum path length
        if (uiDepth > uiTotalTiles)
            break;
        
    }

    return new Path(std::vector<Tile::Directions>(), 0);

}

bool IDSAlgorithm::depthLimitedSearch(const Tile *cCurrent, const Tile* cPrevTile, const Tile *cGoal, size_t depth, std::stack<const Tile *>& scVisited) const {
    
    //Since using unsigned int depth 0 is converted to simple check - add to visited if part of the path
    if ((depth == 0) && (*cCurrent) == (*cGoal)) { scVisited.push(cCurrent); return true; }
    else if (depth > 0) {
        
        //Iterate over all it's neighbors (that have not been iterated on yet)
        for (const Tile* cTile : cCurrent->getNeighbors()) {
            
            //Duplicate pruning - dont go back to parent
            if (cPrevTile && ((*cTile) == (*cPrevTile))) continue;
            
            //If the recursion has found the goal, it's part of the correct path
            if (depthLimitedSearch(cTile, cCurrent, cGoal, depth - 1, scVisited)) {
                
                //Insert into the visited set
                scVisited.push(cCurrent);
                return true;
                
            }
            
        }
        
    }
    
    return false;
    
}
