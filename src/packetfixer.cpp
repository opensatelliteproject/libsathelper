/*
 * packetfixer.cpp
 *
 *  Created on: 05/11/2016
 *      Author: Lucas Teske
 */

#include "packetfixer.h"


using namespace SatHelper;

bool PacketFixer::initialized = false;
uint8_t PacketFixer::deg90LUT[256];
uint8_t PacketFixer::iqInvertLUT[256];

void PacketFixer::initializeLUT() {
    for (int i = 0; i < 256; i++) {
        // Phase Ambiquity Mapping for every two bits:
        //00 90
        //ab ab
        //00 10
        //01 00
        //11 01
        //10 11

        // (90deg a) = ~ (0deg b)
        // (90deg b) =   (0deg a)

        deg90LUT[i] = ((i & 0x55) ^ 0x55) << 1 | (i & 0xAA) >> 1;

        // IQ Inversion. Swap every two bits
        iqInvertLUT[i] = (i & 0x55) << 1 | (i & 0xAA) >> 1;
    }
    initialized = true;
}

void PacketFixer::fixPacket(uint8_t *data, uint32_t length, PhaseShift phaseShift, bool iqInversion) {
    for (uint32_t i = 0; i < length; i++) {
        // Process IQ Inversion
        if (iqInversion) {
            data[i] = iqInvertLUT[data[i]];
        }

        // 270 degrees is actually 90 degrees inverted
        if (phaseShift == DEG_90 || phaseShift == DEG_270) {
            data[i] = deg90LUT[data[i]];
        }

        // Invert
        if (phaseShift == DEG_180 || phaseShift == DEG_270) {
            data[i] ^= 0xFF;
        }
    }
}

