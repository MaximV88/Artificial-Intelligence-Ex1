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
#include <stack>
#include <queue>
#include <set>

Path* UCSAlgorithm::apply(const Tile& cStart, const Tile& cDestination, size_t uiTotalTiles) const {
    
    std::priority_queue<const UCSAlgorithmNode*, std::vector<const UCSAlgorithmNode*>, NodeComparatorLessThan> pcFrontier;
    std::set<const Tile*, TileComparatorLessThan> scExplored;
    std::set<const Tile*, TileComparatorLessThan> scFrontier;

    //Stores all of the allocated nodes
    std::stack<const UCSAlgorithmNode*> vcAllNodes;
    
    const UCSAlgorithmNode* cStartNode = new UCSAlgorithmNode(nullptr, 0, &cStart);
    
    vcAllNodes.push(cStartNode);
    pcFrontier.push(cStartNode);
    scFrontier.insert(&cStart);
    
    while (!pcFrontier.empty()) {
        
        const UCSAlgorithmNode* cNode = pcFrontier.top();
        pcFrontier.pop();
        scFrontier.erase(cNode->getTile());
        
        if ((*(cNode->getTile())) == cDestination) {
            
            std::stack<const Tile*> scTiles;
            
            //Retrace all of the parent nodes
            while (cNode->getParent()) {
                scTiles.push(cNode->getTile());
                cNode = cNode->getParent();
            }
            
            return Path::createPath(scTiles);
            
        }
        
        scExplored.insert(cNode->getTile());
        
        for (const Tile* cChild : cNode->getTile()->getNeighbors())
            if (scExplored.find(cChild) == scExplored.end() &&
                (scFrontier.find(cChild) == scFrontier.end())) {
                
                const UCSAlgorithmNode* cChildNode = new UCSAlgorithmNode(cNode, cNode->getPathCost() + cNode->getTile()->eType, cChild);
                vcAllNodes.push(cChildNode);
                pcFrontier.push(cChildNode);
                scFrontier.insert(cChild);
                
            }
        
    }
    
    
    return Path::createPath(std::vector<const Tile*>());
    
}
