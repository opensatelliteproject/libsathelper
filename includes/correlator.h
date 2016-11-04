/*
 * correlator.h
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_CORRELATOR_H_
#define INCLUDES_CORRELATOR_H_


class Correlator {
public:
	static inline bool hardCorrelate(uint8_t dataByte, uint8_t wordByte) { return ((dataByte >= 127) && (wordByte == 0)) || ((dataByte < 127) && (wordByte == 255)); }
};



#endif /* INCLUDES_CORRELATOR_H_ */
