/*
 * tcpclient.cpp
 *
 *  Created on: 25/12/2016
 *      Author: Lucas Teske
 */

#include <SatHelper/tcpclient.h>
#include <cstdio>
#include <SatHelper/exceptions.h>
#include <fcntl.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <ws2tcpip.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
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
#ifdef _MSC_VER
		_close(s);
#else
        close(s);
#endif
    }
} /* namespace SatHelper */
