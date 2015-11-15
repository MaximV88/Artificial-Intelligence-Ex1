//
//  Map.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Tile.hpp"

class Map {

    //Private Variables
    size_t m_uiWidth;
    size_t m_uiHeight;
    
    Tile* m_cData;
    
    //Private Functions
    constexpr size_t index(size_t x, size_t y) const;
    
public:

    /** Constructor */
    Map(const std::string& strFormattedMap);
    
    /** Destructor */
    ~Map();
    
    Tile getStartTile() const;
    Tile getEndTile() const;
    
    const Tile& getTile(const Tile& cOrigin, Tile::Direction) const;

    const std::vector<const Tile*> getNeighbors(const Tile& cTile) const;
    
};

#endif /* Map_hpp */
