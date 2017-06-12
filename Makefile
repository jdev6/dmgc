CC=gcc
OUT=./dmgc
CFLAGS=-std=c11 -Wall -O3

.PHONY: all test

all:
	$(CC) $(CFLAGS) *.c -o $(OUT)

debug:
	$(CC) $(CFLAGS) -ggdb *.c -o $(OUT).debug

test: debug
	$(OUT).debug tetris.gb
