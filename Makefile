# Compiler
CC=g++
# Compiler options
CFLAGS=-O2 
# Linker
LINK=g++

all: chatSrv chatCli clean

chatSrv: chatSrv.o tcpSock.o
	$(LINK) chatSrv.o tcpSock.o -o chatSrv

tcpSock.o: tcpSock.cpp tcpSock.h
	$(CC) -c $(CFLAGS) tcpSock.cpp

chatSrv.o: chatSrv.cpp tcpSock.h
	$(CC) -c $(CFLAGS) chatSrv.cpp


chatCli: chatCli.o tcpSock.o
	$(LINK) chatCli.o tcpSock.o -o chatCli

chatCli.o: chatCli.cpp tcpSock.h
	$(CC) -c $(CFLAGS) chatCli.cpp

love:
	@echo "Oh don't get fresh with me!"

# Cleaning:
reallyclean:
	/bin/rm -f chatCli chatSrv *.o
clean:
	/bin/rm -f *.o
