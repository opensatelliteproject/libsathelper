/*
 * SocketAcceptException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SOCKETACCEPTEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SOCKETACCEPTEXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class SocketAcceptException: public SocketException {
    public:
        SocketAcceptException(int errorCode) :
                SocketException(errorCode) {
        }

        virtual const char* what() const throw () {
            return "There was an error accepting a client.";
        }

        virtual std::string reason() const {
            std::stringstream ss;
            ss << "There was an error accepting a client. ErrorCode: " << errorCode;
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_SOCKETACCEPTEXCEPTION_H_ */
