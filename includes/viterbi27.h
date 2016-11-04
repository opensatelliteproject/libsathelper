/*
 * viterbi27.h
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#ifndef SATHELPER_INCLUDES_VITERBI27_H_
#define SATHELPER_INCLUDES_VITERBI27_H_

#include <stdint.h>


#define _VITERBI27_POLYA 0x4F
#define _VITERBI27_POLYB 0x6D

class Viterbi27 {
private:
	int polynomials[2];
	uint8_t *checkDataPointer;
	void *viterbi;
	int frameBits;
	int BER;
	bool calculateErrors;

	void encode(uint8_t *input, uint8_t *output);
	static uint32_t calculateError(uint8_t *original, uint8_t *corrected, int length);

public:
	Viterbi27(int frameBits, int polyA, int polyB);
	Viterbi27(int frameBits) : Viterbi27(frameBits, _VITERBI27_POLYA, _VITERBI27_POLYB) {}

	inline int DecodedSize() { return this->frameBits / 8; }
	inline int EncodedSize() { return this->frameBits; }
	inline void SetCalculateErrors(bool calculateErrors) { this->calculateErrors = calculateErrors; }
	inline int GetBER() { return this->BER / 2; }
	inline float GetPercentBER() { return (100.f * this->BER) / this->frameBits; }

	void decode(uint8_t *input, uint8_t *output);

	~Viterbi27();
};



#endif /* SATHELPER_INCLUDES_VITERBI27_H_ */
