//
//  Path.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 15/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Path.hpp"

Path* Path::createPath(const std::stack<const Tile *>& scPath) {
    
    std::stack<const Tile*> svModifiablePath = scPath;
    
    size_t uiCost = 0;
    std::vector<Tile::Directions> vcDirections;
    
    //Get the information from the order they were added by.
    while (!svModifiablePath.empty()) {
        
        const Tile* cCurrentTile = svModifiablePath.top();
        svModifiablePath.pop();
        
        switch (cCurrentTile->eType) {
            case Tile::Types::kRoad: uiCost += 1; break;
            case Tile::Types::kDirt: uiCost += 3; break;
            case Tile::Types::kHill: uiCost += 10; break;
            default: break; //Shouldnt add cost for non-existing tiles
        }
        
        //Dont add any more directions if its the last
        if (svModifiablePath.empty()) break;
        
        const Tile* cNextTile = svModifiablePath.top();
        
        //Store the direction of this tile compared to the previous
        if (cNextTile) vcDirections.push_back(cCurrentTile->getDirection(*cNextTile));
        
    }
    
    //Return a path with gathered information
    return new Path(vcDirections, uiCost);
    
}

Path* Path::createPath(const std::vector<const Tile *> &vcPath) {
    
    size_t uiCost = 0;
    std::vector<Tile::Directions> vcDirections;
    const Tile* cPrevTile = nullptr;
    
    for (const Tile* cCurrentTile : vcPath) {
        
        switch (cCurrentTile->eType) {
            case Tile::Types::kRoad: uiCost += 1; break;
            case Tile::Types::kDirt: uiCost += 3; break;
            case Tile::Types::kHill: uiCost += 10; break;
            default: break; //Shouldnt add cost for non-existing tiles
        }
        
        //Store the direction of this tile compared to the previous
        if (cPrevTile) vcDirections.push_back(cPrevTile->getDirection(*cCurrentTile));
        
        cPrevTile = cCurrentTile;

    }
    
    //Return a path with gathered information
    return new Path(vcDirections, uiCost);
    
}

Path* Path::createPath(std::nullptr_t) {
    
    return new Path(std::vector<Tile::Directions>(), 0);
    
}

Path::Path(const std::vector<Tile::Directions>& vcDirections, size_t uiCost) :
m_uiCost(uiCost), m_vcDirections(vcDirections) { }

size_t Path::getCost() const { return m_uiCost; }

const std::vector<Tile::Directions>& Path::getDirections() const { return m_vcDirections; }

std::ostream& operator<< (std::ostream &out, const Path &cPath) {

    //Check that there is a path (not empty)
    if (!cPath.m_vcDirections.size()) {
        
        out << "no path";
        return out;
        
    }
    
    //Otherwise gather all of the directions to a string
    std::string strFormatted;

    for (Tile::Directions direction : cPath.m_vcDirections) {
    
        //Append before each direction a '-' character, except for the first one
        if (strFormatted.length()) strFormatted.append("-");
        
        //Append by rules specified in instructions
        switch (direction) {
            case Tile::Directions::kCenter:      strFormatted.append("C");   break; //Something is wrong
            case Tile::Directions::kDown:        strFormatted.append("D");   break;
            case Tile::Directions::kLeft:        strFormatted.append("L");   break;
            case Tile::Directions::kRight:       strFormatted.append("R");   break;
            case Tile::Directions::kUp:          strFormatted.append("U");   break;
            case Tile::Directions::kLeftDown:    strFormatted.append("LD");  break;
            case Tile::Directions::kLeftUp:      strFormatted.append("LU");  break;
            case Tile::Directions::kRightDown:   strFormatted.append("RD");  break;
            case Tile::Directions::kRightUp:     strFormatted.append("RU");  break;
        }
        
    }

    //Print and return
    out << strFormatted << " " << cPath.m_uiCost;
    return out;
    
}