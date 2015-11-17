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
    
//    std::vector<const Tile*> vcPath;
//
//    std::priority_queue<const Tile*, std::vector<const Tile*>, TileComparatorLessThan> pcFrontier;
//    std::set<const Tile*, TileComparatorEqual> scFrontier;
//    std::set<const Tile*, TileComparatorEqual> scExplored;
//    
//    pcFrontier.push(&cStart);
//    scFrontier.insert(&cStart);
//
//    while (!pcFrontier.empty()) {
//        
//        const Tile* cNode = pcFrontier.top();
//        pcFrontier.pop();
//        scFrontier.erase(cNode);
//        
//        vcPath.push_back(cNode);
//
//        if ((*cNode) == cDestination) {
//            return Path::createPath(vcPath);
//        }
//        
//        scExplored.insert(cNode);
//        
//        for (const Tile* cChild : cNode->getNeighbors()) {
//            
//            if (!scExplored.count(cChild)) {
//                
//                if (scFrontier.find(cChild) == scFrontier.end()) {
//                    
//                    pcFrontier.push(cChild);
//                    
//                }
//                //If it has a higher cost  (not the first)
//             //   else if ((*cPrev)->eType > cChild->eType) {
//                  //  std::swap(cChild, (*cPrev));
//                  //  std::make_heap(vcFrontier.begin(), vcFrontier.end());
//               // }
//                
//            }
//            
//        }
//        
//    }
    
    return Path::createPath(std::vector<const Tile*>());
    
}
