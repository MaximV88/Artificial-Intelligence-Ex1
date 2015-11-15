//
//  UCSAlgorithm.hpp
//  Ex1
//
//  Created by Maxim Vainshtein on 14/11/2015.
//  Copyright © 2015 Bar-Ilan. All rights reserved.
//

#ifndef UCSAlgorithm_hpp
#define UCSAlgorithm_hpp

#include "Algorithm.hpp"

class UCSAlgorithm : public Algorithm {
    
    /** Returns a vector of direction that represent the result of the algorithm */
    virtual Path* apply(const Map& cMap) const;
    
public:
    
};

#endif /* UCSAlgorithm_hpp */
