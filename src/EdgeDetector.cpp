/**
 * @file EdgeDetector.cpp
 * @author Giel Willemsen
 * @brief Implement the functions from the EdgeDetector defined in EdgeDetector.h
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "libEmbedded/EdgeDetector.h"

namespace libEmbedded
{
    bool EdgeDetector::Update(bool newValue)
    {
        bool hasEdge = false;
        if (this->previousValue && newValue == false)
        {
            if (this->edgeType != EdgeType::RISING)
            {
                hasEdge = true;
            }
        }
        else if (this->previousValue == false && newValue)
        {
            if (this->edgeType != EdgeType::FALLING)
            {
                hasEdge = true;
            }
        }
        this->previousValue = newValue;
        return hasEdge;
    }
    
    bool EdgeDetector::operator==(const EdgeDetector& other) const
    {
        return other.edgeType == this->edgeType && other.previousValue == this->previousValue;
    }

    bool EdgeDetector::operator!=(const EdgeDetector& other) const
    {
        return other.edgeType != this->edgeType || other.previousValue != this->previousValue;
    }
} // namespace libEmbedded
