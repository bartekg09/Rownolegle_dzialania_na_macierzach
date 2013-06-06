CC = /usr/bin/gcc
CFLAGS = -Wall -ggdb

all: build

build: gen licz
	
gen: generator.o
	$(CC) $(CFLAGS) -o gen generator.o

licz: main.o funkcje.o
	$(CC) $(CFLAGS) -o licz main.o funkcje.o

generator.o: generator.c generator.h
	$(CC) $(CFLAGS) -c -o generator.o generator.c

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c -o main.o main.c
	
funkcje.o: funkcje.c matrix.h
	$(CC) $(CFLAGS) -c -o funkcje.o funkcje.c 
