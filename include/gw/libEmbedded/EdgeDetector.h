/**
 * @file EdgeDetector.h
 * @author Giel Willemsen
 * @brief A helper to do edge detection on a boolean input signal.
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef GW_LIBEMBEDDED_EDGE_DETECTOR_H
#define GW_LIBEMBEDDED_EDGE_DETECTOR_H

namespace gw
{
    namespace libEmbedded
    {
        /**
         * @brief Different types of edges that can be detected.
         * 
         */
        enum class EdgeType
        {
            /**
             * @brief Edge type to detect rising edges.
             */
            RISING,

            /**
             * @brief Edge type to detect falling edges.
             */
            FALLING,

            /**
             * @brief Edge type to detect both rising and falling edges.
             */
            BOTH
        };

        class EdgeDetector
        {
        public:
        private:
            const EdgeType edgeType;
            bool previousValue;

        public:
            /**
             * @brief Creates a new edge dector with the given edge mode.
             * 
             * @param type [in] The type of the edge to detect.
             */
            constexpr EdgeDetector(EdgeType type) : EdgeDetector(type, false){};

            /**
             * @brief Creates a new edge detector with the given edge mode and initial value.
             * 
             * @param type [in] The type of the edge to detect.
             * @param initialValue [in] The initial state of the signal to start detection with on the first iteration.
             */
            constexpr EdgeDetector(EdgeType type, bool initialValue) : previousValue(initialValue), edgeType(type){};

            /**
             * @brief Update the state of the edge detector with a new input value.
             * 
             * @param newValue [in] The latest state of the signal. 
             * @return true If the edge has changed.
             * @return false If the edge has not changed.
             */
            bool Update(bool newValue);
        };
    } // namespace libEmbedded
} // namespace gw

#endif // GW_LIBEMBEDDED_EDGE_DETECTOR_H
