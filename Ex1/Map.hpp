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
    
    Tile** m_cData;
    
    //Private Functions
    size_t index(size_t x, size_t y) const;
    
    /** Returns the neighbors of the input tile */
    const std::vector<const Tile*> getNeighbors(const Tile& cTile) const;
        
public:
    
    /** Constructor */
    Map(const std::string& strFormattedMap);
    
    /** Destructor */
    ~Map();
    
    Tile getStartTile() const;
    Tile getEndTile() const;
    
    size_t getTilesCount() const;
    
    /** May return null if out of map bounds */
    const Tile* getTile(const Tile& cOrigin, Directions direction) const;
    
};

#endif /* Map_hpp */
