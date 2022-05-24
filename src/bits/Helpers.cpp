#include <limits.h>
#include <limits>
#include <stdint.h>
#include "libEmbedded/bits/Helpers.h"

namespace libEmbedded
{
    namespace bits
    {
        void MoveWithOffset(void* dest, size_t destinationBitOffset, void* src, size_t sourceBitOffset, size_t bitCount)
        {
            if (dest == nullptr || src == nullptr || (dest == src && destinationBitOffset == sourceBitOffset))
            {
                return;
            }

            typedef unsigned char data_t;
            constexpr size_t kMaxBitSize = CHAR_BIT;

            data_t *destination = (data_t*)dest;
            data_t *source = (data_t*)src;
            size_t destinationOffset = destinationBitOffset;
            size_t sourceOffset = sourceBitOffset;
            size_t copiedBits = 0;
            while (copiedBits < bitCount)
            {
                const size_t leftInDestination = kMaxBitSize - destinationOffset;
                const size_t leftInSource = kMaxBitSize - sourceOffset;
                const size_t maxBitCopy = leftInSource < leftInDestination ? leftInSource : leftInDestination;
                const data_t fromDestination = *destination & ~CreateMask<data_t>(destinationOffset);
                const data_t fromSource = ((*source) >> sourceOffset) & CreateMask<data_t>(maxBitCopy);
                *destination = fromDestination | (fromSource << destinationOffset);
                destinationOffset += maxBitCopy;
                sourceOffset += maxBitCopy;
                copiedBits += maxBitCopy;
                if (destinationOffset >= kMaxBitSize)
                {
                    destination++;
                    destinationOffset = 0;
                }
                if (sourceOffset >= kMaxBitSize)
                {
                    source++;
                    sourceOffset = 0;
                }
            }
        }
    } // namespace bits
} // namespace libEmbedded

