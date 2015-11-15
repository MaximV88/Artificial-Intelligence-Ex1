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

Tile::Tile(TileType eTileType, size_t uiPositionX, size_t uiPositionY) :
eType(eTileType), m_uiPositionX(uiPositionX), m_uiPositionY(uiPositionY) { }

Tile::Tile(const Tile& cTile) :
eType(cTile.eType), m_uiPositionX(cTile.m_uiPositionX), m_uiPositionY(cTile.m_uiPositionY) { }

Tile::Direction Tile::getDirection(const Tile &cTile) const {

    //Important to remember that highest is 0 and lowest is N-1, sideways is normal
    
    //Get the horizontal direction
    Direction eHorizontal;
    if (cTile.m_uiPositionX == m_uiPositionX)       eHorizontal = Direction::kCenter;
    else if (cTile.m_uiPositionX > m_uiPositionX)   eHorizontal = Direction::kRight;
    else                                            eHorizontal = Direction::kLeft;
    
    //Get the vertical direction
    Direction eVertical;
    if (cTile.m_uiPositionY == m_uiPositionY)       eVertical = Direction::kCenter;
    else if (cTile.m_uiPositionY > m_uiPositionY)   eVertical = Direction::kDown;
    else                                            eVertical = Direction::kUp;
    
    //Compare both horizontal and vertical to get the final heading
    switch (eHorizontal) {
        case Direction::kCenter:
            
            switch (eVertical) {
                case Direction::kCenter:    return Direction::kCenter;
                case Direction::kUp:        return Direction::kUp;
                case Direction::kDown:      return Direction::kDown;
                default: break; //Shouldnt reach
            }
            
            break;
            
        case Direction::kRight:
            
            switch (eVertical) {
                case Direction::kCenter:    return Direction::kRight;
                case Direction::kUp:        return Direction::kRightUp;
                case Direction::kDown:      return Direction::kRightDown;
                default: break; //Shouldnt reach
                    
            }
        
        case Direction::kLeft:
        
            switch (eVertical) {
                case Direction::kCenter:    return Direction::kLeft;
                case Direction::kUp:        return Direction::kLeftUp;
                case Direction::kDown:      return Direction::kLeftDown;
                default:  break; //Shouldnt reach
            }

        //Shouldnt reach
        default: break;
    }
    
    throw std::runtime_error("incorrect implementation of direction between tiles");
    
}

bool Tile::operator==(const Tile &cTile) const {
    
    return ((m_uiPositionX == cTile.m_uiPositionX) && (m_uiPositionY == cTile.m_uiPositionY));
    
}

bool Tile::operator!=(const Tile &cTile) const {
    
    return ((m_uiPositionX != cTile.m_uiPositionX) || (m_uiPositionY != cTile.m_uiPositionY));
    
}

std::ostream& operator<< (std::ostream &out, const Tile &cTile) {
    
    std::string strType;
    
    switch (cTile.eType) {
        case Tile::TileType::kStart : strType = "Start";    break;
        case Tile::TileType::kEnd   : strType = "End";      break;
        case Tile::TileType::kHill  : strType = "Hill";     break;
        case Tile::TileType::kRoad  : strType = "Road";     break;
        case Tile::TileType::kDirt  : strType = "Dirt";     break;
        case Tile::TileType::kWater : strType = "Water";    break;
    }
    
    out << "Type: \t" << strType << ", \tLocation: (" << cTile.m_uiPositionX << ", " << cTile.m_uiPositionY << ")";
    return out;
    
}