/*
 * Socket.cpp
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */
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


Socket::~Socket() {

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
    int n = send(s, data, length, 0);
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
    int ret = ioctl(s, FIONREAD, &bytesAvailable);

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
        status = shutdown(s, 2);
        if (status == 0) {
            status = close(s);
        }
    }
}

