/*
 * ipaddress.h
 *
 *  Created on: 06/11/2016
 *      Author: Lucas Teske
 */

#ifndef INCLUDES_IPADDRESS_H_
#define INCLUDES_IPADDRESS_H_

#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
#include <netinet/in.h>
#endif

namespace SatHelper {
    enum PresetIpAddress {
        IP_ANY = 0x00000000,        // 0.0.0.0
        IP_LOCALHOST = 0x0100007F   // 127.0.0.1
    };

    class IPAddress {
    private:
        union {
            struct {
                uint8_t b1, b2, b3, b4;
            } bytes;
            uint32_t addr;
        } address_data;
    public:
        IPAddress() :
                IPAddress(IP_ANY) {
        }

        IPAddress(PresetIpAddress addr) :
                IPAddress((uint32_t) addr) {
        }

        IPAddress(uint32_t addr) {
            address_data.addr = addr;
        }

        IPAddress(in_addr addr) {
            address_data.addr = addr.s_addr;
        }

        IPAddress(char b1, char b2, char b3, char b4) {
            address_data.bytes.b4 = b1;
            address_data.bytes.b3 = b2;
            address_data.bytes.b2 = b3;
            address_data.bytes.b1 = b4;
        }

        IPAddress(std::string addr) {
            char ch;
            std::stringstream s(addr);
            int b1, b2, b3, b4;
            s >> b1 >> ch >> b2 >> ch >> b3 >> ch >> b4;
            address_data.bytes.b1 = b1;
            address_data.bytes.b2 = b2;
            address_data.bytes.b3 = b3;
            address_data.bytes.b4 = b4;
        }

        IPAddress(const char* addr) :
                IPAddress(std::string(addr)) {
        }

        std::string ToString() const {
            std::stringstream ss;
            ss << (int) address_data.bytes.b1 << "." << (int) address_data.bytes.b2 << "." << (int) address_data.bytes.b3 << "." << (int) address_data.bytes.b4;
            return ss.str();
        }

        inline uint32_t ToUint32() const {
            return address_data.addr;
        }

        inline in_addr ToInAddr() const {
            in_addr a;
            a.s_addr = address_data.addr;
            return a;
        }

        bool operator==(const IPAddress &b) const {
            return this->ToUint32() == b.ToUint32();
        }

        bool operator!=(const IPAddress &b) const {
            return this->ToUint32() != b.ToUint32();
        }
    };
}

#endif /* INCLUDES_IPADDRESS_H_ */
