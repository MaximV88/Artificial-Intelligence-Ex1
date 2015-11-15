//
//  IDSAlgorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef IDSAlgorithm_hpp
#define IDSAlgorithm_hpp

#include "Algorithm.hpp"

class IDSAlgorithm : public Algorithm {
public:
    
    /** Returns a vector of direction that represent the result of the algorithm */
    virtual Path* apply(const Map& cMap) const;
    
};

#endif /* IDSAlgorithm_hpp */
