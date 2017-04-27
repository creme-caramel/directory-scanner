FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(shell cd $(dir $(FILEPATH));pwd)

CC = clang
CFLAGS = -g -c -Wall -pedantic -Wextra -Wno-unused-parameter 
LDFLAGS = -L$(CURDIR)/lib -lsqlite3
RPATH = -Wl,-rpath=$(CURDIR)/lib
INC = -I$(CURDIR)/inc

all: main

main: main.o

test:
	./main
	sqlite3 -header -csv table.db "select * from my_table;" > output.csv

clean:
	rm -f main main.o

.PHONY: test clean all
