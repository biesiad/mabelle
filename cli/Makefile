CC = gcc
CFLAGS = -Wall
CP = cp
RM = rm
BUILD = build
SRC = bell

bell:
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS)	-o $(BUILD)/bell $(SRC).c

all:
	bell install

install:
	$(CP) $(BUILD)/bell /usr/local/bin

clean:
	$(RM) -rf $(BUILD)

deinstall:
	$(RM) -f /usr/local/bin/bell
