/*
 * SocketBindException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SOCKETBINDEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SOCKETBINDEXCEPTION_H_

#include "SocketException.h"
#include "ipaddress.h"

namespace SatHelper {
    class SocketBindException: public SocketException {
    private:
        const IPAddress address;
        const int portNumber;
    public:
        SocketBindException(int errorCode, int portNumber, IPAddress address) :
                SocketException(errorCode), address(address), portNumber(portNumber) {
        }

        virtual const char* what() const throw () {
            return "There was an Socket Error";
        }
        virtual std::string reason() const {
            std::stringstream ss;
            ss << "There was an Error binding " << address.ToString() << ":" << portNumber << " with errorCode " << errorCode;
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_SOCKETBINDEXCEPTION_H_ */
