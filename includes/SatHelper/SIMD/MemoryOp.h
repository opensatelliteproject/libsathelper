/*
 * MemoryOp.h
 *
 *  Created on: 06/01/2017
 *      Author: Lucas Teske
 */

#ifndef SRC_SIMD_MEMORYOP_H_
#define SRC_SIMD_MEMORYOP_H_

#if defined(_M_IX86) || defined(_M_X86) || defined(__i386__) || defined(__x86_64) || defined(_M_X64)
#define MEMORY_OP_X86
#elif defined(__arm__) || defined(_M_ARM) || defined(__aarch64__)
// For now we don't have ARM Vec instructions, so lets fall back to generic
// #define MEMORY_OP_ARM
#define MEMORY_OP_GENERIC
#else
#define MEMORY_OP_GENERIC
#endif

#include <cstddef>

namespace SatHelper {

    class MemoryOp {
    public:
        static int getAligment();
        static void *alignedAlloc(size_t size, size_t alignment);
        static void free(void *data);
    };

} /* namespace SatHelper */

#endif /* SRC_SIMD_MEMORYOP_H_ */
