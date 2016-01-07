/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  TCP Socket by Maxim Zalutskiy                          *
 *  CSC 643                                                *
 *  tcpSock.h                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TCPSOCK_H
#define TCPSOCK_H

#include <arpa/inet.h>
#include <string>

using namespace std;

class TCPsocket {
    private:
        int sock;
        struct sockaddr_in hostAddr;
    public:
		// Maximum message size
        static const int buffer_size = 256;

        TCPsocket();// Null constructor

		TCPsocket(int _sock);
		string address(); // gets address of the remote host
        string local_address();// gets the address of the local host
        int port(); // gets the remote port
        int local_port(); // gets the local port
        void close(); // closes the socket
        bool bind(int port); // binds the socket to the local address and the given port

		// listens to the socket for connection requests
		// maxPending is the maximum number of pending connections
		bool listen(int maxPending = 0);
        TCPsocket accept();// accepts connection and returns the accepted socket

		// connects the socket to the IP address (C-string) and port
		bool connect(char* address, int port);

        TCPsocket& operator << (char *msg); // sends a C-string to the socket
        TCPsocket& operator >> (char *buffer); // receives a C-string from the socket
        ~TCPsocket();// distructor
};


#endif // TCPSOCK_H
