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
#include <memory.h>
#include "ipaddress.h"

#ifdef _WIN32
#include <atomic>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <atomic>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

namespace SatHelper {
    class Socket {
    private:
        #ifdef _WIN32
        static std::atomic_bool initialized;
        static std::atomic_uint sockCount;
        void socketInitialize();
        #endif
    protected:
        IPAddress address;
        fd_set writeFd;
        struct sockaddr_in socketAddr;
        int s;

    public:
        Socket() :
                Socket(IPAddress()) {
            memset(&socketAddr, 0x00, sizeof(sockaddr_in));
            #ifdef _WIN32
            socketInitialize();
            #endif
        }

        Socket(IPAddress addr) :
                address(addr), s(0) {
            #ifdef _WIN32
            socketInitialize();
            #endif
        }

        Socket(std::string addr) :
                address(IPAddress(addr)), s(0) {
            #ifdef _WIN32
            socketInitialize();
            #endif
        }

        Socket(IPAddress addr, int socket) :
                address(addr), s(socket) {
            #ifdef _WIN32
            socketInitialize();
            #endif
        }

        Socket(const Socket &a) :
                Socket(a.address, a.s) {
            #ifdef _WIN32
            socketInitialize();
            #endif
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
