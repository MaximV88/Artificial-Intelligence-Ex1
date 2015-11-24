//
//  Tile.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Tile.hpp"
#include <string>
#include <stdexcept>

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

Directions Tile::getDirection(const Tile& cDestination) const {
    
    //Important to remember that highest is 0 and lowest is N-1, sideways is normal
    
    //Get the horizontal direction
    Directions eHorizontal;
    if (cDestination.m_uiPositionX == m_uiPositionX)        eHorizontal = kCenter;
    else if (cDestination.m_uiPositionX > m_uiPositionX)    eHorizontal = kRight;
    else                                                    eHorizontal = kLeft;
    
    //Get the vertical direction
    Directions eVertical;
    if (cDestination.m_uiPositionY == m_uiPositionY)        eVertical = kCenter;
    else if (cDestination.m_uiPositionY > m_uiPositionY)    eVertical = kDown;
    else                                                    eVertical = kUp;
    
    //Compare both horizontal and vertical to get the final heading
    switch (eHorizontal) {
        case kCenter:
            
            switch (eVertical) {
                case kCenter:    return kCenter;
                case kUp:        return kUp;
                case kDown:      return kDown;
                default: break; //Shouldnt reach
            }
            
            break;
            
        case kRight:
            
            switch (eVertical) {
                case kCenter:    return kRight;
                case kUp:        return kRightUp;
                case kDown:      return kRightDown;
                default: break; //Shouldnt reach
                    
            }
            
        case kLeft:
            
            switch (eVertical) {
                case kCenter:    return kLeft;
                case kUp:        return kLeftUp;
                case kDown:      return kLeftDown;
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

bool Tile::operator<(const Tile &cTile) const {

    return ((m_uiPositionX < cTile.m_uiPositionX) || ((m_uiPositionX == cTile.m_uiPositionX) && m_uiPositionY < cTile.m_uiPositionY));
    
}

bool Tile::operator>(const Tile &cTile) const {
    
    return ((m_uiPositionX > cTile.m_uiPositionX) || ((m_uiPositionX == cTile.m_uiPositionX) && m_uiPositionY > cTile.m_uiPositionY));
    
}

std::string Tile::kind() const {
    
    switch (eType) {
        case kStart : return "Start";
        case kEnd   : return "End";
        case kHill  : return "Hill";
        case kRoad  : return "Road";
        case kDirt  : return "Dirt";
        case kWater : return "Water";
    }
    
}

char Tile::type() const {
 
    switch (eType) {
        case kStart:   return 'S';
        case kEnd:     return 'G';
        case kDirt:    return 'D';
        case kHill:    return 'H';
        case kWater:   return 'W';
        case kRoad:    return 'R';
    }
    
}

std::ostream& operator<< (std::ostream &out, const Tile &cTile) {
    
    out << "Type: \t" << cTile.type() << ", Neighbors: \t" << cTile.m_vcNeighbors.size() << ", \tLocation: (" << cTile.m_uiPositionX << ", " << cTile.m_uiPositionY << ")" << "\n";
    
    if (cTile.m_vcNeighbors.size()) out << "List of neighbors: \n" << std::endl;
    
    for (std::vector<const Tile*>::const_iterator iterator = cTile.m_vcNeighbors.begin() ; iterator != cTile.m_vcNeighbors.end() ; iterator++) {
        
        const Tile* cNeighbor = *iterator;
        out << "Type: \t" << cNeighbor->type() << ", \tLocation: (" << cNeighbor->m_uiPositionX << ", " << cNeighbor->m_uiPositionY << ")" << "\n";
        
    }
    
    return out;
    
}