CC=gcc
CFLAGS=-Wall -g
LIBS=-lcurl
BUILD=./build
SRC=mabelle

mabelle: build
	gcc -o $(BUILD)/$(SRC) $(CFLAGS) $(LIBS) $(SRC).c

all: mabelle

install:
	cp $(BUILD)/$(SRC) /usr/local/bin

build:
	mkdir build

clean:
	rm -rf $(BUILD)

deinstall:
	rm -f /usr/local/bin/$(SRC)
