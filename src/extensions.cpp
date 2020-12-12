/*
 * extensions.cpp
 *
 *  Created on: 16/09/2017
 *      Author: Lucas Teske
 */

#include <SatHelper/extensions.h>

#ifdef MEMORY_OP_X86
#include <immintrin.h>

#define FMA3 (1 << 12)
#define SSE  (1 << 26)
#define SSE4 (1 << 20)
#define XCR  (1 << 27)
#define AVX  (1 << 28)

unsigned long long __xgetbv(unsigned int index) {
    unsigned int eax, edx;
    __asm__ __volatile__(
        "xgetbv;"
        : "=a" (eax), "=d"(edx)
        : "c" (index)
    );
    return ((unsigned long long)edx << 32) | eax;
}

void InitExtensions() {
    unsigned int eax, ebx, ecx, edx;
    eax = 0x01;
#ifdef _MSC_VER
    int cpuInfo[4] = { -1 };
    __cpuid(cpuInfo, 1);
    eax = cpuInfo[0];
    ebx = cpuInfo[1];
    ecx = cpuInfo[2];
    edx = cpuInfo[3];
#else
    __asm__ __volatile__(
                         "cpuid;"
                         : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                         : "a"(eax)
                         );
#endif
    SatHelper::Extensions::hasFMA = ecx & FMA3 || false;
    SatHelper::Extensions::hasSSE = edx & SSE || false;
    SatHelper::Extensions::hasSSE4 = ecx & SSE4 || false;

    SatHelper::Extensions::hasAVX = ecx & AVX || false;
    bool osxsaveSupported = ecx & XCR || false;
    if (osxsaveSupported && SatHelper::Extensions::hasAVX) {
        auto xcrFeatureMask = __xgetbv(0);
        SatHelper::Extensions::hasAVX = (xcrFeatureMask & 0x6) == 0x6;
    }

    #if 0
    std::cerr << "Has FMA: "  << (SatHelper::Extensions::hasFMA  ? "true" : "false") << std::endl;
    std::cerr << "Has SSE: "  << (SatHelper::Extensions::hasSSE  ? "true" : "false") << std::endl;
    std::cerr << "Has SSE4: " << (SatHelper::Extensions::hasSSE4 ? "true" : "false") << std::endl;
    std::cerr << "Has AVX: "  << (SatHelper::Extensions::hasAVX  ? "true" : "false") << std::endl;
    #endif
}

#else
void InitExtensions() {
    std::cerr << "Non x86 device detected. No extensions supported." << std::endl;
}

#endif

namespace SatHelper {

bool Extensions::hasFMA = false;
bool Extensions::hasSSE = false;
bool Extensions::hasSSE4 = false;
bool Extensions::hasAVX = false;
bool Extensions::initialized = (InitExtensions(), true);

} /* namespace SatHelper */
