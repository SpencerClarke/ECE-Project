.PHONY: clean

CC := gcc
CFLAGS := -I./include -I./build -Wall -Wextra -Wpedantic -g
LDFLAGS := -lfl -lm
BUILD_DIR := build
BIN_DIR := bin

bin/a.out: src/main.c build/interpreter.o build/lex.o build/transcendentals.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o bin/a.out build/transcendentals.o build/lex.o build/interpreter.o src/main.c $(LDFLAGS)

build/interpreter.o: src/interpreter.c include/interpreter.h include/lex.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/interpreter.c -o build/interpreter.o

build/lex.o: include/lex.h src/lex.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/lex.c -o build/lex.o

build/transcendentals.o: include/transcendentals.h src/transcendentals.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/transcendentals.c -o build/transcendentals.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
clean:
	rm -f bin/a.out
	rm -f build/*
