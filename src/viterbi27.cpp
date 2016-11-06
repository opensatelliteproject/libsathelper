/*
 * viterbi27.cpp
 *
 *  Created on: 04/11/2016
 *      Author: lucas
 */

extern "C" {
#include <fec.h>
}

#include "viterbi27.h"
#include <memory.h>
#include "correlator.h"
#include "ViterbiCreationException.h"

using namespace SatHelper;

Viterbi27::Viterbi27(int frameBits, int polyA, int polyB) {
    this->frameBits = frameBits;
    this->polynomials[0] = polyA;
    this->polynomials[1] = polyB;
    this->BER = 0;
    this->calculateErrors = true;
    set_viterbi27_polynomial(this->polynomials);
    if ((viterbi = create_viterbi27(this->frameBits)) == NULL) {
        throw ViterbiCreationException();
    }
    this->checkDataPointer = new uint8_t[this->frameBits];
}

Viterbi27::~Viterbi27() {
    delete[] this->checkDataPointer;
}

void Viterbi27::encode(uint8_t *input, uint8_t *output) {
    unsigned int encstate = 0;
    uint8_t c;
    uint32_t pos = 0;
    uint32_t opos = 0;
    uint32_t outputLength = this->frameBits / 8;
    uint32_t inputLength = this->frameBits;

    memset(output, 0x00, outputLength);
    while (pos < inputLength && (pos * 16) < outputLength) {
        c = input[pos];
        for (int i = 7; i >= 0; i--) {
            encstate = (encstate << 1) | ((c >> 7) & 1);
            c <<= 1;
            output[opos] = ~(0 - parity(encstate & polynomials[0]));
            output[opos + 1] = ~(0 - parity(encstate & polynomials[1]));

            opos += 2;
        }
        pos++;
    }
}

void Viterbi27::decode(uint8_t *input, uint8_t *output) {
    init_viterbi27(viterbi, 0);
    update_viterbi27_blk(viterbi, input, this->frameBits + 6);
    chainback_viterbi27(viterbi, output, this->frameBits, 0);
    if (calculateErrors) {
        this->encode(output, this->checkDataPointer);
        this->BER = Viterbi27::calculateError(input, this->checkDataPointer, this->frameBits);
    }
}

uint32_t Viterbi27::calculateError(uint8_t *original, uint8_t *corrected, int length) {
    uint32_t errors = 0;
    for (int i = 0; i < length; i++) {
        errors += (uint32_t) Correlator::hardCorrelate(original[i], ~corrected[i]);
    }

    return errors;
}
