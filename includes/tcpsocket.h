/*
 * tcpsocket.hpp
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_TCPSOCKET_HPP_
#define INCLUDES_TCPSOCKET_HPP_

#include <cstdlib>
#include "socket.h"

namespace SatHelper {
    class TcpSocket: public Socket {
    public:
        TcpSocket() :
                Socket() {
        }
        TcpSocket(IPAddress addr) :
                Socket(addr) {
        }
        TcpSocket(std::string addr) :
                Socket(addr) {
        }
        TcpSocket(IPAddress addr, int socket) :
                Socket(addr, socket) {
        }
        TcpSocket(const TcpSocket &a) :
                Socket(a) {
        }
    };
}


#endif /* INCLUDES_TCPSOCKET_HPP_ */
