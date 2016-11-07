/*
 * Socket.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_SOCKET_H_
#define INCLUDES_SOCKET_H_

#include <cstdint>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include "ipaddress.h"

namespace SatHelper {
    class Socket {
    protected:
        IPAddress address;
        fd_set writeFd;
        struct sockaddr_in socketAddr;
        int s;

    public:
        Socket() :
                Socket(IPAddress()) {
            memset(&socketAddr, 0x00, sizeof(sockaddr_in));
        }

        Socket(IPAddress addr) :
                address(addr), s(0) {
        }

        Socket(std::string addr) :
                address(IPAddress(addr)), s(0) {
        }

        Socket(IPAddress addr, int socket) :
                address(addr), s(socket) {
        }

        Socket(const Socket &a) :
                Socket(a.address, a.s) {
            socketAddr = a.socketAddr;
        }

        virtual ~Socket();

        void Receive(char *data, int length);
        void Send(char *data, int length);
        void SendTo(char *data, int length, IPAddress destinationAddress, int destinationPort);
        int ReceiveFrom(char *data, int length, IPAddress fromAddress, int fromPort);

        uint64_t AvailableData();

        inline const IPAddress GetAddress() const {
            return address;
        }

        virtual void Close();
    };
}
#endif /* INCLUDES_SOCKET_H_ */
