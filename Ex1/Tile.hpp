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
#include <iostream>
#include <vector>

enum Types {
    kRoad = 1,
    kDirt = 3,
    kHill = 10,
    kWater,
    kStart,
    kEnd
};

enum Directions {
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

class Tile {

    friend class Map;
    
    //Private Variables
    const size_t m_uiPositionX;
    const size_t m_uiPositionY;
    
    std::vector<const Tile*> m_vcNeighbors;
    
    void setNeighbors(const std::vector<const Tile*>& vcNeighbors);
    
public:

    //Public Variables
    const Types eType;
    

    /** Constructor */
    Tile(Types eTileType, size_t uiPositionX, size_t uiPositionY);
    
    /** Copy Constructor */
    Tile(const Tile& cTile);
    
    /** Returns the direction between the input tiles */
    Directions getDirection(const Tile& cDestination) const;
    
    /** Returns the neighbors of the current tile */
    std::vector<const Tile*> getNeighbors() const;
    
    /** Returns a string that represents the type of the tile */
    std::string kind() const;
    
    /** Returhs a char that represents the type of the tile */
    char type() const;
    
    /** opeartor == */
    bool operator==(const Tile& cTile) const;
    bool operator!=(const Tile& cTile) const;
    bool operator<(const Tile& cTile) const;
    bool operator>(const Tile& cTile) const;
    
    friend std::ostream& operator<<(std::ostream &out, const Tile &cTile);
    
};

struct TileComparatorLessThan {
    bool operator() (const Tile* lhs, const Tile* rhs) {
        return *lhs < *rhs;
    }
};

#endif /* Tile_hpp */
