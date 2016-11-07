/*
 * SocketNotReadyException.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_EXCEPTIONS_SOCKETNOTREADYEXCEPTION_H_
#define INCLUDES_EXCEPTIONS_SOCKETNOTREADYEXCEPTION_H_

#include "SocketException.h"

namespace SatHelper {
    class SocketNotReadyException: public SocketException {
    public:
        SocketNotReadyException() :
                SocketException(-1) {
        }

        virtual const char* what() const throw () {
            return "The socket was not ready to write.";
        }
        virtual std::string reason() const {
            std::stringstream ss;
            ss << "The socket was not ready to write. ";
            return ss.str();
        }
    };
}

#endif /* INCLUDES_EXCEPTIONS_SOCKETNOTREADYEXCEPTION_H_ */
