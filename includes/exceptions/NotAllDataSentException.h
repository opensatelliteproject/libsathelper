/*
 * NotAllDataSentException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_NOTALLDATASENTEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_NOTALLDATASENTEXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class NotAllDataSentException: public SocketException {
    public:
        NotAllDataSentException(int errorCode) :
                SocketException(errorCode) {
        }

        virtual const char* what() const throw () {
            return "There was an socket write exception.";
        }
    };

}
#endif /* INCLUDES_EXCEPTIONS_NOTALLDATASENTEXCEPTION_H_ */
