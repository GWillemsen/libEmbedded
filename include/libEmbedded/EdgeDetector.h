/**
 * @file EdgeDetector.h
 * @author Giel Willemsen
 * @brief A helper to do edge detection on a boolean input signal.
 * @version 0.1 2022-02-20 Initial value
 * @version 0.2 2022-03-05 Addition of comparison operators
 * @version 0.2 2022-06-14 Wrong construction order of type and value.
 * @date 2022-06-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef LIBEMBEDDED_EDGE_DETECTOR_H
#define LIBEMBEDDED_EDGE_DETECTOR_H

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

    /**
     * @brief A helper class to detect falling and rising edges on a signal.
     * 
     */
    class EdgeDetector
    {
    public:
    private:
        EdgeType edgeType;
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
        constexpr EdgeDetector(EdgeType type, bool initialValue) : edgeType(type), previousValue(initialValue){};

        /**
         * @brief Constructs a new EdgeDetector with the state from the given one.
         * 
         * @param other The EdgeDetector to copy state from.
         */
        constexpr EdgeDetector(const EdgeDetector& other) : edgeType(other.edgeType), previousValue(other.previousValue){}

        /**
         * @brief Update the state of the edge detector with a new input value.
         * 
         * @param newValue [in] The latest state of the signal. 
         * @return true If the edge has changed.
         * @return false If the edge has not changed.
         */
        bool Update(bool newValue);

        /**
         * @brief Get the last state of the signal.
         * 
         * @return The state of the last signal.
         */
        bool GetState() const
        {
            return this->previousValue;
        };

        /**
         * @brief Compares the current EdgeDetector to the given one for equality.
         * @details Does a value compare of the state for the current EdgeDetector with the other.
         * 
         * @param other The other edge detector to compare equality to.
         * @return true If the two EdgeDetectors have the same state.
         * @return false If the two EdgeDetectors have two different states.
         */
        bool operator==(const EdgeDetector& other) const;

        /**
         * @brief Compares the current EdgeDetector to the given one for inequality.
         * @details Does a value inequality compare of the state for the current EdgeDetector with the other.
         * 
         * @param other The other edge detector to compare inequality to.
         * @return true If the two EdgeDetectors have two different states.
         * @return false If the two EdgeDetectors have the same state.
         */
        bool operator!=(const EdgeDetector& other) const;
    };
} // namespace libEmbedded

#endif // LIBEMBEDDED_EDGE_DETECTOR_H
