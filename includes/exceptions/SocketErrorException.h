/*
 * SocketErrorException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SOCKETERROREXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SOCKETERROREXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class SocketErrorException: public SocketException {
    public:
        SocketErrorException(int errorCode) :
                SocketException(errorCode) {
        }

        virtual const char* what() const throw () {
            return "There was an Socket Error";
        }

        virtual std::string reason() const {
            std::stringstream ss;
            ss << "There was an Socket Error with code " << errorCode;
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_SOCKETERROREXCEPTION_H_ */
