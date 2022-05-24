/**
 * @file BitBuffer.h
 * @author Giel Willemsen (g.willemsen@student.fontys.nl)
 * @brief Helper to manage bitstreams and read/write individual bits instead of byte aligned.
 * @version 0.1
 * @date 2022-05-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#ifndef LIBEMBEDDED_BITS_BIT_BUFFER_H
#define LIBEMBEDDED_BITS_BIT_BUFFER_H

#include <stddef.h>
#include <limits.h>
#include "libEmbedded/Span.h"
#include "libEmbedded/Helpers.h"

namespace libEmbedded
{
    namespace bits
    {

        class BitBuffer
        {
        public:
        private:

        public:
        private:
            Span<char> workspace;
            size_t usedBits;
            size_t totalBits;

        public:
            BitBuffer(Span<char> workspace, size_t workspaceBitSize);

            size_t PushData(const char* data, size_t bitCount);
            size_t ReadData(char* data, size_t bitsToRead);
            size_t AvailableForWrite();
            size_t AvailableForRead();
        private:
            void RemoveData(size_t bitCount);
            bool TryOptimizedRemove(size_t bitCount);
            void ComplexMoveData(size_t destinationBitIndex, size_t sourceBitIndex);
        };

        template<size_t TBufferBitSize>
        class StaticBitBuffer : public BitBuffer
        {
        private:
            static constexpr size_t workspaceBufferSize = libEmbedded::DivdeByAndRoundUp(TBufferBitSize, CHAR_BIT);
            char workspaceBuffer[workspaceBufferSize];
        public:
            StaticBitBuffer();
        };
    } // namespace bits
} // namespace libEmbedded


#endif // LIBEMBEDDED_BITS_BIT_BUFFER_H
