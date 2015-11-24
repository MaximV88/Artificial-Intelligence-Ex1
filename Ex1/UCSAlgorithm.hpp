//
//  UCSAlgorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef UCSAlgorithm_hpp
#define UCSAlgorithm_hpp

#include "Algorithm.hpp"
#include <queue>
#include <stack>

class UCSAlgorithm : public Algorithm {
    
    struct UCSAlgorithmNode {
        
        const Tile* m_cTile;
        size_t m_uiPathCost;
        const UCSAlgorithmNode* m_cParent;
                
        const Tile* getTile() const { return m_cTile; }
        size_t getPathCost() const { return m_uiPathCost; }
        const UCSAlgorithmNode* getParent() const { return m_cParent; }
        
        UCSAlgorithmNode(const UCSAlgorithmNode* cParent, size_t uiPathCost, const Tile* cTile) :
        m_cTile(cTile), m_cParent(cParent), m_uiPathCost(uiPathCost) { }
        
    };
    
    /*
     * The priority queue will do the opposite of the strick weak ordering,
     * so we need to supply the NOT equavivalent: !(<) is actually >=.
     */
    
    struct NodeComparatorGreaterThan {
        bool operator() (const UCSAlgorithmNode* lhs, const UCSAlgorithmNode* rhs) {
            return lhs->getPathCost() > rhs->getPathCost();
        }
    };

    
    /** Returns a vector of direction that represent the result of the algorithm */
    virtual Path* apply(const Tile& cStart, const Tile& cDestination) const;
    
    void clearNodes(std::stack<const UCSAlgorithmNode*>& scNodes) const;
    
public:
    
};

#endif /* UCSAlgorithm_hpp */
