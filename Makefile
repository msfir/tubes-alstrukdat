CC = gcc
CFLAGS = -std=c11 -g -Iheader -Iheader/adt -lm

compile:
	$(CC) $(CFLAGS) src/*.c src/adt/*.c -o bin/main
