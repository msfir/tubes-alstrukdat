CC = clang
CFLAGS = -std=c11 -g -Iheader -Iheader/adt -lm

compile:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.c src/adt/*.c -o build/main
