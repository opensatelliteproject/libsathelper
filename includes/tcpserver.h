/*
 * tcpserver.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_TCPSERVER_H_
#define INCLUDES_TCPSERVER_H_

#include <tcpsocket.h>

namespace SatHelper {
    class TcpServer: public TcpSocket {
    private:
        int port;
        int maxConnections;

    public:
        TcpServer() :
                TcpSocket(), port(0), maxConnections(10) {
        }

        TcpServer(IPAddress addr) :
                TcpSocket(addr), port(0), maxConnections(10) {
        }

        TcpServer(std::string addr) :
                TcpSocket(addr), port(0), maxConnections(10) {
        }

        TcpServer(int maxConnections) :
                TcpSocket(), port(0), maxConnections(maxConnections) {
        }

        TcpServer(IPAddress addr, int maxConnections) :
                TcpSocket(addr), port(0), maxConnections(maxConnections) {
        }

        TcpServer(std::string addr, int maxConnections) :
                TcpSocket(addr), port(0), maxConnections(maxConnections) {
        }

        void Listen(int port) {
            Listen(port, false);
        }

        void Listen(int port, bool nonBlocking);

        TcpSocket Accept();

        inline int GetPort() {
            return port;
        }

        inline void Listen(std::string port) {
            Listen(atoi(port.c_str()));
        }
    };
}

#endif /* INCLUDES_TCPSERVER_H_ */
