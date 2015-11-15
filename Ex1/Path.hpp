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
#include "Map.hpp"

class Path {
    
    //Private Variables
    const size_t m_uiCost;
    const std::vector<Map::Directions> m_vcDirections;
    
public:
    
    Path(const std::vector<Map::Directions>& vcDirections, size_t uiCost);
    
    /** Returns the cost of the path */
    size_t getCost() const;
    
    /** Returns the directions the path made */
    const std::vector<Map::Directions>& getDirections() const;
    
    /** prints the formatted description of the path */
    friend std::ostream& operator<<(std::ostream &out, const Path &cPath);

};

#endif /* Path_hpp */
