/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  TCP Server by Maxim Zalutskiy                          *
 *  CSC 643                                                *
 *  chatSrv.cpp                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <cstdlib>
#include "tcpSock.h"

using namespace std;

// gracefull extraction of arguments from command line
// returns port
void get_args(int argc, char *argv[], int &port);

int main(int argc, char *argv[]) {

    int port;
	get_args(argc, argv, port);	
    TCPsocket mySock;

    mySock.bind(port); // 1784 is a good number 
    mySock.listen();

	while(true) { //loops over sessions from different clients
		TCPsocket clientSock = mySock.accept();

		char buffer[mySock.buffer_size];

		while(true) { // loops over messages
		    clientSock >> buffer; // message from client 

			// this is how I quit
		    if( (buffer[0]=='q' or buffer[0]=='Q') and buffer[1]=='\0') {
		        clientSock.close();
		        break;
		    }
			cout << "From " <<clientSock.local_address() << "(" << clientSock.local_port() << "): ";
			cout << buffer << endl; // let's see what he says

			cout << "Message -> ";
			char msg[mySock.buffer_size];
			cin.getline(msg, mySock.buffer_size);
			clientSock << msg;// my message to the client
		}
	}
    return 0;
}

//----------------------------------------------------------------

void get_args(int argc, char *argv[], int &port) {
    if(argc < 2){
        cerr << "Not enough parameters" << endl;
        exit(1);
    } else if(argc > 2) {
        cerr << "Too many parameters" << endl;
        exit(2);
    } else if(argc == 2) {
        port = atoi(argv[1]);
    }	
}
