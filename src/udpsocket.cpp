/*
 * udpsocket.cpp
 *
 *  Created on: 07/02/2017
 *      Author: Lucas Teske
 */

#include "SatHelper/udpsocket.h"
#include <fcntl.h>
#include <SatHelper/exceptions.h>

#ifdef _WIN32
    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/resource.h>
    #include <sys/select.h>
    #include <sys/ioctl.h>
    #include <netdb.h>
#endif


using namespace SatHelper;

void UdpSocket::Bind(int port) {
    s = socket(AF_INET, SOCK_DGRAM, 0);
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

    this->port = port;
}


