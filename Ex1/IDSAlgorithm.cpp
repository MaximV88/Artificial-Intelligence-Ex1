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
        
        std::vector<const Tile*> vcChecked;
        bIsFound = depthLimitedSearch(&cStart, &cDestination, uiDepth, scValid, vcChecked);
        ++uiDepth;
        
        /*
         * If the goal node has been found, get the information
         * from the order they were added by.
         */
        
        if (bIsFound) {
            
            size_t uiCost = 0;
            std::vector<Tile::Directions> vcDirections;
            
           while (!scValid.empty()) {

            
                const Tile* cCurrentTile = scValid.top();
                scValid.pop();

                switch (cCurrentTile->eType) {
                    case Tile::Types::kRoad: uiCost += 1; break;
                    case Tile::Types::kDirt: uiCost += 3; break;
                    case Tile::Types::kHill: uiCost += 10; break;
                    default: break; //Shouldnt add cost for non-existing tiles
                }

                //Dont add any more directions if its the last
                if (scValid.empty()) break;
                
                const Tile* cNextTile = scValid.top();

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

bool IDSAlgorithm::depthLimitedSearch(const Tile *cCurrent, const Tile *cGoal, size_t depth, std::stack<const Tile *>& scValid, std::vector<const Tile*>& vcChecked) const {
    
    vcChecked.push_back(cCurrent);
    
    //Since using unsigned int depth 0 is converted to simple check - add to visited if part of the path
    if ((depth == 0) && (*cCurrent) == (*cGoal)) { scValid.push(cCurrent); return true; }
    else if (depth > 0) {
        
        //Iterate over all it's neighbors (that have not been iterated on yet)
        for (const Tile* cTile : cCurrent->getNeighbors()) {
            
            //If the recursion has found the goal, it's part of the correct path
            if (std::find(vcChecked.begin(), vcChecked.end(), cTile) == vcChecked.end())
                if (depthLimitedSearch(cTile, cGoal, depth - 1, scValid, vcChecked)) {
                    
                    //Insert into the visited set
                    scValid.push(cCurrent);
                    return true;
                    
                }
            
        }
        
    }
    
    return false;
    
}
