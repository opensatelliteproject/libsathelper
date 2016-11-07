/*
 * packetfixer.h
 *
 *  Created on: 05/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_PACKETFIXER_H_
#define INCLUDES_PACKETFIXER_H_

#include <mutex>

namespace SatHelper {
    enum PhaseShift {
        DEG_0, DEG_90, DEG_180, DEG_270
    };

    class PacketFixer {
    private:
        static bool initialized;
        static uint8_t deg90LUT[256];
        static uint8_t iqInvertLUT[256];
        static void initializeLUT();

    public:
        PacketFixer() {
            if (!initialized) {
                PacketFixer::initializeLUT();
            }
        }
        void fixPacket(uint8_t *data, uint32_t length, PhaseShift phaseShift, bool iqInversion);
    };
}

#endif /* INCLUDES_PACKETFIXER_H_ */
