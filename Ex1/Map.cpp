//
//  Map.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Map.hpp"
#include "Tile.hpp"
#include <algorithm>

constexpr size_t Map::index(size_t x, size_t y) const { return x + m_uiWidth * y; }

size_t Map::getTilesCount() const { return m_uiHeight * m_uiWidth; }

Map::Map(const std::string& strFormattedMap) : m_cData(nullptr) {
    
    //The input is in formatted view, so fill the data according to each 'tile' (letter) - first get the size
    size_t uiCurrentIndex = strFormattedMap.find_first_of("\n");
    m_uiHeight = m_uiWidth = stoi(strFormattedMap.substr(0, uiCurrentIndex));
    
    //Allocate the dynamic memory block required
    typedef std::aligned_storage<sizeof(Tile), std::alignment_of<Tile>::value>::type storage_type;
    m_cData = reinterpret_cast<Tile*>(new storage_type[m_uiWidth * m_uiHeight]);
    
    //Now parse each row by getting the relevant line and fill tiles by it
    for (size_t uiRow = 0 ; uiRow < m_uiWidth ; uiRow++) {
        
        size_t uiEndOfRow = strFormattedMap.find_first_of("\n", uiCurrentIndex+1);
        std::string strRowInfo = strFormattedMap.substr(uiCurrentIndex+1, m_uiWidth);
        uiCurrentIndex = uiEndOfRow;
        
        for (size_t uiCol = 0 ; uiCol < m_uiHeight ; uiCol++) {
            
            //Using  placement new to create tiles, assignemt is as told by instructions
            switch (strRowInfo[uiCol]) {
                case 'S': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kStart,    uiCol, uiRow); break;
                case 'G': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kEnd,      uiCol, uiRow); break;
                case 'R': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kRoad,     uiCol, uiRow); break;
                case 'D': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kDirt,     uiCol, uiRow); break;
                case 'H': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kHill,     uiCol, uiRow); break;
                case 'W': new(m_cData + uiRow * m_uiWidth + uiCol) Tile(Tile::Types::kWater,    uiCol, uiRow); break;
                default: break;
            }
            
        }
        
    }
    
    /*
     * After the assignment of Tiles to the map, each tile needs to 
     * know about it's neighbors. This is done by assigning it's 
     * reachable neighbors via pre-calculation in this class and
     * setting the member variable at the Tile class.
     */
    
    for (size_t uiRow = 0 ; uiRow < m_uiWidth ; uiRow++)
        for (size_t uiCol = 0 ; uiCol < m_uiHeight ; uiCol++) {
         
            Tile& cCurrentTile = m_cData[index(uiCol, uiRow)];
            
            //Assign the neighbors
            cCurrentTile.setNeighbors(getNeighbors(cCurrentTile));
            
        }

}

Map::~Map() {

    //Delete the allocated dynamic array
    if (m_cData) delete  m_cData;

}

Tile Map::getStartTile() const { return Tile(m_cData[0]); }

Tile Map::getEndTile() const { return Tile(m_cData[index(m_uiWidth - 1, m_uiHeight - 1)]); }

const Tile* Map::getTile(const Tile &cOrigin, Tile::Directions direction) const {
    
    /*
     * Checks if the origin tile's location is valid for retrieval in the requested direction,
     * (i.e. isnt going to read out of bounds) and return the required tile by direction.
     * otherwise no condition is going to be met and a NULL (nullptr) will be retured.
     */
    
    switch (direction) {
        case Tile::Directions::kUp:
            
            if (cOrigin.m_uiPositionY > 0)
                return &m_cData[index(cOrigin.m_uiPositionX, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case Tile::Directions::kDown:
            
            if (cOrigin.m_uiPositionY < m_uiHeight - 1)
                return &m_cData[index(cOrigin.m_uiPositionX, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case Tile::Directions::kLeft:
            
            if (cOrigin.m_uiPositionX > 0 )
                return &m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY)];
            
            break;
            
        case Tile::Directions::kRight:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1)
                return &m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY)];
            
            break;
            
        case Tile::Directions::kLeftDown:
            
            if (cOrigin.m_uiPositionX > 0 && cOrigin.m_uiPositionY < m_uiHeight - 1)
                return &m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case Tile::Directions::kLeftUp:
            
            if (cOrigin.m_uiPositionX > 0 && cOrigin.m_uiPositionY > 0)
                return &m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case Tile::Directions::kRightDown:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1 && cOrigin.m_uiPositionY < m_uiHeight - 1)
                return &m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case Tile::Directions::kRightUp:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1 && cOrigin.m_uiPositionY > 0)
                return &m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case Tile::Directions::kCenter: return &cOrigin; break;
        default: break;
    }
    
    //No conditions were met
    return nullptr;
    
}

const std::vector<const Tile*> Map::getNeighbors(const Tile &cTile) const {
    
    //Guardian - return empty
    if (cTile.eType == Tile::Types::kWater) return std::vector<const Tile*>();
    
    //Can have up to 8 adjacent tiles
    std::vector<const Tile*> vcNeighbors;

    //The following number should be included in the for loop (i.e. iteration with those values included in uiCol/uiRow)
    size_t uiRowHighest = std::min(m_uiWidth - 1, cTile.m_uiPositionX + 1);
    size_t uiColHighest = std::min(m_uiHeight - 1, cTile.m_uiPositionY + 1);
    size_t uiRowLowest  = std::max(size_t(0), (cTile.m_uiPositionX != 0) ? cTile.m_uiPositionX - 1 : 0);
    size_t uiColLowest  = std::max(size_t(0), (cTile.m_uiPositionY != 0) ? cTile.m_uiPositionY - 1 : 0);
    
    //Iterate through all of the neighbors and store those who are valid (compensate for reducation in value before test)
    for (size_t uiRow = uiRowHighest + 1 ; uiRow-- > uiRowLowest ;)
        for (size_t uiCol = uiColHighest + 1 ; uiCol-- > uiColLowest ;) {
            
            //Skip the requesting tile
            if (uiRow == cTile.m_uiPositionX && uiCol == cTile.m_uiPositionY) continue;

            const Tile& cNeighbor = m_cData[index(uiRow, uiCol)];

            //Check for water tiles
            if (cNeighbor.eType == Tile::Types::kWater) continue;
            else {
                
                /* 
                 * Check if the neighbor is sideways or not, otherwise we add (default).
                 * For sideways neighbors the related neighbors must also be checked.
                 * When the relevent tiles for the neighbors (adjacent in direction) have
                 * been checked and found not to be Water, it's valid.
                 */
                
                switch (cTile.getDirection(cNeighbor)) {
                    case Tile::Directions::kLeftDown:
                        
                        //Must get the 'Down' and 'Left' neighbors of current tile - they must exist due to sideways existing
                        if ((*getTile(cTile, Tile::Directions::kLeft)).eType == Tile::Types::kWater) continue;
                        if ((*getTile(cTile, Tile::Directions::kDown)).eType == Tile::Types::kWater) continue;
                        vcNeighbors.push_back(&cNeighbor);
                        break;
                        
                    case Tile::Directions::kLeftUp:
                        
                        //Must get the 'Up' and 'Left' neighbors of current tile - they must exist due to sideways existing
                        if ((*getTile(cTile, Tile::Directions::kLeft)).eType == Tile::Types::kWater) continue;
                        if ((*getTile(cTile, Tile::Directions::kUp)).eType == Tile::Types::kWater) continue;
                        vcNeighbors.push_back(&cNeighbor);
                        break;
                        
                    case Tile::Directions::kRightDown:
                        
                        //Must get the 'Down' and 'Right' neighbors of current tile - they must exist due to sideways existing
                        if ((*getTile(cTile, Tile::Directions::kRight)).eType == Tile::Types::kWater) continue;
                        if ((*getTile(cTile, Tile::Directions::kDown)).eType == Tile::Types::kWater) continue;
                        vcNeighbors.push_back(&cNeighbor);
                        break;
                        
                    case Tile::Directions::kRightUp:

                        //Must get the 'Up' and 'Right' neighbors of current tile - they must exist due to sideways existing
                        if ((*getTile(cTile, Tile::Directions::kRight)).eType == Tile::Types::kWater) continue;
                        if ((*getTile(cTile, Tile::Directions::kUp)).eType == Tile::Types::kWater) continue;
                        vcNeighbors.push_back(&cNeighbor);
                        break;
                        
                    //Since the direction is 'Up', 'Left', 'Right', 'Down' its valid
                    default: vcNeighbors.push_back(&cNeighbor); break;
                }
                
            }
            
        }
    
    return vcNeighbors;
    
}
