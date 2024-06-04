CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second third forth

simulator.o: simulator.cpp simulator.h
	$(CC) $(CFLAGS) -c -o simulator.o simulator.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c -o object.o object.cpp

node.o: node.cpp node.h packet.h object.h
	$(CC) $(CFLAGS) -c -o node.o node.cpp

link.o: link.cpp link.h object.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c -o link_installer.o link_installer.cpp

first.o: scenarios/first.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o first.o scenarios/first.cpp

second.o: scenarios/second.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o second.o scenarios/second.cpp

third.o: scenarios/third.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o third.o scenarios/third.cpp

forth.o: scenarios/forth.cpp echo_service.h echo_service_installer.h host.h link_installer.h manual_router.h message_service_installer.h
	$(CC) $(CFLAGS) -c -o forth.o scenarios/forth.cpp

first: first.o  link_installer.o node.o link.o object.o simulator.o
	$(CC) $(CFLAGS) -o first first.o link_installer.o node.o link.o object.o simulator.o

second: second.o link_installer.o node.o link.o simulator.o object.o
	$(CC) $(CFLAGS) -o second second.o link_installer.o node.o link.o simulator.o object.o

third: third.o link_installer.o node.o link.o simulator.o object.o
	$(CC) $(CFLAGS) -o third third.o link_installer.o node.o link.o simulator.o object.o

forth: forth.o link_installer.o node.o link.o simulator.o object.o
	$(CC) $(CFLAGS) -o forth forth.o link_installer.o node.o link.o simulator.o object.o

clean:
	rm -f *.o first second third first