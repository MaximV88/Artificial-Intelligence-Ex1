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
#include <vector>

class Tile {

    friend class Map;
    
    //Private Variables
    const size_t m_uiPositionX;
    const size_t m_uiPositionY;
    
    std::vector<const Tile*> m_vcNeighbors;
    
    void setNeighbors(const std::vector<const Tile*>& vcNeighbors);
    
public:
    
    enum class Types : std::int_fast8_t {
        kRoad,
        kDirt,
        kHill,
        kWater,
        kStart,
        kEnd
    };
    
    enum class Directions : int_fast8_t {
        kRight,
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
    const Types eType;
    

    /** Constructor */
    Tile(Types eTileType, size_t uiPositionX, size_t uiPositionY);
    
    /** Copy Constructor */
    Tile(const Tile& cTile);
    
    /** Returns the direction between the input tiles */
    Directions getDirection(const Tile& cDestination) const;
    
    /** Returhs the neighbors of the current tile */
    std::vector<const Tile*> getNeighbors() const;
    
    /** opeartor == */
    bool operator==(const Tile& cTile) const;
    bool operator!=(const Tile& cTile) const;

    friend std::ostream& operator<<(std::ostream &out, const Tile &cTile);
    
};

#endif /* Tile_hpp */
