//
//  Path.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 15/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <iostream>
#include <vector>
#include <stack>
#include "Map.hpp"

class Path {
    
    //Private Variables
    const size_t m_uiCost;
    const std::vector<Directions> m_vcDirections;
    
    /** Private Constructor */
    Path(const std::vector<Directions>& vcDirections, size_t uiCost);
    
public:
    
    /** Constructor */
    Path(const std::stack<const Tile*>& scPath);
    
    /** Returns the cost of the path */
    size_t getCost() const;
    
    /** Returns the directions the path made */
    const std::vector<Directions>& getDirections() const;
    
    /** Returns a Path object that is influenced by the tile's order in the stack */
    static Path* createPath(const std::stack<const Tile*>& scPath);
    
    /** Returns a Path object that is influenced by the tile's order in the vector */
    static Path* createPath(const std::vector<const Tile*>& vcPath);

    /** prints the formatted description of the path */
    friend std::ostream& operator<<(std::ostream &out, const Path &cPath);

};

#endif /* Path_hpp */
