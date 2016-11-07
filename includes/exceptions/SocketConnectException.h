/*
 * SocketConnectException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SOCKETCONNECTEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SOCKETCONNECTEXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class SocketConnectException: public SocketException {
    public:
        SocketConnectException(int errorCode) :
                SocketException(errorCode) {
        }

        virtual const char* what() const throw () {
            return "There was an Socket Connection problem";
        }
        virtual std::string reason() const {
            std::stringstream ss;
            ss << "There was an Socket Connection error with code " << errorCode;
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_SOCKETCONNECTEXCEPTION_H_ */
