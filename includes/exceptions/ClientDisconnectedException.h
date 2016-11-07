/*
 * ClientDisconnectedException.h
 *
 *  Created on: 06/11/2016
 *      Author: lucas
 */

#ifndef INCLUDES_EXCEPTIONS_CLIENTDISCONNECTEDEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_CLIENTDISCONNECTEDEXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class ClientDisconnectedException: SocketException {
    public:
        ClientDisconnectedException() :
                SocketException(0) {
        }
        virtual const char* what() const throw () {
            return "The client has been disconnected.";
        }
        virtual std::string reason() const {
            std::stringstream ss;
            ss << "The client has been disconnected.";
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_CLIENTDISCONNECTEDEXCEPTION_H_ */
