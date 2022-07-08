#-*- Makefile -*-

all: crypt.exe crypt.o main.o

crypt.exe: crypt.o main.o
	g++ crypt.o main.o -o crypt.exe

crypt.o: crypt.cpp
	g++ crypt.cpp -c

main.o: main.cpp
	g++ main.cpp -c

clean:
	rm *.o crypt.exe