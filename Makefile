CC = gcc
CFLAGS = -std=c11 -g -Iheader -Iheader/adt
CLIBS = -lm

build:
	$(CC) $(CFLAGS) src/*.c src/adt/*.c $(CLIBS) -o bin/main
