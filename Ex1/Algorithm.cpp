//
//  Algorithm.cpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#include "Algorithm.hpp"
#include "IDSAlgorithm.hpp"
#include "UCSAlgorithm.hpp"

Algorithm* Algorithm::createAlgorithm(const std::string &strFormattedType) {
    
    if (strFormattedType.find("IDS") != std::string::npos)
        return createAlgorithm(Algorithm::Type::kIDS);
    else if (strFormattedType.find("UCS") != std::string::npos)
        return createAlgorithm(Algorithm::Type::kUCS);
    
    return nullptr;
    
}

Algorithm* Algorithm::createAlgorithm(Algorithm::Type eType) {
    
    switch (eType) {
        case Algorithm::Type::kIDS: return new IDSAlgorithm();
        case Algorithm::Type::kUCS: return new UCSAlgorithm();
        default:                  return nullptr;
    }
    
}

Algorithm::~Algorithm() { }