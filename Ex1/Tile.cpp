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
eType(cTile.eType), m_uiPositionX(cTile.m_uiPositionX), m_uiPositionY(cTile.m_uiPositionY), m_vcNeighbors(cTile.m_vcNeighbors) { }

void Tile::setNeighbors(const std::vector<const Tile *> &vcNeighbors) {
    
    //Copy
    m_vcNeighbors = vcNeighbors;
    
}

std::vector<const Tile*> Tile::getNeighbors() const {
    
    //Returns a copy
    return m_vcNeighbors;
    
}

Tile::Directions Tile::getDirection(const Tile& cDestination) const {
    
    //Important to remember that highest is 0 and lowest is N-1, sideways is normal
    
    //Get the horizontal direction
    Directions eHorizontal;
    if (cDestination.m_uiPositionX == m_uiPositionX)        eHorizontal = Directions::kCenter;
    else if (cDestination.m_uiPositionX > m_uiPositionX)    eHorizontal = Directions::kRight;
    else                                                            eHorizontal = Directions::kLeft;
    
    //Get the vertical direction
    Directions eVertical;
    if (cDestination.m_uiPositionY == m_uiPositionY)        eVertical = Directions::kCenter;
    else if (cDestination.m_uiPositionY > m_uiPositionY)    eVertical = Directions::kDown;
    else                                                            eVertical = Directions::kUp;
    
    //Compare both horizontal and vertical to get the final heading
    switch (eHorizontal) {
        case Directions::kCenter:
            
            switch (eVertical) {
                case Directions::kCenter:    return Directions::kCenter;
                case Directions::kUp:        return Directions::kUp;
                case Directions::kDown:      return Directions::kDown;
                default: break; //Shouldnt reach
            }
            
            break;
            
        case Directions::kRight:
            
            switch (eVertical) {
                case Directions::kCenter:    return Directions::kRight;
                case Directions::kUp:        return Directions::kRightUp;
                case Directions::kDown:      return Directions::kRightDown;
                default: break; //Shouldnt reach
                    
            }
            
        case Directions::kLeft:
            
            switch (eVertical) {
                case Directions::kCenter:    return Directions::kLeft;
                case Directions::kUp:        return Directions::kLeftUp;
                case Directions::kDown:      return Directions::kLeftDown;
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