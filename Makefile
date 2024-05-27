CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second

node.o: node.cpp node.h packet.h
	$(CC) $(CFLAGS) -c -o node.o node.cpp

host.o: host.cpp host.h node.h
	$(CC) $(CFLAGS) -c -o host.o host.cpp

router.o: router.cpp router.h	node.h
	$(CC) $(CFLAGS) -c -o router.o router.cpp

manual_router.o: manual_router.cpp manual_router.h router.h
	$(CC) $(CFLAGS) -c -o manual_router.o manual_router.cpp

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c -o link_installer.o link_installer.cpp

service_installer.o:service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c -o service_installer.o service_installer.cpp

message_service.o: message_service.cpp message_service.h service.h
	$(CC) $(CFLAGS) -c -o message_service.o message_service.cpp
	
message_service_installer.o: message_service_installer.cpp message_service_installer.h service_installer.h
	$(CC) $(CFLAGS) -c -o message_service_installer.o message_service_installer.cpp

echo_service.o: echo_service.cpp echo_service.h service.h
	$(CC) $(CFLAGS) -c -o echo_service.o echo_service.cpp
	
echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h service_installer.h
	$(CC) $(CFLAGS) -c -o echo_service_installer.o echo_service_installer.cpp

first.o: scenarios/first.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o first.o scenarios/first.cpp

second.o: scenarios/second.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o second.o scenarios/second.cpp

first: first.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o
	$(CC) $(CFLAGS) -o first first.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o 

second: second.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o
	$(CC) $(CFLAGS) -o second second.o echo_service.o echo_service_installer.o host.o link_installer.o manual_router.o message_service_installer.o message_service.o node.o service_installer.o link.o router.o

clean:
	rm -f *.o first