/*
 * tcpserver.cpp
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#include <tcpserver.h>
#include <cstdio>
#include <unistd.h>
#include <socket.h>
#include <sys/resource.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <sstream>
#include <iostream>
#include "exceptions.h"

using namespace SatHelper;

void TcpServer::Listen(int port) {
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        throw SocketErrorException(errno);
    }

    memset(&socketAddr, '\0', sizeof(socketAddr));

    socketAddr.sin_family = AF_INET;
    socketAddr.sin_addr = address.ToInAddr();
    socketAddr.sin_port = htons(port);
    int x = bind(s, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
    if (x < 0) {
        throw SocketBindException(errno, port, address);
    }

    listen(s, 1);

    this->port = port;
}

TcpSocket TcpServer::Accept() {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int ns = accept(s, (sockaddr *) &clientAddr, &clientAddrLen);

    if (ns < 0) {
        throw SocketAcceptException(errno);
    }

    return TcpSocket(IPAddress(clientAddr.sin_addr), ns);
}