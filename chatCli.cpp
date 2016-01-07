/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  TCP Client by Maxim Zalutskiy                          *
 *  CSC 643                                                *
 *  chatCli.cpp                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "tcpSock.h"

using namespace std;

// gracefull extraction of arguments from command line
// returns hostAddr and port
// hostAddr c-string for address
void get_args(int argc, char *argv[], char* &hostAddr, int &port);

int main(int argc, char *argv[]) {
    char *hostAddr; // address to connect
    int port; // port to connec
	get_args(argc, argv, hostAddr, port);

    TCPsocket mySock;
    mySock.connect(hostAddr, port);

    char msg[mySock.buffer_size];

    while(true) { // loops over dialog messages
		cout << "Message -> "; // prompt
		cin.getline(msg, mySock.buffer_size);
		mySock << msg ; // sends msg to the socket

		//quiting
		if( (msg[0]== 'q' or msg[0] == 'Q') and msg[1] == '\0' ) break;

		char buffer[mySock.buffer_size]; // stores data received from socket
		mySock >> buffer; // getting a reply
		cout << mySock.address() <<"("<<mySock.port()<< "): ";
		cout << buffer << endl; // let's see what the host says
    }
    return 0;
}

//----------------------------------------------------------------

void get_args(int argc, char *argv[], char* &hostAddr, int &port) {
    if(argc < 3){
        cerr << "Not enough parameters" << endl;
        exit(1);
    } else if(argc > 3) {
        cerr << "Too many parameters" << endl;
        exit(2);
    } else if(argc == 3) {
        port = atoi(argv[2]);
        hostAddr = new char[strlen(argv[1])+1];
        strcpy(hostAddr, argv[1]);
    }
}
