/*
 * tcpclient.h
 *
 *  Created on: 25/12/2016
 *      Author: lucas
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include <tcpsocket.h>

namespace SatHelper {

    class TcpClient: public TcpSocket {
    private:
        int port;
    public:
        TcpClient(IPAddress addr, int port) :
                TcpSocket(addr) {
            this->port = port;
        }
        TcpClient(std::string addr, int port) :
                TcpSocket(addr) {
            this->port = port;
        }

        void Connect();
        void Close();

        inline int GetPort() {
            return port;
        }
    };

} /* namespace SatHelper */

#endif /* TCPCLIENT_H_ */
