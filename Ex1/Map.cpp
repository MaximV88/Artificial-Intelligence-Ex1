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
#include <stack>
#include <stdexcept>

size_t Map::index(size_t x, size_t y) const { return x + m_uiWidth * y; }

size_t Map::getTilesCount() const { return m_uiHeight * m_uiWidth; }

Map::Map(const std::string& strFormattedMap) : m_cData(NULL) {
    
    //The input is in formatted view, so fill the data according to each 'tile' (letter) - first get the size
    size_t uiCurrentIndex = strFormattedMap.find_first_of("\n");
    m_uiHeight = m_uiWidth = atoi(strFormattedMap.substr(0, uiCurrentIndex).c_str());
    
    m_cData = new Tile*[m_uiHeight * m_uiWidth];
    
    //Now parse each row by getting the relevant line and fill tiles by it
    for (size_t uiRow = 0 ; uiRow < m_uiWidth ; uiRow++) {
        
        size_t uiEndOfRow = strFormattedMap.find_first_of("\n", uiCurrentIndex+1);
        std::string strRowInfo = strFormattedMap.substr(uiCurrentIndex+1, m_uiWidth);
        uiCurrentIndex = uiEndOfRow;
        
        for (size_t uiCol = 0 ; uiCol < m_uiHeight ; uiCol++) {
            
            Types type;
            
            //Using  placement new to create tiles, assignemt is as told by instructions
            switch (strRowInfo[uiCol]) {
                case 'S': type = kStart;   break;
                case 'G': type = kEnd;     break;
                case 'R': type = kRoad;    break;
                case 'D': type = kDirt;    break;
                case 'H': type = kHill;    break;
                case 'W': type = kWater;   break;
                default: break;
            }
            
            //Assign a tile with the designated type
            m_cData[(uiRow * m_uiWidth + uiCol)] = new Tile(type, uiCol, uiRow);

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
         
            Tile& cCurrentTile = *m_cData[index(uiCol, uiRow)];
            
            //Assign the neighbors
            cCurrentTile.setNeighbors(getNeighbors(cCurrentTile));

        }

}

Map::~Map() {

    //Delete the allocated dynamic array
    if (m_cData) delete  m_cData;

}

Tile Map::getStartTile() const {
    
    //All of the tiles to iterate through
    size_t uiTotal = m_uiHeight * m_uiWidth;
    
    //Find the required tile by enum type
    for (size_t uiIndex = 0 ; uiIndex < uiTotal ; uiIndex++)
        if (m_cData[uiIndex]->eType == kStart)
            return Tile(*m_cData[uiIndex]);
    
    //If no such tile found there is a fundumental problem with the map
    throw std::runtime_error("no start tile found");
    
}

Tile Map::getEndTile() const {
    
    //All of the tiles to iterate through
    size_t uiTotal = m_uiHeight * m_uiWidth;
    
    //Find the required tile by enum type
    for (size_t uiIndex = 0 ; uiIndex < uiTotal ; uiIndex++)
        if (m_cData[uiIndex]->eType == kEnd)
            return Tile(*m_cData[uiIndex]);
    
    //If no such tile found there is a fundumental problem with the map
    throw std::runtime_error("no end tile found");

}

const Tile* Map::getTile(const Tile &cOrigin, Directions direction) const {
    
    /*
     * Checks if the origin tile's location is valid for retrieval in the requested direction,
     * (i.e. isnt going to read out of bounds) and return the required tile by direction.
     * otherwise no condition is going to be met and a NULL (nullptr) will be retured.
     */
    
    switch (direction) {
        case kUp:
            
            if (cOrigin.m_uiPositionY > 0)
                return m_cData[index(cOrigin.m_uiPositionX, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case kDown:
            
            if (cOrigin.m_uiPositionY < m_uiHeight - 1)
                return m_cData[index(cOrigin.m_uiPositionX, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case kLeft:
            
            if (cOrigin.m_uiPositionX > 0 )
                return m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY)];
            
            break;
            
        case kRight:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1)
                return m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY)];
            
            break;
            
        case kLeftDown:
            
            if (cOrigin.m_uiPositionX > 0 && cOrigin.m_uiPositionY < m_uiHeight - 1)
                return m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case kLeftUp:
            
            if (cOrigin.m_uiPositionX > 0 && cOrigin.m_uiPositionY > 0)
                return m_cData[index(cOrigin.m_uiPositionX - 1, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case kRightDown:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1 && cOrigin.m_uiPositionY < m_uiHeight - 1)
                return m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY + 1)];
            
            break;
            
        case kRightUp:
            
            if (cOrigin.m_uiPositionX < m_uiWidth - 1 && cOrigin.m_uiPositionY > 0)
                return m_cData[index(cOrigin.m_uiPositionX + 1, cOrigin.m_uiPositionY - 1)];
            
            break;
            
        case kCenter: return &cOrigin; break;
        default: break;
    }
    
    //No conditions were met
    return NULL;
    
}

const std::vector<const Tile*> Map::getNeighbors(const Tile &cTile) const {
    
    //Guardian - return empty
    if (cTile.eType == kWater) return std::vector<const Tile*>();

    bool bIsAtLeftBorder = (cTile.m_uiPositionX == 0);
    bool bIsAtRightBorder = (cTile.m_uiPositionX == m_uiWidth - 1);
    bool bIsAtTopBorder = (cTile.m_uiPositionY == 0);
    bool bIsAtBottomBorder = (cTile.m_uiPositionY == m_uiHeight - 1);
    
    //Push to stack the order in which to check the neighbors (as in instructions, but reversed due to stack)
    std::stack<const Tile*> scTiles;
    if (!bIsAtTopBorder) {
        if (!bIsAtRightBorder)  scTiles.push(m_cData[index(cTile.m_uiPositionX + 1, cTile.m_uiPositionY - 1)]);
                                scTiles.push(m_cData[index(cTile.m_uiPositionX, cTile.m_uiPositionY - 1)]);
        if (!bIsAtLeftBorder)   scTiles.push(m_cData[index(cTile.m_uiPositionX - 1, cTile.m_uiPositionY - 1)]);
    }
    
    if (!bIsAtLeftBorder)       scTiles.push(m_cData[index(cTile.m_uiPositionX - 1, cTile.m_uiPositionY)]);
    
    if (!bIsAtBottomBorder) {
        if (!bIsAtLeftBorder)   scTiles.push(m_cData[index(cTile.m_uiPositionX - 1, cTile.m_uiPositionY + 1)]);;
                                scTiles.push(m_cData[index(cTile.m_uiPositionX, cTile.m_uiPositionY + 1)]);
        if (!bIsAtRightBorder)  scTiles.push(m_cData[index(cTile.m_uiPositionX + 1, cTile.m_uiPositionY + 1)]);
    }
    
    if (!bIsAtRightBorder)      scTiles.push(m_cData[index(cTile.m_uiPositionX + 1, cTile.m_uiPositionY)]);
    
    //Stores the valid neighbors
    std::vector<const Tile*> vcNeighbors;
    
    //Iterate through all of the neighbors and store those who are valid (compensate for reducation in value before test)
    while (!scTiles.empty()) {
        
        const Tile& cNeighbor = *scTiles.top();
        scTiles.pop();
        
        //Check for water tiles
        if (cNeighbor.eType != kWater) {
            
            /*
             * Check if the neighbor is sideways or not, otherwise we add (default).
             * For sideways neighbors the related neighbors must also be checked.
             * When the relevent tiles for the neighbors (adjacent in direction) have
             * been checked and found not to be Water, it's valid.
             */
            
            switch (cTile.getDirection(cNeighbor)) {
                case kLeftDown:
                    
                    //Must get the 'Down' and 'Left' neighbors of current tile - they must exist due to sideways existing
                    if (getTile(cTile, kLeft)->eType == kWater) continue;
                    if (getTile(cTile, kDown)->eType == kWater) continue;
                    vcNeighbors.push_back(&cNeighbor);
                    break;
                    
                case kLeftUp:
                    
                    //Must get the 'Up' and 'Left' neighbors of current tile - they must exist due to sideways existing
                    if (getTile(cTile, kLeft)->eType == kWater) continue;
                    if (getTile(cTile, kUp)->eType == kWater) continue;
                    vcNeighbors.push_back(&cNeighbor);
                    break;
                    
                case kRightDown:
                    
                    //Must get the 'Down' and 'Right' neighbors of current tile - they must exist due to sideways existing
                    if (getTile(cTile, kRight)->eType == kWater) continue;
                    if (getTile(cTile, kDown)->eType == kWater) continue;
                    vcNeighbors.push_back(&cNeighbor);
                    break;
                    
                case kRightUp:
                    
                    //Must get the 'Up' and 'Right' neighbors of current tile - they must exist due to sideways existing
                    if (getTile(cTile, kRight)->eType == kWater) continue;
                    if (getTile(cTile, kUp)->eType == kWater) continue;
                    vcNeighbors.push_back(&cNeighbor);
                    break;
                    
                    //Since the direction is 'Up', 'Left', 'Right', 'Down' its valid
                default: vcNeighbors.push_back(&cNeighbor); break;
            }
            
        }
        
    }
    
    return vcNeighbors;
    
}
