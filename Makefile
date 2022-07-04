# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = --std=c++17 -g -I /opt/homebrew/Cellar/nlohmann-json/3.10.5/include
LIBS = -jsoncpp

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Node.o processData.o
	$(CC) $(CFLAGS) -o main main.o Node.o processData.o
	rm *.o

main-dev: main.o Node.o processData.o
	$(CC) $(CFLAGS) -o main main.o Node.o processData.o

# The main.o target can be written more simply
main.o: main.cpp lib/Node.hpp lib/processData.hpp
	$(CC) $(CFLAGS) -c main.cpp

Node.o: lib/node.cpp lib/node.hpp
	$(CC) $(CFLAGS) -c lib/node.cpp

processData.o: lib/processData.cpp lib/processData.hpp
	$(CC) $(CFLAGS) -c lib/processData.cpp

clean:
	rm *.o main
