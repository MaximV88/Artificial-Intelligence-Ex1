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
    
    enum class Directions : int_fast8_t {
        kRight = 0,
        kLeft,
        kUp,
        kDown,
        kRightDown,
        kRightUp,
        kLeftDown,
        kLeftUp,
        kCenter
    };
    
    /** Constructor */
    Map(const std::string& strFormattedMap);
    
    /** Destructor */
    ~Map();
    
    Tile getStartTile() const;
    Tile getEndTile() const;
    
    Directions getDirection(const Tile &cOrigin, const Tile& cDestination) const;
    
    /** May return 0 if out of map bounds */
    const Tile* getTile(const Tile& cOrigin, Directions direction) const;

    const std::vector<const Tile*> getNeighbors(const Tile& cTile) const;
    
};

#endif /* Map_hpp */
