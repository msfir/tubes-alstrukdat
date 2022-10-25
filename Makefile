CC = gcc
CFLAGS = -std=c11 -g -Iheader -Iheader/adt
CLIBS = -lm

build:
	$(CC) $(CFLAGS) src/main.c src/adt/*.c $(CLIBS) -o bin/main
	$(CC) $(CFLAGS) src/driver_food.c src/adt/*.c $(CLIBS) -o bin/driver_food
