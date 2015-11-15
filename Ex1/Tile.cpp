//
//  Tile.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Tile.hpp"
#include <string>
#include <exception>

Tile::Tile(Types eTileType, size_t uiPositionX, size_t uiPositionY) :
eType(eTileType), m_uiPositionX(uiPositionX), m_uiPositionY(uiPositionY) { }

Tile::Tile(const Tile& cTile) :
eType(cTile.eType), m_uiPositionX(cTile.m_uiPositionX), m_uiPositionY(cTile.m_uiPositionY) { }

bool Tile::operator==(const Tile &cTile) const {
    
    return ((m_uiPositionX == cTile.m_uiPositionX) && (m_uiPositionY == cTile.m_uiPositionY));
    
}

bool Tile::operator!=(const Tile &cTile) const {
    
    return ((m_uiPositionX != cTile.m_uiPositionX) || (m_uiPositionY != cTile.m_uiPositionY));
    
}

std::ostream& operator<< (std::ostream &out, const Tile &cTile) {
    
    std::string strType;
    
    switch (cTile.eType) {
        case Tile::Types::kStart : strType = "Start";    break;
        case Tile::Types::kEnd   : strType = "End";      break;
        case Tile::Types::kHill  : strType = "Hill";     break;
        case Tile::Types::kRoad  : strType = "Road";     break;
        case Tile::Types::kDirt  : strType = "Dirt";     break;
        case Tile::Types::kWater : strType = "Water";    break;
    }
    
    out << "Type: \t" << strType << ", \tLocation: (" << cTile.m_uiPositionX << ", " << cTile.m_uiPositionY << ")";
    return out;
    
}