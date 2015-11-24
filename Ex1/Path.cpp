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
    std::vector<Directions> vcDirections;
    
    //Get the information from the order they were added by.
    while (!svModifiablePath.empty()) {
        
        const Tile* cCurrentTile = svModifiablePath.top();
        svModifiablePath.pop();
        
        switch (cCurrentTile->eType) {
            case kRoad: uiCost += 1; break;
            case kDirt: uiCost += 3; break;
            case kHill: uiCost += 10; break;
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
    std::vector<Directions> vcDirections;
    const Tile* cPrevTile = NULL;
    
    for (std::vector<const Tile*>::const_iterator iterator = vcPath.begin() ; iterator != vcPath.end() ; iterator++) {
        
        const Tile* cCurrentTile = *iterator;
        
        switch (cCurrentTile->eType) {
            case kRoad: uiCost += 1; break;
            case kDirt: uiCost += 3; break;
            case kHill: uiCost += 10; break;
            default: break; //Shouldnt add cost for non-existing tiles
        }
        
        //Store the direction of this tile compared to the previous
        if (cPrevTile) vcDirections.push_back(cPrevTile->getDirection(*cCurrentTile));
        
        cPrevTile = cCurrentTile;

    }
    
    //Return a path with gathered information
    return new Path(vcDirections, uiCost);
    
}

Path::Path(const std::vector<Directions>& vcDirections, size_t uiCost) :
m_uiCost(uiCost), m_vcDirections(vcDirections) { }

size_t Path::getCost() const { return m_uiCost; }

const std::vector<Directions>& Path::getDirections() const { return m_vcDirections; }

std::ostream& operator<< (std::ostream &out, const Path &cPath) {

    //Check that there is a path (not empty)
    if (!cPath.m_vcDirections.size()) {
        
        out << "no path";
        return out;
        
    }
    
    //Otherwise gather all of the directions to a string
    std::string strFormatted;

    for (std::vector<Directions>::const_iterator iterator = cPath.m_vcDirections.begin() ; iterator != cPath.m_vcDirections.end() ; iterator++) {
    
        Directions direction = *iterator;
        
        //Append before each direction a '-' character, except for the first one
        if (strFormatted.length()) strFormatted.append("-");
        
        //Append by rules specified in instructions
        switch (direction) {
            case kCenter:      strFormatted.append("C");   break; //Something is wrong
            case kDown:        strFormatted.append("D");   break;
            case kLeft:        strFormatted.append("L");   break;
            case kRight:       strFormatted.append("R");   break;
            case kUp:          strFormatted.append("U");   break;
            case kLeftDown:    strFormatted.append("LD");  break;
            case kLeftUp:      strFormatted.append("LU");  break;
            case kRightDown:   strFormatted.append("RD");  break;
            case kRightUp:     strFormatted.append("RU");  break;
        }
        
    }

    //Print and return
    out << strFormatted << " " << cPath.m_uiCost;
    return out;
    
}