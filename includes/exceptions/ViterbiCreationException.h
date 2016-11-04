/*
 * ViterbiCreationException.h
 *
 *  Created on: 04/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_VITERBICREATIONEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_VITERBICREATIONEXCEPTION_H_

#include "SatHelperException.h"

class ViterbiCreationException: public SatHelperException {
public:
	ViterbiCreationException() : SatHelperException("Failed to create Viterbi") {}

};



#endif /* INCLUDES_EXCEPTIONS_VITERBICREATIONEXCEPTION_H_ */
