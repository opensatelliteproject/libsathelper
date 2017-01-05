/*
 * PacketFixerTest.h
 *
 *  Created on: 05/01/2017
 *      Author: Lucas Teske
 */

#ifndef TESTS_PACKETFIXERTEST_H_
#define TESTS_PACKETFIXERTEST_H_

#include "BaseTest.h"

namespace SatHelper {

    class PacketFixerTest: public BaseTest {
    private:
        const static uint8_t baseData[];
        const static uint8_t deg0[];
        const static uint8_t deg90[];
        const static uint8_t deg180[];
        const static uint8_t deg270[];
        const static uint8_t degIQ[];
    public:
        std::string TestName() const override { return std::string("Packet Fixer Test"); }
        bool RunTest() override;
    };

} /* namespace SatHelper */

#endif /* TESTS_PACKETFIXERTEST_H_ */
