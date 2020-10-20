CC = gcc
DEST = build/main
SRC = src/main.c
LIBF = ./lib/
LIB = -lcflags -lpthread

all: src/main.c
	$(CC) -o $(DEST) $(SRC) -L$(LIBF) $(LIB)

debug: src/main.c
	$(CC) -g -o $(DEST) $(SRC) -L$(LIBF) $(LIB)
