/*
 * reedsolomon.cpp
 *
 *  Created on: 04/11/2016
 *      Author: Lucas teske
 */

#include <reedsolomon.h>

extern "C" {
#include <fec.h>
}

#define NULL 0


using namespace SatHelper;

ReedSolomon::ReedSolomon(uint32_t parityOffset) {
    this->parityOffset = parityOffset;
    this->copyParityToOutput = false;
}

uint32_t ReedSolomon::decode_ccsds(uint8_t *data) {
    return decode_rs_ccsds((unsigned char *) data, NULL, 0, 0);
}

uint32_t ReedSolomon::decode_rs8(uint8_t *data) {
    return decode_rs_8((unsigned char *) data, NULL, 0, 0);
}

void ReedSolomon::deinterleave(uint8_t *data, uint8_t *output, uint8_t pos, uint8_t I) {
    // Copy data
    for (int i = 0; i < 223; i++) {
        output[i] = data[i * I + pos];
    }
    // Copy parity
    for (int i = 0; i < 32; i++) {
        output[i + 223] = data[this->parityOffset + i * I + pos];
    }
}

void ReedSolomon::interleave(uint8_t *data, uint8_t *output, uint8_t pos, uint8_t I) {
    // Copy data
    for (int i = 0; i < 223; i++) {
        output[i * I + pos] = data[i];
    }
    // Copy parity
    if (copyParityToOutput) {
        for (int i = 0; i < 32; i++) {
            output[parityOffset + i * I + pos] = data[i + 223];
        }
    }
}
