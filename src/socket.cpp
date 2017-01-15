/*
 * Socket.cpp
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */
#include <cstdio>
#include <sstream>
#include <iostream>
#include "exceptions.h"
#include "socket.h"

#ifdef _WIN32
    #include <windows.h>
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    #include <atomic>
    #ifndef MSG_WAITALL
        #define MSG_WAITALL (1 << 3)
    #endif
    #ifndef MSG_NOSIGNAL
        #define MSG_NOSIGNAL 0
    #endif
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <sys/resource.h>
    #include <sys/select.h>
    #include <sys/ioctl.h>
    #include <netdb.h>
    #include <unistd.h>
    #define ioctlsocket ioctl
#endif
using namespace SatHelper;

#ifdef _WIN32
std::atomic_bool Socket::initialized(false);
std::atomic_uint Socket::sockCount(0);

void Socket::socketInitialize() {
    if (!initialized) {
        initialized = true;
        sockCount = 1;
        WSADATA wsa_data;
        WSAStartup(MAKEWORD(1, 1), &wsa_data);
    } else {
        sockCount++;
    }
}
#endif

Socket::~Socket() {
    #ifdef _WIN32
    sockCount--;
    if (!sockCount) {
        WSACleanup();
    }
    #endif
}

void Socket::Receive(char *data, int length) {
    long n = recv(s, data, length, MSG_WAITALL);
    if (n == 0) {
        throw ClientDisconnectedException();
    } else if (n != length) {
        throw SocketErrorException(errno);
    }
}

void Socket::Send(char * data, int length) {
    int n = send(s, data, length, MSG_NOSIGNAL);
    if (n == 0) {
        throw ClientDisconnectedException();
    } else if (n < 0) {
        throw SocketWriteException(errno);
    } else if (n != length) {
        throw NotAllDataSentException(errno);
    }
}

void Socket::SendTo(char * data, int length, IPAddress destinationAddress, int destinationPort) {
    struct sockaddr_in targetSocketAddr;
    targetSocketAddr.sin_family = AF_INET;
    targetSocketAddr.sin_addr = destinationAddress.ToInAddr();
    targetSocketAddr.sin_port = htons(destinationPort);
    if (select(s + 1, NULL, &writeFd, NULL, NULL) < 0) {
        throw SocketWriteException(errno);
    }

    if (FD_ISSET(s, &writeFd)) {
        int n = sendto(s, data, length, 0, (struct sockaddr*) &targetSocketAddr, sizeof(targetSocketAddr));
        if (n == 0) {
            throw ClientDisconnectedException();
        } else if (n < 0) {
            throw SocketWriteException(errno);
        } else if (n != length) {
            throw NotAllDataSentException(errno);
        }
    } else {
        throw SocketNotReadyException();
    }
}

int Socket::ReceiveFrom(char * data, int length, IPAddress fromAddress, int fromPort) {
    struct sockaddr_in targetSocketAddr;
    targetSocketAddr.sin_family = AF_INET;
    targetSocketAddr.sin_addr = fromAddress.ToInAddr();
    targetSocketAddr.sin_port = htons(fromPort);
    socklen_t targetSocketAddrLen = sizeof(targetSocketAddr);

    int n = recvfrom(s, data, length, 0, (struct sockaddr*) &targetSocketAddr, &targetSocketAddrLen);
    if (n == 0) {
        throw ClientDisconnectedException();
    } else if (n < 0) {
        throw SocketErrorException(errno);
    } else {
        return n;
    }
}

uint64_t Socket::AvailableData() {
    if (s < 0) {
        return 0;
    }

    unsigned long bytesAvailable = 0;
    int ret = ioctlsocket(s, FIONREAD, &bytesAvailable);

    switch (ret) {
        case EINVAL:
        case EFAULT:
        case ENOTTY:
            throw SocketErrorException(ret);
            break;
        case EBADF:
            throw ClientDisconnectedException();
            break;
    }

    return bytesAvailable;
}

void Socket::Close() {
    if (s > 0) {
        int status = 0;
#ifdef _WIN32
        status = shutdown(s, SD_BOTH);
        if (status == 0) {
            status = closesocket(s);
        }
#else
        status = shutdown(s, 2);
        if (status == 0) {
            status = close(s);
        }
#endif
    }
}

