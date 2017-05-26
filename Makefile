FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
SRC := $(CURDIR)/src/
DB := $(SRC)db/
INC := -I$(CURDIR)/include/

CC = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -lsqlite3 -lm
BIN = $(SRC)scan

RPATH = -Wl,-rpath=$(DB) -L$(DB) 
LIBS = -ldb

all: muttypehash db $(BIN)

muttypehash:
	gperf -t $(SRC)hash/muttype.gperf > $(SRC)hash/muttype.h

db: $(DB)db.o
	$(CC) -shared -o $(DB)libdb.so $(DB)db.o 

$(BIN): $(SRC)scan.o
	$(CC) $(SRC)scan.o -o $(SRC)scan $(RPATH) $(LIBS) $(LDFLAGS)
	@ln -s $(SRC)scan $(CURDIR)/scan

$(SRC)scan.o: $(SRC)scan.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(DB)/db.o: $(DB)/db.c
	$(CXX) $(CFLAGS) -c -o $@ $<
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan $(SRC)scan.o $(DB)/db.o $(BIN)

.PHONY: test clean all
