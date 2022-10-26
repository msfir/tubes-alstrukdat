CC := gcc
CFLAGS := -std=c11 -g
CINCLUDES := -Iheader -Iheader/adt
CLIBS := -lm

ADTS := src/adt/*.c
TARGET := bin

TEST_SOURCES = $(wildcard src/tests/*.c)
TEST_BIN = $(TEST_SOURCES:src/tests/%.c=bin/tests/%)

.SILENT: clean run-test

build:
	@mkdir -p bin
	$(CC) $(CFLAGS) $(CINCLUDES) src/*.c $(ADTS) $(CLIBS) -o $(TARGET)/main

test: build-test run-test

build-test: $(TEST_BIN)

$(TEST_BIN): $(TARGET)/tests/%: src/tests/%.c
	@mkdir -p bin/tests
	$(CC) $(CFLAGS) $(CINCLUDES) $< $(ADTS) $(CLIBS) -o $@

run-test:
	$(foreach bin, $(TEST_BIN), $(bin);)

clean:
	rm -rf bin
