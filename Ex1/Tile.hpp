//
//  Tile.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>
#include <cstdint>
#include <iostream>

class Tile {

    friend class Map;
    
    //Private Variables
    const size_t m_uiPositionX;
    const size_t m_uiPositionY;
    
public:
    
    enum class TileType : std::int_fast8_t {
        kRoad = 0,
        kDirt,
        kHill,
        kWater,
        kStart,
        kEnd
    };
    
    enum class Direction : int_fast8_t {
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
    
    //Public Variables
    const TileType eType;
    

    /** Constructor */
    Tile(TileType eTileType, size_t uiPositionX, size_t uiPositionY);
    
    /** Copy Constructor */
    Tile(const Tile& cTile);
    
    Direction getDirection(const Tile& cTile) const;

    /** opeartor == */
    bool operator==(const Tile& cTile) const;
    bool operator!=(const Tile& cTile) const;

    friend std::ostream& operator<<(std::ostream &out, const Tile &cTile);
    
};

#endif /* Tile_hpp */
