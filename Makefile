CC=g++

CFLAGS=-Iinclude/ -I../cpp-netlib-0.9.4 -I../boost-build/include

LDIR= -L./ -L/Users/patrick/src/patrick/tempo-cpp-client/boost-build/lib
LIBS=-lssl -lcrypto -L../cpp-netlib-build/libs/network/src -lboost_thread -lboost_system -lboost_regex -lboost_date_time -lcppnetlib-client-connections -lcppnetlib-uri -ltempodb

OBJ=Series.o Client.o

%.o: src/%.cpp
		$(CC) -c -o $@ $< $(CFLAGS)

staticlink: $(OBJ)
		ar rcs libtempodb.a $(OBJ)

tempodb: staticlink
		$(CC) tempodb_client_example.cpp -o tempodb_client_example $(CFLAGS) $(LDIR) $(LIBS)  

all: tempodb

clean: 
	rm -f *.o libtempodb.a tempodb_client_example
