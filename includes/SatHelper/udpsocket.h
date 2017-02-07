/*
 * udpsocket.h
 *
 *  Created on: 07/02/2017
 *      Author: Lucas Teske
 */

#ifndef SRC_UDPSOCKET_H_
#define SRC_UDPSOCKET_H_

#include <SatHelper/socket.h>

namespace SatHelper {

class UdpSocket: public Socket {
private:
    int port;
public:
    UdpSocket(): Socket(), port(0) {}
    UdpSocket(IPAddress addr): Socket(addr), port(0) {}
    UdpSocket(std::string addr): Socket(addr), port(0) {}
    UdpSocket(const UdpSocket &a): Socket(a), port(0) {}

    void Bind(int port);

    inline int GetPort() {
        return port;
    }

    inline void Bind(std::string port) {
        Bind(atoi(port.c_str()));
    }
};

}

#endif /* SRC_UDPSOCKET_H_ */
