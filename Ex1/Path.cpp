//
//  Path.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 15/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Path.hpp"

Path::Path(const std::vector<Map::Directions>& vcDirections, size_t uiCost) :
m_uiCost(uiCost), m_vcDirections(vcDirections) { }

size_t Path::getCost() const { return m_uiCost; }

const std::vector<Map::Directions>& Path::getDirections() const { return m_vcDirections; }

std::ostream& operator<< (std::ostream &out, const Path &cPath) {

    //Check that there is a path (not empty)
    if (!cPath.m_vcDirections.size()) {
        
        out << "no path";
        return out;
        
    }
    
    //Otherwise gather all of the directions to a string
    std::string strFormatted;

    for (Map::Directions direction : cPath.m_vcDirections) {
    
        //Append before each direction a '-' character, except for the first one
        if (strFormatted.length()) strFormatted.append("-");
        
        //Append by rules specified in instructions
        switch (direction) {
            case Map::Directions::kCenter: break; //Dont add central direction
            case Map::Directions::kDown:        strFormatted.append("D"); break;
            case Map::Directions::kLeft:        strFormatted.append("L"); break;
            case Map::Directions::kRight:       strFormatted.append("R"); break;
            case Map::Directions::kUp:          strFormatted.append("U"); break;
            case Map::Directions::kLeftDown:    strFormatted.append("LD"); break;
            case Map::Directions::kLeftUp:      strFormatted.append("LU"); break;
            case Map::Directions::kRightDown:   strFormatted.append("RD"); break;
            case Map::Directions::kRightUp:     strFormatted.append("RU"); break;
        }
        
    }

    //Print and return
    out << strFormatted << " " << cPath.m_uiCost;
    return out;
    
}