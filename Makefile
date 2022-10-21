CC = clang
CFLAGS = -std=c11 -g -Iheader -lm

compile:
	mkdir -p build
	$(CC) $(CFLAGS) src/*.c src/adt/*.c -o build/main
