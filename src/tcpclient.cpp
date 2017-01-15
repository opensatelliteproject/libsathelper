/*
 * tcpclient.cpp
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 */

#include "tcpclient.h"
#include <cstdio>
#include "exceptions.h"
#include <fcntl.h>

#ifdef _WIN32
    #include <windows.h>
    #include <winsock2.h>
    #include <Ws2tcpip.h>
#else
    #include <unistd.h>
    #include <socket.h>
    #include <sys/resource.h>
    #include <sys/select.h>
    #include <sys/ioctl.h>
    #include <netdb.h>
#endif

namespace SatHelper {

    void TcpClient::Connect() {
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) {
            throw SocketErrorException(errno);
        }
        memset(&socketAddr, '\0', sizeof(socketAddr));

        socketAddr.sin_family = AF_INET;
        socketAddr.sin_addr = address.ToInAddr();
        socketAddr.sin_port = htons(port);
        int x = connect(s, (struct sockaddr *) &socketAddr, sizeof(socketAddr));
        if (x < 0) {
            throw SocketConnectException(errno);
        }
    }

    void TcpClient::Close() {
        close(s);
    }
} /* namespace SatHelper */
