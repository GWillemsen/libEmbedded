#include <stddef.h>
#include <limits.h>
#include "libEmbedded/Span.h"
#include "libEmbedded/Helpers.h"
#include "libEmbedded/bits/BitBuffer.h"
#include "libEmbedded/bits/Helpers.h"

// namespace libEmbedded
// {
//     namespace bits
//     {
//         BitBuffer::BitBuffer(Span<char> workspaceInput, size_t workspaceBitSize) : workspace(workspaceInput), usedBits(0), totalBits(workspaceBitSize)
//         {

//         }

//         size_t BitBuffer::PushData(const char* data, size_t bitCount)
//         {
//             return 0;
//         }

//         size_t BitBuffer::ReadData(char* data, size_t bitsToRead)
//         {
//             size_t readCount = bitsToRead < this->usedBits ? bitsToRead : this->usedBits;
//             size_t charReads = readCount / CHAR_MAX;
//             size_t bitsRead = readCount - charReads;
//             for (size_t i = 0; i < charReads; i++)
//             {
//                 data[i] = workspace[i];
//             }
//             if (bitsRead > 0)
//             {
//                 data[charReads] = this->workspace[charReads] & CreateMask<char>(bitsRead);
//             }
//             this->RemoveData(readCount);

//             return 0;
//         }

//         size_t BitBuffer::AvailableForWrite()
//         {
//             return this->totalBits - this->usedBits;
//         }

//         size_t BitBuffer::AvailableForRead()
//         {
//             return this->usedBits;
//         }

//         void BitBuffer::RemoveData(size_t bitCount)
//         {
//             if (this->TryOptimizedRemove(bitCount) == false)
//             {
//                 this->ComplexMoveData(0, bitCount);
//             }
//         }

//         bool BitBuffer::TryOptimizedRemove(size_t bitCount)
//         {
//             if (bitCount == this->usedBits)
//             {
//                 for (size_t i = 0; i < bitCount; i++)
//                 {
//                     this->workspace[i] = 0;
//                 }
//                 this->usedBits = 0;
//                 return true;
//             }
//             else if (bitCount % CHAR_BIT == 0)
//             {
//                 const size_t bytesRemoved = bitCount / CHAR_BIT;
//                 const size_t bitsLeft = this->usedBits - bitCount;
//                 const size_t bytesLeft = libEmbedded::DivdeByAndRoundUp(bitsLeft, CHAR_MAX);
//                 for (size_t i = 0; i < bytesLeft; i++)
//                 {
//                     this->workspace[i] = this->workspace[bytesRemoved + i];
//                     this->workspace[bytesRemoved + i] = 0;;
//                 }
//                 this->usedBits = bytesLeft;
//                 return true;
//             }
//             return false;
//         }

//         void BitBuffer::ComplexMoveData(size_t destinationBitIndex, size_t sourceBitIndex)
//         {

//         }

//         template<size_t TBufferBitSize>
//         StaticBitBuffer<TBufferBitSize>::StaticBitBuffer() : workspaceBuffer{ 0 }, BitBuffer(Span<char>(workspaceBuffer, workspaceBufferSize), TBufferBitSize)
//         {

//         }
//     } // namespace bits
// } // namespace libEmbedded

