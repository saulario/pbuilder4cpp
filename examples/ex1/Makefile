
CC=g++
CFLAGS=-Wall -std=c++11 -c

all: main

main: main.o ex1_entity.o ex1_dao.o
	$(CC) main.cpp ex1_entity.o ex1_dao.o -lcxxtools -ltntdb -lboost_system -o ex1

ex1_entity.o : ex1_entity.cpp ex1_entity.h
	$(CC) $(CFLAGS) ex1_entity.cpp

ex1_dao.o : ex1_dao.cpp ex1_dao.h
	$(CC) $(CFLAGS) ex1_dao.cpp

clean:
	rm *.o ex1
