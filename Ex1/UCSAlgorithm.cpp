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
#include "Tile.hpp"
#include <set>

Path* UCSAlgorithm::apply(const Tile& cStart, const Tile& cDestination) const {
    
    std::priority_queue<const UCSAlgorithmNode*, std::vector<const UCSAlgorithmNode*>, NodeComparatorGreaterThan> pcFrontier;
    std::set<const Tile*, TileComparatorLessThan> scExplored;

    //Stores all of the allocated nodes
    std::stack<const UCSAlgorithmNode*> vcAllNodes;
    
    const UCSAlgorithmNode* cStartNode = new UCSAlgorithmNode(NULL, 0, &cStart);
    
    vcAllNodes.push(cStartNode);
    pcFrontier.push(cStartNode);
    
    while (!pcFrontier.empty()) {
        
        const UCSAlgorithmNode* cNode = pcFrontier.top();
        pcFrontier.pop();
        
        //If destination was found
        if ((*(cNode->getTile())) == cDestination) {
            
            std::stack<const Tile*> scTiles;
            
            //Retrace all of the parent nodes
            while (cNode->getParent()) {
                scTiles.push(cNode->getTile());
                cNode = cNode->getParent();
            }
            
            scTiles.push(cNode->getTile());
            clearNodes(vcAllNodes);
            
            return Path::createPath(scTiles);
            
        }
        
        scExplored.insert(cNode->getTile());
        
        std::vector<const Tile*> vcNeighbors = cNode->getTile()->getNeighbors();

        //Iterate by reversal to get the sorting order correctly (because priority queue works by descending sorting)
        for (std::vector<const Tile*>::reverse_iterator iterator = vcNeighbors.rbegin() ; iterator != vcNeighbors.rend() ; iterator++) {
            
            const Tile* cChild = *iterator;
            
            //If the tile has not been already considered try it
            if (scExplored.find(cChild) == scExplored.end()) {

                const UCSAlgorithmNode* cChildNode = new UCSAlgorithmNode(cNode, cNode->getPathCost() + cChild->eType, cChild);
                vcAllNodes.push(cChildNode);
                pcFrontier.push(cChildNode);
                
            }
        
        }
        
    }
    
    //Return empty
    clearNodes(vcAllNodes);
    return Path::createPath(std::stack<const Tile*>());
    
}

void UCSAlgorithm::clearNodes(std::stack<const UCSAlgorithmNode*>& scNodes) const {
    
    while (!scNodes.empty()) {
        delete scNodes.top();
        scNodes.pop();
    }
    
}
