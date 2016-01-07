/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  TCP Socket by Maxim Zalutskiy                          *
 *  CSC 643                                                *
 *  tcpSock.cpp                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tcpSock.h"
#include <iostream>
#include <sys/socket.h> // socket (), send (), recv ()
#include <arpa/inet.h> // struct socket sockaddr
#include <unistd.h> // close ()
#include <string.h> // memset ()
#include <cstdlib>

using namespace std;

//----------------------------------------------------------------
// Null constructor
TCPsocket::TCPsocket() {
}

//----------------------------------------------------------------
TCPsocket::TCPsocket(int _sock) {
    sock = _sock;
}

//----------------------------------------------------------------
string TCPsocket::address() {
    struct sockaddr_in remoteAddr;
    unsigned int len = sizeof(remoteAddr);

    if(getpeername(sock, (struct sockaddr*)&remoteAddr, &len) == -1) {
        cerr << "Could not get remote host's info" << endl;
        exit(5);
    }

    string remoteAddrString(inet_ntoa(remoteAddr.sin_addr));
    return remoteAddrString;
}

//----------------------------------------------------------------
string TCPsocket::local_address() {
    string remoteAddrString(inet_ntoa(hostAddr.sin_addr));
    return remoteAddrString;
}

//----------------------------------------------------------------
int TCPsocket::port() {
    struct sockaddr_in remoteAddr;
    unsigned int len = sizeof(remoteAddr);

	// getting the remote info
    if(getpeername(sock, (struct sockaddr*)&remoteAddr, &len) == -1) {
        cerr << "Could not get remote host's info" << endl;
        exit(5);
    }

    return ntohs(remoteAddr.sin_port);
}

//----------------------------------------------------------------
int TCPsocket::local_port() {
    return ntohs(hostAddr.sin_port);
}

//----------------------------------------------------------------
void TCPsocket::close() {
    ::close(sock);
}

//----------------------------------------------------------------
bool TCPsocket::bind(int port) {
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == -1) {
        cerr << "Could not create socket \n";
        exit (1);
    }
    hostAddr.sin_family = AF_INET ;
    hostAddr.sin_port = htons(port);
    hostAddr.sin_addr.s_addr = INADDR_ANY ; // my address
    memset (&( hostAddr.sin_zero), '\0', 8); // set to zero


    if(::bind(sock, (struct sockaddr *) &hostAddr, sizeof(struct sockaddr )) == -1){
        cerr << "Could not bind to port" << endl;
        exit(2);
    } else
        return true;
}

bool TCPsocket::listen(int maxPending) {
    if(::listen (sock , maxPending) < 0) {
        cerr << "Could not listen to socket \n";
        exit(3);
    } else
        return true;
}

//----------------------------------------------------------------
TCPsocket TCPsocket::accept() {
    int clientSock;
    struct sockaddr_in clientAddr; // client addr
    unsigned int clientAddrLength = sizeof (struct sockaddr_in );
    clientSock = ::accept(sock, (struct sockaddr *) &clientAddr, &clientAddrLength);
    if(clientSock < 0) {
        cerr << "Could not accept connection\n";
        exit (4);
    }

    TCPsocket acceptSock(clientSock);
    return acceptSock;
}

//----------------------------------------------------------------
bool TCPsocket::connect(char* address, int port) {
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(sock == -1) {
            cerr << "Could not create socket \n";
            exit (1);
        }

    hostAddr.sin_family = AF_INET ; // Internet address
    hostAddr.sin_port = htons(port);
    hostAddr.sin_addr.s_addr = inet_addr(address);
    memset(&( hostAddr .sin_zero), '\0', 8); // set to zero

    // establish connection with server
    if(::connect(sock, (sockaddr*) &hostAddr, sizeof(sockaddr)) < 0) {
        cerr << "TCPsocket: could not connect" << endl;
        exit(2);
        return false;
    } else
        return true;
}

//----------------------------------------------------------------
TCPsocket& TCPsocket::operator << (char* msg) {
    int bytes;
    bytes = send(sock, msg, strlen(msg) + 1, 0);
    if( bytes == -1) {
        cerr << "TCPsocket: could not send to socket \n";
        exit(3);
    }
    return *this;
}

//----------------------------------------------------------------
TCPsocket& TCPsocket::operator >> (char buffer[]) {
    int numBytes = 0;
    if(( numBytes = recv(sock , buffer , buffer_size, 0)) <= 0) {
        cerr << "TCPsocket: could not receive from socket \n";
        exit(4);
    }
    return *this;
}

//----------------------------------------------------------------
TCPsocket::~TCPsocket() {
    ::close(sock);
}

