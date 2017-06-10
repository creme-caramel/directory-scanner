FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)
DBDIR := $(CURDIR)/db
HSDIR := $(CURDIR)/hash
INC := -I$(CURDIR)

CC = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -lsqlite3 -lm
BIN = scan

RPATH = -Wl,-rpath=$(DBDIR) -L$(DBDIR) 
LIBS = -ldb

all: muttypehash db $(BIN)

muttypehash:
	gperf -t $(HSDIR)/muttype.gperf > $(HSDIR)/muttype.h

db: $(DBDIR)/db.o
	$(CC) -shared -o $(DBDIR)/libdb.so $(DBDIR)/db.o 

$(BIN): scan.o $(DBDIR)/db.o
	$(CC) scan.o -o scan $(RPATH) $(LIBS) $(LDFLAGS)
#	$(CC) scan.o $(DBDIR)/db.o -o scan $(LDFLAGS)

scan.o: scan.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(DBDIR)/db.o: $(DBDIR)/db.c
	$(CC) $(CFLAGS) -c -o $@ $<
	
test:
	@chmod +x scandir
	@./scandir --with-no-filters

clean:
	@rm -f scan scan.o $(DBDIR)/db.o $(BIN)

.PHONY: test clean all
