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
        return createAlgorithm(kIDS);
    else if (strFormattedType.find("UCS") != std::string::npos)
        return createAlgorithm(kUCS);
    
    return NULL;
    
}

Algorithm* Algorithm::createAlgorithm(AlgorithmType eType) {
    
    switch (eType) {
        case kIDS: return new IDSAlgorithm();
        case kUCS: return new UCSAlgorithm();
        default:   return NULL;
    }
    
}

Algorithm::~Algorithm() { }