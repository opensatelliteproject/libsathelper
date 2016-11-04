/*
 * WordSizeException.h
 *
 *  Created on: 04/11/2016
 *      Author: lucas
 */

#ifndef INCLUDES_EXCEPTIONS_WORDSIZEEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_WORDSIZEEXCEPTION_H_

#include <sstream>
#include "SatHelperException.h"

class WordSizeException: public SatHelperException {
public:
	WordSizeException(uint8_t expectedWordSize, uint8_t currentWordSize) {
		std::stringstream ss;
		ss << "Tried to add word with size " << expectedWordSize << " but there is already a word with size " << currentWordSize;
		this->msg_ = ss.str();
	}
};



#endif /* INCLUDES_EXCEPTIONS_WORDSIZEEXCEPTION_H_ */
